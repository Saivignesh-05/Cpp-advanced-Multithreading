#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>
#include<future>
#include<functional>
/*
    A package of tasks that can be transported to different places in the program

    It is a template class that is parameterized with the func signature of the task
    *Available in #include<future>
    -> it is alternative of promise??

    Bind allows callable object to be bound with its parameters


*/

using namespace std;

int factorial(int N, int m)
{
    int ans=1;
    while(N>1)
    {
        ans*=N;
        --N;
    }
    cout<<"answer is: "<<ans<<endl;
    cout<<"simply extra number: "<<m<<endl;
    return ans;
}

int main()
{
    //type 1
    packaged_task<int(int,int)> pt(factorial);      //<return_type(parameter_type)>
    pt(6,5);  // NOTE: This returns 'void' type

    //type 2
    packaged_task<int()> pt1(bind(factorial,6));   // bind function is in <functional> header file
    pt1();

    int x = pt.get_future().get();  // Gets the Actual return value
}