/** @file jake_platform.h
*	This file #includes various platform specific headers, and defines
*	a few simple macros to avoid more #ifdefs elsewhere in the code 
*
*	Copyright (c) 2006-2009, University of Glasgow
*	All rights reserved.
*
*	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
*
*		* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
*		* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
*			in the documentation and/or other materials provided with the distribution.
*		* Neither the name of the University of Glasgow nor the names of its contributors may be used to endorse or promote products derived 
*			from this software without specific prior written permission.
*
*	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
*	THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
*	BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
*	GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
*	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _JAKE_PLATFORM_H_
#define _JAKE_PLATFORM_H_

/* Windows DLL import/export stuff. The JAKE_API macro evals to nothing on other
*	platforms */
#ifdef _WIN32

/* only the implementation file for the driver should define JAKE_DRIVER_IMPL */
#ifndef JAKE_DRIVER_IMPL
#define JAKE_API __declspec(dllimport)
#else
#define JAKE_API __declspec(dllexport)

#endif	/* _WIN32 */

#else
#define JAKE_API 
#endif

#ifdef _WIN32 
/*	Windows headers */

/* these #defines cut down on the extra headers included from windows.h */
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <tchar.h>
#include <wchar.h>

#define jake_sleep(x) Sleep(x)

#define JAKE_CALLBACK __cdecl
#define JAKE_STDCALL_CALLBACK __stdcall

#define JAKE_INT64 __int64

#ifdef __cplusplus
extern "C" {
	/**	This is a utility function for Windows systems (2K/XP and CE), which searches the registry
	*	and retrieves the Bluetooth COM port numbers currently configured for outgoing connections.
	*	@param ports should be the address of an uninitialised int pointer. If the function succeeds,
	*	it will be updated to point to an array of at most 20 COM port numbers. 
	*	@param portcount will be updated to contain the number of valid entries in the \a ports array.
	*	@return 1 on success, -1 on error. */
	JAKE_API int jake_scan_for_comm_ports(int** ports, int* portcount);
}
#endif

#else

/* Linux headers */
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#ifndef __APPLE__
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#endif
#include <ctype.h>

#define DWORD unsigned int
#define BOOL int
#define TRUE 1
#define FALSE 0
#define TCHAR char
#define SOCKET_ERROR -1

#define jake_sleep(x) usleep(x*1000)

#define JAKE_CALLBACK

#ifdef JAKE_DEBUGGING
#define JAKE_DBG printf
#else
#define JAKE_DBG(...) //
#endif

#define JAKE_INT64 long long

#endif /* _WIN32 */

#endif
