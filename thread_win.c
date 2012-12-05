#include <windows.h>
#include <stdio.h>
#include <process.h>
#include "tantrix_thread.h"

static CRITICAL_SECTION cs;
static HANDLE tHandle;
#if 0
static int sock;
static DWORD threadId;

static HANDLE ghMutex; 
#endif

void 
tanthread_lock(void)
{
    EnterCriticalSection( &cs ); 
}

void 
tanthread_unlock(void)
{
    LeaveCriticalSection( &cs );
}

void 
tansleep(int mic)
{
    Sleep(mic / 1000);
}

void 
tanthread_create(void * (*callback)(void *), void * arg)
{
    InitializeCriticalSection( &cs );

#if 0  
    DWORD WINAPI (*fn)(LPVOID lpParam) = (DWORD (*)(LPVOID)) callback; 
    tHandle = CreateThread(NULL, 0, fn, (LPVOID) sock, 0, &threadId);
    ghMutex = CreateMutex(NULL, FALSE, NULL);
#endif

    void (*fn)(void *lp) = (void (*)(void *)) callback;
    tHandle = (HANDLE)_beginthread(fn, 0, arg);
}


void 
tanthread_cancel(void)
{
  CloseHandle( tHandle );
}

void 
tanthread_join(void)
{
  CloseHandle( tHandle );
}
