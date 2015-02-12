#ifndef __MLUA_THREAD_H__
#define __MLUA_THREAD_H__

#include "MLuaCommon.h"
#include "MLuaRefCount.h"

#if defined(__OSX__)
#include "pthread.h"
typedef pthread_mutex_t mlua_mutex_t;
#endif

namespace MLua {
    class Mutex : public IAtomicOpt
    {
    public:
        Mutex() {
#if defined (__OSX__)
            pthread_mutexattr_t attr;
            if (pthread_mutexattr_init(&attr))
                abort();
            if (pthread_mutex_init(&m_mutex, &attr))
                abort();
            pthread_mutexattr_destroy( &attr );
#endif
        }
        ~Mutex() {
#if defined (__OSX__)
            pthread_mutex_destroy( &m_mutex );
#endif
        }
        
    public:
        virtual void Enter() {
#if defined (__OSX__)
            pthread_mutex_lock( &m_mutex );
#endif
        }
        virtual void Leave()  {
#if defined (__OSX__)
            pthread_mutex_unlock(&m_mutex);
#endif
        }
        
    private:
        mlua_mutex_t m_mutex;
    };
}
#endif//__MLUA_THREAD_H__