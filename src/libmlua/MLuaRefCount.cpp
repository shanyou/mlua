#include "MLuaRefCount.h"
using namespace MLua;

RefCount::RefCount()
{
    m_nRefCount = 0;
#if defined (__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    __sync_synchronize ();
#elif defined (WIN32) && defined (__GNUC__)
#elif defined(__OSX__)
    OSMemoryBarrier();
#else
    //TODO: add IAtomicOpt init
#endif
}

RefCount::~RefCount()
{
#if defined (__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
#elif defined (WIN32) && defined (__GNUC__)
#elif defined(__OSX__)
#else
    //TODO: destory IAtomicOpt
#endif
}

ULONG RefCount::AddRef()
{
    //	return InterlockedIncrement(&m_nRefCount);
    uintptr_t refs;
    
#if defined (__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    refs = __sync_add_and_fetch (&m_nRefCount, 1);
#elif defined (WIN64)
    refs = InterlockedIncrement64 (&m_nRefCount);
#elif defined (WIN32)
    refs = InterlockedIncrement ((volatile LONG*)&m_nRefCount);
#elif defined(__OSX__)
    refs = OSAtomicIncrement32Barrier((int*)&m_nRefCount);
#else
    //TODO: add IAtomicOpt increase method
#endif
    return refs;
}

ULONG RefCount::Release()
{
    ULONG refs;
    
#if defined (__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    refs = __sync_sub_and_fetch (&m_nRefCount, 1);
#elif defined (WIN64)
    refs = InterlockedDecrement64 (&m_nRefCount);
#elif defined (WIN32)
    refs = InterlockedDecrement ((volatile LONG*)&m_nRefCount);
#elif defined(__OSX__)
    refs = OSAtomicDecrement32Barrier((int*)&m_nRefCount);
#else
    //TODO: add IAtomicOpt decrease method
#endif
    
    if (refs < 1)
    {
        delete this;
    }
    
    return refs;
}