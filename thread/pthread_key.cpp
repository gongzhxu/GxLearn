#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_key_t   key;

class Foo
{
public:
	Foo(int x): _x(x)
	{
		printf("create thid=%u, Foo=%d\n", pthread_self(), _x);
	}

	~Foo()
	{
		printf("delete thid=%u, Foo=%d\n", pthread_self(),  _x);
	}
	
	int get()
	{
		return _x;
	}
private:
	int _x;
};


void destructor(void * arg)
{
    printf("destructor thid=%u, Foo=%d\n", pthread_self(), ((Foo*)arg)->get());
	delete (Foo*)arg;
}

void * child1(void *arg)
{
	Foo * foo = new Foo(123);
	pthread_setspecific(key,(void *)foo);

	printf("thread %u returns %p and key %d\n", pthread_self(),pthread_getspecific(key), key);
}

void * child2(void *arg)
{
	Foo * foo = new Foo(456);
	pthread_setspecific(key, (void *)foo);

	printf("thread %u returns %p and key %d\n", pthread_self(), pthread_getspecific(key),key);
}

int main(void)
{
	pthread_t tid1,tid2;
	pthread_key_create(&key, destructor);
	
	pthread_create(&tid1,NULL,child1,NULL);
	pthread_create(&tid2,NULL,child2,NULL);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	pthread_key_delete(key);
	printf("main thread exit\n");
	return 0;
}