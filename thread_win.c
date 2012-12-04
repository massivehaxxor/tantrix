#include <windows.h>
#include <stdio.h>
#include "tantrix_thread.h"

static int sock;
static DWORD threadId;
HANDLE tHandle;

void 
tanthread_lock(void)
{
}

void 
tanthread_unlock(void)
{
}

void 
tansleep(int mic)]
{
    Sleep(mic / 1000);
}

void 
tanthread_create(void * (*callback)(void *), void * arg)
{
    DWORD WINAPI (*fn)(LPVOID lpParam);
    
    fn = (DWORD (*)(LPVOID)) callback;
    tHandle = CreateThread(NULL, 0, fn, (LPVOID) sock, 0, &threadId);
}


void 
tanthread_cancel(void)
{
}

void 
tanthread_join(void)
{
    WaitForSingleObject(tHandle, 0);
}
