#ifndef __TANTRIX_THREAD_H
#define __TANTRIX_THREAD_H

void tanthread_lock(void);
void tanthread_unlock(void);
void tansleep(int mil);
void tanthread_create(void * (*func)(void *), void * arg);
void tanthread_cancel(void);
void tanthread_join(void);

#endif

