#include <qevent.h>
#include <QMessageBox>
#include <qmenu.h>
#include <qpixmap.h>
#include <qdir.h>
#include <qinputdialog.h>
#include <qdesktopservices.h>
#include <qurl.h>

#include "ichannel.h"
#include "iencoder.h"
#include "gui_main.h"
#include "source.h"
#include "gui_surface_settings.h"
#include "plugin.h"
#include "settings.h"

MlsMain::MlsMain(QWidget *parent, Qt::WindowFlags flags) :
		QMainWindow(parent, flags)
{
	ui.setupUi(this);

	view = new GLRenderWidget(this);
	view->initialize((QWidget*) view);
	view->move(10, 40);
	view->show();

	QObject::connect(ui.list_scenes, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(onScenePressed(QListWidgetItem *)));
	QObject::connect(ui.list_sources, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(onSourcePressed(QListWidgetItem *)));
    QObject::connect(static_cast<GLRenderWidget*>(view), SIGNAL(frameReadyAll(unsigned char *, unsigned char *, unsigned char *, uint, uint)), this, SLOT(onOpenGLRenderComplete(unsigned char *, unsigned char *, unsigned char *, uint, uint)));
    QObject::connect(static_cast<GLRenderWidget*>(view), SIGNAL(surfaceSelected(string)), this, SLOT(onSelectSource(string)));
	QObject::connect(static_cast<GLRenderWidget*>(view), SIGNAL(surfaceAdd(string)), this, SLOT(onAddSource(string)));
    QObject::connect(static_cast<GLRenderWidget*>(view), SIGNAL(surfaceDel(string)), this, SLOT(onDeleteSource(string)));

	initMenu();
}

void MlsMain::onOpenGLRenderComplete(unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, uint width, uint height)
{
	//ui.render_space->setPixmap(QPixmap::fromImage(QImage(data, width, height, QImage::Format_RGB888).mirrored(false, true)));
    emit onFrameReady(yuv_y, yuv_u, yuv_v, width, height);
}

//------------GUI_UPDATE--------------------

void MlsMain::updateMain(GUIUpdate update_type)
{
    switch (update_type)
    {
    case GUIUpdate::BROADCASTS:
        updateBroadcasts();
        break;
    case GUIUpdate::RESOLUTIONS:
        updateResolutions();
        break;
    case GUIUpdate::CONFIG://TODO: GENERAL CONFIG UPDATE
        break;
    case GUIUpdate::SCENES:
        updateScenes();
        break;
    case GUIUpdate::WINDOW_SIZE:
        updateSize();
        break;
    case GUIUpdate::FPS:
        updateFPS();
        break;
    case GUIUpdate::SCALE:
        updateScale();
        break;
    case GUIUpdate::PLUGINS:
        updatePlugins();
        break;
    case GUIUpdate::TRANSLATIONS:
        updateTranslations();
        break;
    case GUIUpdate::ALL:
        updateBroadcasts();
        updateResolutions();
        updateScenes();
        updateSize();
        updateFPS();
        updateScale();
        updatePlugins();
        updateTranslations();
        break;
    default:
        traceerr("Unknown update request");
        break;
    }
}

void MlsMain::updateSize()
{
    QSqlRecord current_scale = settings->query("SELECT scale FROM scale WHERE name in (SELECT value FROM property WHERE name = 'scale')").record();
    QSqlRecord current_resolution = settings->query("SELECT width, height FROM resolution WHERE name in (SELECT value FROM property WHERE name = 'resolution')").record();
    view->setScale(current_scale.value("scale").toUInt());
    this->resize(current_resolution.value("width").toUInt() * current_scale.value("scale").toUInt() * 0.01f + 180,
            current_resolution.value("height").toUInt() * current_scale.value("scale").toUInt() * 0.01f + 200);
    view->setSize(current_resolution.value("width").toUInt(), current_resolution.value("height").toUInt());
}

void MlsMain::updateTranslations()
{
    QDir plugin_path("./translations/");
    QStringList tr_files = plugin_path.entryList(QStringList() << "*.qm", QDir::Files);

    QSqlRecord current_language = settings->query("SELECT value as name FROM property WHERE name = 'language'").record();
    QMenu *lang_menu = getMenu("Language");
    lang_menu->clear();
    for(unsigned int i = 0; i < tr_files.size(); ++i)
    {
        QString tr_file = tr_files[i].remove(".qm");
        QAction *act = regMenuAction(lang_menu, tr_file, SLOT(clickLanguageChange()));
        act->setCheckable(true);
        if(current_language.value("name") == tr_file)
        {
            act->setChecked(true);
        }
    }
}

