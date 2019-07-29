/**********************************************************************/
//1. 这个演示了为什么构造函数中不能泄露this指针的原因

#include <thread>
#include <stdio.h>
#include <unistd.h>

class Test
{
public:
    Test()
    {
        printf("begin create Test\n");
        _num1 = 123;
        _td = std::thread(std::bind(&Test::run, this));
        sleep(10);
        _num2 = 346;
        printf("end create Test\n");
    }

    ~Test()
    {
        _td.join();
    }

    void run()
    {
        printf("run num1=%d, num2=%d\n", _num1, _num2);
    }

private:
    std::thread _td;
    int _num1;
    int _num2;
};

int main()
{
    Test t;

    sleep(20);
    return 0;
}
