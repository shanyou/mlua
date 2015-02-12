#ifndef __MLUA_REFCOUNT_H__
#define __MLUA_REFCOUNT_H__


#include "MLuaCommon.h"

namespace MLua
{
    
    class RefCount
    {
    public:
        RefCount();
        
        virtual ULONG AddRef(void);
        virtual ULONG Release(void);
        
    protected:
        virtual ~RefCount();
        
    protected:
        IAtomicOpt*     mLock;
        uintptr_t       m_nRefCount;
    };
    
    template <class T> class CRefPtr
    {
    public:
        CRefPtr(T* ptr = NULL)
        {
            m_ptr = ptr;
            if (m_ptr != NULL)
                m_ptr->AddRef();
        }
        
        CRefPtr(const CRefPtr<T>& lp)
        {
            m_ptr = lp.m_ptr;
            if (m_ptr != NULL)
                m_ptr->AddRef();
        }
        
        ~CRefPtr()
        {
            if (m_ptr)
                m_ptr->Release();
        }
        
        void Release()
        {
            if (m_ptr)
                m_ptr->Release();
            m_ptr = NULL;
        }
        
        operator T*() const throw()	{return m_ptr;}
        T& operator*() const throw() {/*ASSERT(m_ptr!=NULL);*/ return *m_ptr; }
        T** operator&()	{ return (T**)&m_ptr;}
        T* operator->() const throw() {return m_ptr;}
        bool operator!() {return (m_ptr == NULL);}
        
        T* operator=(T* ptr)
        {
            if (ptr)
                ptr->AddRef();
            
            T* old = m_ptr;
            m_ptr = ptr;
            
            if (old)
                old->Release();
            return m_ptr;
        }
        
        T* operator=(const CRefPtr<T>& lp)
        {
            T* p = lp.m_ptr;
            
            if (p)
                p->AddRef();
            
            T* old = m_ptr;
            m_ptr = p;
            
            if (old)
                old->Release();
            return m_ptr;
        }
        
    protected:
        T*	volatile m_ptr;
    };

};


#endif //__MLUA_REFCOUNT_H__