void MlsMain::updatePlugins() //windows only
{
    QSqlRecord plugin_path_rec = settings->query("SELECT value as plugin_path FROM property WHERE name = 'plugin_path'").record();
    string plugin_path_str = plugin_path_rec.value("plugin_path").toString().toStdString();
    traceerr("loading plugins from %s", plugin_path_str.c_str());
    QDir plugin_path(plugin_path_str.c_str());
    QStringList plugin_files = plugin_path.entryList(QStringList() << "*.dll", QDir::Files);

    PluginManager::unloadAll();
    for (int i = 0; i < plugin_files.size(); ++i)
    {
        string full_path = plugin_path_str + "/" + plugin_files[i].toStdString();
        PluginManager::loadPlugin(full_path);
    }

    menu["Add source..."]->clear();
    vector<string> cap_plugins = SrcManager::getCapturePlugins();
    for (unsigned int i = 0; i < cap_plugins.size(); ++i)
    {
        QMenu *cam_list = regMenu(getMenu("Add source..."), cap_plugins[i].c_str(), cap_plugins[i].c_str());
        ICapture* capture = SrcManager::createCapture(cap_plugins[i]);
        vector<string> capture_devices = capture->listDevices();
        if (capture_devices.size() == 0)
        {
            regMenuAction(cam_list, "No capture devices found", SLOT(noCaptureDevices()));
        }
        else
        {
            for (uint i = 0; i < capture_devices.size(); ++i)
            {
                regMenuAction(cam_list, capture_devices[i].c_str(), SLOT(clickFileAddCamera()));
            }
        }
        delete capture;
    }
}

void MlsMain::updateBroadcasts()
{
	getMenu(ui.Broadcast)->clear();
	QSqlQuery channels_result = settings->query("SELECT name FROM channel");
	do
	{
		QSqlRecord channel = channels_result.record();
        QAction *act = regMenuAction(getMenu(ui.Broadcast), channel.value("name").toString(), SLOT(onChannelAction()));
		act->setCheckable(true);
	} while (channels_result.next());
    regMenuSeporator(getMenu(ui.Broadcast));
    regMenuAction(getMenu(ui.Broadcast), "Edit...", SLOT(clickChannelsEdit()));
}

void MlsMain::updateFPS()
{
    QMenu *fps_menu = getMenu("Frame rate");
    fps_menu->clear();
    QSqlQuery fps_result = settings->query("SELECT name FROM fps WHERE enabled != 0");
    QSqlRecord current_fps = settings->query("SELECT value FROM property WHERE name = 'fps'").record();
    do
    {
        QSqlRecord fps = fps_result.record();
        QAction *act = regMenuAction(fps_menu, fps.value("name").toString(), SLOT(clickChangeFrameRate()));
        act->setCheckable(true);
        if (current_fps.value("value").toString() == fps.value("name").toString())
        {
            act->setChecked(true);
        }
        else
        {
            act->setChecked(false);
        }
    } while (fps_result.next());
}

void MlsMain::updateScale()
{
    QMenu *scale_viewport_menu = getMenu("Scale");
    scale_viewport_menu->clear();
    QSqlQuery scale_result = settings->query("SELECT name FROM scale WHERE enabled != 0");
    QSqlRecord current_scale = settings->query("SELECT value FROM property WHERE name = 'scale'").record();
    do
    {
        QSqlRecord scale = scale_result.record();
        QAction *act = regMenuAction(scale_viewport_menu, scale.value("name").toString(), SLOT(clickChangeScaleViewport()));
        act->setCheckable(true);
        if (current_scale.value("value").toString() == scale.value("name").toString())
        {
            act->setChecked(true);
        }
        else
        {
            act->setChecked(false);
        }
    } while (scale_result.next());
}

void MlsMain::updateResolutions()
{
    QMenu *resolutions_menu = getMenu("Resolution");
    resolutions_menu->clear();
	QSqlRecord current_resolution = settings->query("SELECT value FROM property WHERE name = 'resolution'").record();
	QSqlQuery result = settings->query(GET_RESOLUTION, GET_ALL);
	do
	{
		QSqlRecord resolution = result.record();
		if (resolution.value("enabled").toBool())
		{
            QAction *act = regMenuAction(resolutions_menu, resolution.value("name").toString(), SLOT(clickResolutionChoose()));
			act->setCheckable(true);
			if (current_resolution.value("value").toString() == resolution.value("name").toString())
            {
				act->setChecked(true);
            }
			else
            {
                act->setChecked(false);
            }
		}
	} while (result.next());
}

