#include <mutex>
#include <stdio.h>
#include <stdlib.h>


void someFunctionMayCallExit()
{
	printf("begin exit\n");
	exit(1);
	printf("end exit\n");
}

class Lock
{
public:
	Lock(std::mutex & mutex):mutex_(mutex)
	{
		printf("create Lock\n");
		mutex_.lock();
	}
	
	~Lock()
	{
		printf("delete Lock\n");
		mutex_.unlock();
	}
private:
	std::mutex & mutex_;
};

class GlobalObject
{
public:
	void doit()
	{
		Lock t(mutex_);
		someFunctionMayCallExit();
	}

	~GlobalObject()
	{
		printf("GlobalObject:~GlobalObject\n");
		Lock t(mutex_);
		// clean up
		printf("GlobalObject:~GlobalObject cleanning\n");
	}

private:
	std::mutex mutex_;
};

__thread int t_obj = 1;

int main()
{
	GlobalObject g_obj;
	g_obj.doit();
}
