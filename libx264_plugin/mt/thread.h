#ifndef THREAD_H
#define THREAD_H

#define _MULTI_THREADED
#include <pthread.h>
#include <string>
#include "global.h"
#include <time.h>

using namespace std;

class Thread
{
public:
    Thread() {};
    virtual ~Thread() {};
    virtual void run() = 0;
    virtual void onShutdown() = 0;///it should be almost atomic. no general mutex locks 
    uint32 getTid() { return _tid; }
    void setTid(uint32 tid) { _tid = tid; }
private:
    uint32 _tid;
};

class Mutex
{
public:
    /** Initializes a mutex class, with pthread_mutex_init
     */
    Mutex();
    /** Deletes the associated mutex
     */
    virtual ~Mutex();
    inline void lock()
    {
        pthread_mutex_lock(&mutex);
    }
    inline void unlock()
    {
        pthread_mutex_unlock(&mutex);
    }
    /** @return false if cannot be lock, true if it was locked.
     */
    inline bool try_1k_lock()
    {
	unsigned int cnt = 0;
	while(pthread_mutex_trylock(&mutex))
	{
	  cnt++;
	  if(cnt > 1000)
	    return false;
	}
        return true;
    }
    inline bool try_lock()
    {
        return (pthread_mutex_trylock(&mutex) == 0);
    }
protected:
    static bool attr_initalized;
    static pthread_mutexattr_t attr;
    /** pthread struct used in system calls
     */
    pthread_mutex_t mutex;
};

template<class T>
class FQueue
{
public:
    FQueue() {
        first = last = NULL;
        size = 0;
    }
    volatile unsigned int size;

    unsigned int get_size()
    {
        lock.lock();
        unsigned int retval = size;
        lock.unlock();
        return retval;
    }

    void push(T &item)
    {
        h* p = new h;
        p->value = item;
        p->pNext = NULL;

        lock.lock();
        if (last != NULL)//have some items
        {
            last->pNext = (h*)p;
            last = p;
            ++size;
        }
        else //first item
        {
            last = first = p;
            size = 1;
        }
        lock.unlock();
    }

    T pop_nowait() {
        return pop();
    }

    T pop()
    {
        lock.lock();
        if (size == 0)
        {
            lock.unlock();
            return NULL;
        }

        h* tmp = first;
        if (tmp == NULL)
        {
            lock.unlock();
            return NULL;
        }

        if (--size) //more than 1 item
            first = (h*)first->pNext;
        else //last item
        {
            first = last = NULL;
        }

        lock.unlock();

        T returnVal = tmp->value;
        delete tmp;
        return returnVal;
    }

private:
    struct h
    {
        T value;
        void* pNext;
    };

    h * first;
    h * last;

    Mutex lock;
};

#endif // THREAD_H