//-----------------MENU----------------------------

void MlsMain::initMenu()
{
    QMenu *add_source_menu = regMenu("Add source...", tr("Add source..."));

    //SCENE POPUP MENU
    ui.list_scenes->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui.list_scenes, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onSceneContextMenuRequested(const QPoint &)));

    regMenu("list_scenes_context", "list_scenes_context");
    regMenu("list_scenes_actions", "list_scenes_actions");

    regMenuAction(getMenu("list_scenes_context"), tr("Create"), SLOT(onSceneCreate()));
    regMenuAction(getMenu("list_scenes_actions"), tr("Create"), SLOT(onSceneCreate()));
    regMenuAction(getMenu("list_scenes_actions"), tr("Delete"), SLOT(onSceneDelete()));
    regMenuAction(getMenu("list_scenes_actions"), tr("Rename"), SLOT(onSceneRename()));
    regMenuAction(getMenu("list_scenes_actions"), tr("Change background"), SLOT(onSceneSetBackground()));

    //SOURCE POPUP MENU
    ui.list_sources->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui.list_sources, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onSourceContextMenuRequested(const QPoint &)));

    regMenu("list_source_context", "list_source_context");
    regMenu("list_source_actions", "list_source_actions");
    getMenu("list_source_context")->addMenu(add_source_menu);
    getMenu("list_source_actions")->addMenu(add_source_menu);

    regMenuAction(getMenu("list_source_actions"), tr("Hide\\Show"), SLOT(onSourceHideShow()));
    regMenuAction(getMenu("list_source_actions"), tr("Remove"), SLOT(onSourceRemove()));
    regMenuAction(getMenu("list_source_actions"), tr("Settings"), SLOT(onSourceSettings()));

    //MAIN MENU BAR
    regMenu(ui.File);
    regMenu(ui.View);
    regMenu(ui.Broadcast);
    regMenu(ui.Tools);
    regMenu(ui.Help);

    ui.File->installEventFilter(this);
    ui.View->installEventFilter(this);
    ui.Broadcast->installEventFilter(this);
    ui.Tools->installEventFilter(this);
    ui.Help->installEventFilter(this);

    //FILE
    regMenuAction(getMenu(ui.File), tr("New"), SLOT(clickFileNew()));
    regMenuAction(getMenu(ui.File), tr("Save"), SLOT(clickFileSave()));
    regMenuAction(getMenu(ui.File), tr("Load"), SLOT(clickFileLoad()));
    regMenuSeporator(getMenu(ui.File));
    getMenu(ui.File)->addMenu(add_source_menu);
    regMenuSeporator(getMenu(ui.File));
    regMenuAction(getMenu(ui.File), "Exit", SLOT(clickFileExit()));

    //VIEW
    regMenu(getMenu(ui.View), "Resolution", tr("Resolution"));
    regMenu(getMenu(ui.View), "Frame rate", tr("Frame rate"));
    regMenu(getMenu(ui.View), "Scale", tr("Scale"));
    regMenu(getMenu(ui.View), "Language", tr("Language"));
    regMenuSeporator(getMenu(ui.View));
    QAction* disable_preview_action = regMenuAction(getMenu(ui.View), tr("Disable preview"), SLOT(clickDisablePreview()));
    disable_preview_action->setCheckable(true);
    disable_preview_action->setChecked(false);

    //TOOLS
    regMenuAction(getMenu(ui.Tools), tr("Activate delay..."), SLOT(clickToolsDelay()));
    regMenuAction(getMenu(ui.Tools), tr("My recordings..."), SLOT(clickToolsRecordings()));
    regMenuAction(getMenu(ui.Tools), tr("Print screen..."), SLOT(clickSaveScreenShot()));
    regMenuAction(getMenu(ui.Tools), tr("Disable advertisements..."), SLOT(clickToolsRecordings()));
    regMenuSeporator(getMenu(ui.Tools));
    regMenuAction(getMenu(ui.Tools), tr("Settings"), SLOT(clickToolsSettings()));

    //HELP
    regMenuAction(getMenu(ui.Help), tr("Contents"), SLOT(clickHelpContents()));
    regMenuSeporator(getMenu(ui.Help));
    regMenuAction(getMenu(ui.Help), tr("Forum..."), SLOT(clickHelpForum()));
    regMenuAction(getMenu(ui.Help), tr("Latest news..."), SLOT(clickHelpNews()));
    regMenuAction(getMenu(ui.Help), tr("Check for updates..."), SLOT(clickHelpUpdates()));
    regMenuSeporator(getMenu(ui.Help));
    regMenuAction(getMenu(ui.Help), tr("About"), SLOT(clickHelpAbout()));

    updateMain(GUIUpdate::ALL);
}

