#include "video_capture_ds.h"

//VIDEODEVICE
//public
VideoDevice::VideoDevice()
{
	friendlyname = (char*) calloc(1, MAX_DEVICE_NAME * sizeof(char));
	filtername =  (WCHAR*) calloc(1, MAX_DEVICE_NAME * sizeof(WCHAR));
	filter = 0;
}

VideoDevice::~VideoDevice()
{
	free(friendlyname);
	free(filtername);
}

const char* VideoDevice::GetFriendlyName()
{
	return friendlyname;
}



//VIDEOCAPTURE
//public
VideoCapture::VideoCapture(ICallbackHandler *cb) : num_devices(0)
{
	CoInitialize(NULL);

	playing = false;
	current = 0;
	callbackhandler = cb;
	devices = new VideoDevice[MAX_DEVICES];

	InitializeGraph();
	SetSourceFilters();
	SetSampleGrabber();
	SetNullRenderer();
}

VideoCapture::~VideoCapture()
{
	delete callbackhandler;
	delete[] devices;
}

VideoDevice* VideoCapture::GetDevices()
{
	return devices;
}
unsigned int VideoCapture::getHeight() 
{ 	
	AM_MEDIA_TYPE mt;
	samplegrabber->GetConnectedMediaType(&mt);
	VIDEOINFOHEADER* pInfo = (VIDEOINFOHEADER*)mt.pbFormat;
	return pInfo->bmiHeader.biHeight;
}
unsigned int VideoCapture::getWidth()
{ 
	AM_MEDIA_TYPE mt;
	samplegrabber->GetConnectedMediaType(&mt);
	VIDEOINFOHEADER* pInfo = (VIDEOINFOHEADER*)mt.pbFormat;
	return pInfo->bmiHeader.biWidth;
}
int VideoCapture::NumDevices()
{
	return num_devices;
}

void VideoCapture::Select(VideoDevice* dev)
{
	HRESULT hr;
	LONGLONG start=MAXLONGLONG, stop=MAXLONGLONG;
	bool was_playing = playing;

	if (!dev->filter) throw E_INVALIDARG;

	//temporary stop
	if (playing) Stop();

	if (current)
	{
		//remove and add the filters to force disconnect of pins
		graph->RemoveFilter(current->filter);
		graph->RemoveFilter(samplegrabberfilter);

		graph->AddFilter(samplegrabberfilter,L"Sample Grabber");
		graph->AddFilter(current->filter, current->filtername);
	}

	start = 0;
	current = dev;

	//connect graph with current source filter
#ifdef SHOW_DEBUG_RENDERER
	hr = capture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, current->filter, samplegrabberfilter, NULL);
#else
	hr = capture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, current->filter, samplegrabberfilter, nullrenderer);
#endif
	if (hr != S_OK) throw hr;

	//start streaming
	hr = capture->ControlStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, current->filter, &start, &stop, 1,2);
	if (hr < 0) throw hr;

	//restart
	if (was_playing) Start();
}

void VideoCapture::Start()
{
	HRESULT hr;

	hr = control->Run();
	if (hr < 0) throw hr;

	playing = true;
}

void VideoCapture::Stop()
{
	HRESULT hr;

	hr = control->StopWhenReady();
	if (hr < 0) throw hr;

	playing = false;
}

//protected
void VideoCapture::InitializeGraph()
{
	HRESULT hr;

	//create the FilterGraph
	hr = CoCreateInstance(CLSID_FilterGraph,NULL,CLSCTX_INPROC_SERVER,IID_IFilterGraph2,(void**) &graph);
	if (hr < 0) throw hr; 

	//create the CaptureGraphBuilder
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2,NULL,CLSCTX_INPROC_SERVER,IID_ICaptureGraphBuilder2,(void**) &capture);
	if (hr < 0) throw hr;

	//get the controller for the graph
	hr = graph->QueryInterface(IID_IMediaControl, (void**) &control);
	if (hr < 0) throw hr;

	capture->SetFiltergraph(graph);
}

void VideoCapture::SetSourceFilters()
{
	// Create the System Device Enumerator.
	HRESULT hr;
	ICreateDevEnum *pSysDevEnum = NULL;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void **)&pSysDevEnum);
	if (FAILED(hr))
		throw(hr);

	// Obtain a class enumerator for the video compressor category.
	IEnumMoniker *pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,
		&pEnumCat, 0);

	if (hr == S_OK) {
		// Enumerate the monikers.
		IMoniker *pMoniker = NULL;
		num_devices = 0;
		ULONG cFetched;
		while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK) {
			IPropertyBag *pPropBag;
			hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
			if (SUCCEEDED(hr)) {
				// To retrieve the filter's friendly name, do the following:
				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"FriendlyName", &varName, 0);
				if (SUCCEEDED(hr)) {

					//Initialize the VideoDevice struct
					VideoDevice* dev = &(devices[num_devices++]);
					BSTR ptr = varName.bstrVal;

					for (int c = 0; *ptr; c++, ptr++) {
						//bit hacky, but i don't like to include ATL
						dev->filtername[c] = *ptr;
						dev->friendlyname[c] = *ptr & 0xFF;
					}

					//add a filter for the device
					hr = graph->AddSourceFilterForMoniker(pMoniker, 0, dev->filtername,
						&dev->filter);
					if (hr != S_OK && hr != VFW_S_DUPLICATE_NAME)
						num_devices--;
				}
				VariantClear(&varName);
				pPropBag->Release();
			}
			pMoniker->Release();
		}
		pEnumCat->Release();
	}
	pSysDevEnum->Release();
}

void VideoCapture::SetSampleGrabber()
{
	HRESULT hr;

	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,IID_IBaseFilter,(void**)&samplegrabberfilter);
	if (hr < 0) throw hr;

	hr = graph->AddFilter(samplegrabberfilter, L"Sample Grabber");
	if (hr != S_OK) throw hr;

	hr = samplegrabberfilter->QueryInterface(IID_ISampleGrabber, (void**)&samplegrabber);
	if (hr != S_OK) throw hr;

	//set the media type
	AM_MEDIA_TYPE mt;
	memset(&mt, 0, sizeof(AM_MEDIA_TYPE));

	mt.majortype	= MEDIATYPE_Video;
	mt.subtype		= MEDIASUBTYPE_RGB24; 
	// setting the above to 32 bits fails consecutive Select for some reason
	// and only sends one single callback (flush from previous one ???)
	// must be deeper problem. 24 bpp seems to work fine for now.

	callbackhandler->SetMediaType(&mt);
	hr = samplegrabber->SetMediaType(&mt);
	if (hr != S_OK) throw hr;

	samplegrabber->SetCallback(callbackhandler,0);
}

void VideoCapture::SetNullRenderer()
{
	HRESULT hr;

	hr = CoCreateInstance(CLSID_NullRenderer,NULL,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(void**) &nullrenderer);
	if (hr < 0) throw hr; 

	graph->AddFilter(nullrenderer, L"Null Renderer");
}



