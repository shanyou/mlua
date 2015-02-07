#ifndef __MLUA_COMMON_H__
#define __MLUA_COMMON_H__

#include <stdint.h>
#ifndef BASETYPES
	#define BASETYPES
	typedef unsigned long ULONG;
	typedef ULONG *PULONG;
	typedef unsigned short USHORT;
	typedef USHORT *PUSHORT;
	typedef unsigned char UCHAR;
	typedef UCHAR *PUCHAR;
	typedef char *PSZ;
	typedef wchar_t WCHAR;
	typedef const WCHAR *LPCWSTR, *PCWSTR;

	typedef int                 INT;
	typedef unsigned int        UINT;
	typedef unsigned int        *PUINT;
#endif  /* !BASETYPES */

#ifndef VOID
	#define VOID void
	typedef char CHAR;
	typedef short SHORT;
	typedef long LONG;
	typedef	void* PVOID;

	typedef unsigned long       DWORD;
//	typedef int                 BOOL;
	typedef unsigned char       BYTE;
	typedef unsigned short      WORD;
	typedef float               FLOAT;

	typedef BYTE				*LPBYTE;
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE  0
#endif

#ifndef NULL
#define NULL  (void*)0
#endif

#if defined (__OSX__)
# include <libkern/OSAtomic.h> /* OSMemoryBarrier() */
#endif

#endif //__MLUA_COMMON_H__