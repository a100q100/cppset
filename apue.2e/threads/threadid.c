#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void
printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
	  (unsigned int)tid, (unsigned int)tid);
}

void *
thr_fn(void *arg)
{
	printids("new thread: ");
	printf("in thr_fn new thread is %d\n",ntid);
//	return((void *)5);
	pthread_exit((void *)2);
}

int
main(void)
{
	int		err;
	void *rval_ptr;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	printf("err is %d\n",err);
	if (err != 0)
		printf("can't create thread: %s\n", strerror(err));
	printids("main thread:");
	printf ("main new thread is %d\n",ntid);
	err = pthread_join(ntid, &rval_ptr);
	printf("rcal_ptr is %d\n",(int)rval_ptr);
	sleep(100);
	exit(0);
}
