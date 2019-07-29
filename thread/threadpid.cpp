#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
//thread value
__thread int t_cachedTid = 0;
static int gettid()
{
    return static_cast<int>(::syscall(SYS_gettid));
}
int cacheTid()
{
    if(t_cachedTid == 0)
    {
        t_cachedTid = gettid();
    }
	
	return t_cachedTid;
}

void childfork()
{
	t_cachedTid = 0;
}

int main()
{
	printf("father, thid=%d, tid=%d,%d\n", getpid(), gettid(), cacheTid());
	pthread_atfork(NULL, NULL, childfork);
	int pid = fork();
	if(pid == 0)
	{
		printf("child, thid=%d, tid=%d,%d\n", getpid(), gettid(), cacheTid());
	}
	else
	{
		printf("father, thid=%d, tid=%d,%d\n", getpid(), gettid(), cacheTid());
	}
}