QMenu* MlsMain::getMenu(QPushButton *button)
{
	return menu[button->text().toStdString()];
}

QMenu* MlsMain::getMenu(string menu_name)
{
	return menu[menu_name];
}

QMenu *MlsMain::regMenu(QPushButton *button)
{
    QMenu *result = new QMenu(button->text());
    menu.insert(button->text().toStdString(), result);
    return result;
}

QMenu *MlsMain::regMenu(QString internal_name, QString tr_name)
{
    QMenu *result = new QMenu(tr_name);
    menu.insert(internal_name.toStdString(), result);
    return result;
}

QMenu *MlsMain::regMenu(QMenu *p_menu, QString internal_name, QString tr_name)
{
    QMenu *result = p_menu->addMenu(tr_name);
    menu.insert(internal_name.toStdString(), result);
	return result;
}

QAction *MlsMain::regMenuAction(QMenu *menu, QString name, const char* slot)
{
	QAction* act = new QAction(name, 0);
	act->setData(menu->title());
	menu->addAction(act);

	connect(act, SIGNAL(triggered()), slot);
	return act;
}

void MlsMain::regMenuSeporator(QMenu *menu)
{
	menu->addSeparator();
}

///--------------------MENU ACTIONS----------------------------

void MlsMain::clickLanguageChange()
{
    string new_language = ((QAction*) sender())->text().toStdString();

    settings->query("UPDATE property SET value = '%s' WHERE name = 'language'", new_language.c_str());
    QMessageBox::information(this, "Language change", "This changes will take place after restart");

    updateTranslations();
}

void MlsMain::clickDisablePreview()
{
    QAction* action = ((QAction*) sender());
    view->setPreviewVisible(!action->isChecked());
}

void MlsMain::clickChangeScaleViewport()
{
    string new_scale = ((QAction*) sender())->text().toStdString();
    settings->query("UPDATE property SET value = '%s' WHERE name = 'scale'", new_scale.c_str());

    QList<QAction*> scale_menu = getMenu("Scale")->actions();
    for (unsigned int i = 0; i < scale_menu.size(); ++i)
    {
        if (new_scale == scale_menu[i]->text().toStdString())
        {
            scale_menu[i]->setChecked(true);
        }
        else
            scale_menu[i]->setChecked(false);
    }
    updateSize();
}

void MlsMain::clickResolutionChoose()
{
    string new_resolution = ((QAction*) sender())->text().toStdString();
    settings->query("UPDATE property SET value = '%s' WHERE name = 'resolution'", new_resolution.c_str());

    QList<QAction*> resolutions_menu = getMenu("Resolution")->actions();
    for (int i = 0; i < resolutions_menu.size(); ++i)
    {
        if (new_resolution == resolutions_menu[i]->text().toStdString())
        {
            resolutions_menu[i]->setChecked(true);
        }
        else
            resolutions_menu[i]->setChecked(false);
    }
    updateSize();
}

void MlsMain::clickChangeFrameRate()
{
    string new_fps = ((QAction*) sender())->text().toStdString();
    settings->query("UPDATE property SET value = '%s' WHERE name = 'fps'", new_fps.c_str());

    QList<QAction*> fps_menu = getMenu("Frame rate")->actions();
    for (unsigned int i = 0; i < fps_menu.size(); ++i)
    {
        if (new_fps == fps_menu[i]->text().toStdString())
        {
            fps_menu[i]->setChecked(true);
        }
        else
            fps_menu[i]->setChecked(false);
    }
}

void MlsMain::clickFileNew()
{
	QMessageBox::information(this, "Not implemented", "This functionality will be implemented soon");
}

void MlsMain::clickFileSave()
{
	QMessageBox::information(this, "Not implemented", "This functionality will be implemented soon");
}

void MlsMain::clickFileLoad()
{
	QMessageBox::information(this, "Not implemented", "This functionality will be implemented soon");
}

void MlsMain::clickFileAddCamera()
{
	ASSERT_WITH_CODE(!view->getName().empty(), "Can't create surface! Select scene first!", return);

	string capture_plugin = ((QAction*) sender())->data().toString().toStdString();
	string device_name = ((QAction*) sender())->text().toStdString();
	unsigned int device_id = 0;

	ICapture* capture = SrcManager::createCapture(capture_plugin);
	vector<string> device_list = capture->listDevices();
	for (; device_id < device_list.size(); ++device_id)
	{
		if (device_list[device_id] == device_name)
			break;
	}
	capture->bind(device_id);
	ISource *source = dynamic_cast<ISource*>(capture);
	string action_name = view->createSurface(source);
}

