#if !WIN_POC
#include "tantrix_thread.h"
#include <pthread.h>

static pthread_t handle;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void 
tanthread_lock(void)
{
  pthread_mutex_unlock(&mutex);
}

void 
tanthread_unlock(void)
{
    pthread_mutex_lock(&mutex); 
}

void 
tansleep(int mic)
{
    usleep(mic);
}

void 
tanthread_create(void * (*callback)(void *), void * arg)
{
  pthread_create(&handle, NULL, callback, arg);
}


void 
tanthread_cancel()
{
  pthread_cancel(handle);
}

void 
tanthread_join()
{
  pthread_join(handle, NULL);
}


#endif
