#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#ifdef _WIN32 
#include <windows.h>
#endif
class ReferenceCounter
{
public:
	ReferenceCounter() : ref_count(0)
	{}
#ifdef _WIN32 
    inline bool release() { return InterlockedDecrement( (LONG*)&ref_count ); }
    inline void addRef() { InterlockedIncrement( (LONG*)&ref_count ); }
#else
	inline bool release() { return __sync_add_and_fetch( &ref_count, -1 ); };
	inline void addRef() { __sync_add_and_fetch( &ref_count, 1 ); };
#endif
	unsigned int get(){ return ref_count; }
private:
	volatile unsigned int ref_count;
};

template <typename T>
class SmartPtr
{
public:
	SmartPtr() : ptr(NULL), rc(NULL)
	{
		rc = new ReferenceCounter();
		rc->addRef();
	};
	SmartPtr(T* pValue) : ptr(pValue), rc(NULL)
	{
		rc = new ReferenceCounter();
		rc->addRef();
	}
	~SmartPtr()
	{
		if(!rc->release())
		{
			if(ptr)
				delete ptr;
			if(rc)
				delete rc;
		}
	};
	SmartPtr(const SmartPtr<T>& sp) : ptr(sp.ptr), rc(sp.rc)
	{
		rc->addRef();
	}
	SmartPtr<T>& operator = (const SmartPtr<T>& sp)
	{
		if (this != &sp)
		{
			if(!rc->release())
			{
				if(ptr)
					delete ptr;
				delete rc;
			}
			ptr = sp.ptr;
			rc = sp.rc;
			rc->addRef();
		}
		return *this;
	}

	SmartPtr<T>& operator = (const T* pointer)
	{
		if (this->ptr != pointer)
		{
			if(!rc->release())
			{
				delete ptr;
				delete rc;
			}
			ptr = pointer;
			rc->addRef();
		}
		return *this;
	}

	T* operator-> () const { return ptr; }
	T& operator*() const { return *ptr; }
private:
	T *ptr;
	ReferenceCounter *rc;
};

#endif // SMART_POINTER_H