void MlsMain::clickFileExit()
{
	this->close();
}

void MlsMain::clickEncodersEdit()
{
	MqsConfig *config = new MqsConfig(this, Qt::Dialog);
	config->setAttribute(Qt::WA_DeleteOnClose, true);
    config->activateTab(ENCODERS_TAB);
	config->show();
}

void MlsMain::onChannelAction()
{
	QAction* action = (QAction*) sender();
	string user_defined_channel_name = action->text().toStdString();

	if (action->isChecked())
    {
        ChannelManager::startBroadcast(user_defined_channel_name, this);
    }
	else
	{
        ChannelManager::stopBroadcast(user_defined_channel_name);
	}
}

void MlsMain::clickChannelsEdit()
{
	MqsConfig *config = new MqsConfig(this, Qt::Dialog);
	config->setAttribute(Qt::WA_DeleteOnClose, true);
    config->activateTab(CHANNELS_TAB);
	config->show();
}

void MlsMain::clickToolsSettings()
{
	MqsConfig *config = new MqsConfig(this, Qt::Dialog);
	config->setAttribute(Qt::WA_DeleteOnClose, true);
    config->activateTab(GENERAL_TAB);
	config->show();
}

void MlsMain::clickSaveScreenShot()
{
	view->saveScreenShot();
}

void MlsMain::clickToolsDelay()
{
	QMessageBox::information(this, "Not implemented", "This functionality will be implemented soon");
}

void MlsMain::clickToolsRecordings()
{
	QMessageBox::information(this, "Not implemented", "This functionality will be implemented soon");
}

void MlsMain::clickHelpContents()
{
	QDesktopServices::openUrl(QUrl("www.medialivesync.com/?page_id=35"));
}

void MlsMain::clickHelpForum()
{
	QDesktopServices::openUrl(QUrl("www.medialivesync.com"));
}

void MlsMain::clickHelpNews()
{
	QDesktopServices::openUrl(QUrl("www.medialivesync.com"));
}

void MlsMain::clickHelpUpdates()
{
	QDesktopServices::openUrl(QUrl("http://www.medialivesync.com/?page_id=185&lang=en"));
}

void MlsMain::clickHelpAbout()
{
	QMessageBox::about(this, "About Media Live Sync", "<h1>About</h1>"
			"<strong>Media Live Sync. Broadcasting for everyone!</strong>"
			"<pre>Version: 0.1 alfa preview</pre>"
			"<pre>Arch: Multi threaded x86 build, MinGW gcc-4.7.2 debug(SIMD)</pre>"
			"<pre>Libs: Qt framework, sqlite, libx264, libavformat, libavcodec, libavutil, libavfilter</pre>"
			"<pre>Site: <a href='http://www.medialivesync.com/'>www.medialivesync.com<br></a></pre>"
			"This program distributed absolutly free under EULA licence");
}

MlsMain::~MlsMain()
{
	PluginManager::unloadAll();
}

//-----------------------EVENTS----------------------------

bool MlsMain::eventFilter(QObject * watched, QEvent * event)
{
	QPushButton *btn = qobject_cast<QPushButton *>(watched);

	if (event->type() == QEvent::MouseButtonPress)
	{
		getMenu(btn)->exec(btn->pos() + this->pos() + QPoint(0, ui.File->size().height()));
	}
	else if (event->type() == QEvent::Enter)
	{
		for (QMap<string, QMenu*>::iterator it = menu.begin(); it != menu.end(); ++it)
		{
			if (it.value()->isActiveWindow() && it.key() != btn->text().toStdString())
			{
				it.value()->close();
				getMenu(btn)->exec(btn->pos() + this->pos() + QPoint(0, ui.File->size().height()));
			}
		}
	}
	return QObject::eventFilter(watched, event);
}

void MlsMain::mousePressEvent(QMouseEvent* event)
{
	event->accept(); // do not propagate

	if (isWindow())
		offset = event->globalPos() - pos();
	else
		offset = event->pos();
}

void MlsMain::mouseReleaseEvent(QMouseEvent* event)
{
	event->accept(); // do not propagate
	offset = QPoint();
}

void MlsMain::mouseMoveEvent(QMouseEvent* event)
{
	event->accept(); // do not propagate
	if (isWindow())
    {
		move(event->globalPos() - offset);
    }
	else
    {
		move(mapToParent(event->pos() - offset));
    }
}
