#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>
#include<future>

using namespace std;

class A
{
public:
    void f(int x, char c)
    {

    }
    long g(double x)
    {return 0;}
    int operator()(int N)       // indicated class A is a functor
    {
        return 0;
    }
};

int main()
{
    A a;    // This is a callable object
    
    //* The different ways threads can be created using Callable object
//1. 
    thread t1(a,6);
    async(launch::async,a,6);
    bind(a,6);
    call_once(once_flag,a,6);
    return 0;
}