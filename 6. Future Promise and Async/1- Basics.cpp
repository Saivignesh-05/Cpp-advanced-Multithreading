#include<iostream>
#include<thread>
#include<mutex>
#include<windows.h>
#include<string>
#include<fstream>

using namespace std;

void factorial(int N)
{
    int ans=1;
    while(N>1)
    {
        ans*=N;
        --N;
    }
    cout<<"answer is: "<<ans<<endl;
}

int main()
{
    thread t1(factorial,4);
    t1.join();
    return 0;
}