#include<iostream>
#include<thread>
#include<mutex>
#include<windows.h>

using namespace std;
mutex m;

void shared_print(string s, int id)
{
    m.lock();
    cout<<s<<id<<endl;
    m.unlock();
    // Sleep(5);
}

void tfunc()
{
    for(int i=0;i>-10;--i)
    {
        shared_print(string("print from THREAD "),i);
    }
}

int main()
{
    thread t1(tfunc);
    for(int i=0;i<10;++i)
    {
        shared_print(string("print from MAIN "),i);
    }
    t1.join();
}