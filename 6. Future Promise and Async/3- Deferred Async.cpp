#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

/*
    Deferred async: Run the function only when the future.get() is used
    NOTE: 
        -> when future<int> fu = async(factorial,4) is used, it actually means
                                 async(launch::async | launch::deferred, factorial, 4)
        -> the first param launch::async tells program to create a THREAD. If not given, will execute in same thread, Doesn't create NEW
        -> the second param launch::deferred tells program to CREATE THREAD ONLY when the "fu.get()" is CALLED

*/


#include<future>    // new include

using namespace std;

int factorial(int N)
{
    int ans=1;
    while(N>1)
    {
        ans*=N;
        --N;
    }
    cout<<"answer is: "<<ans<<endl;
    return ans;
}

int main()
{
    // thread t1(factorial,4);      no need to create a thread object
    future<int> fu = async(launch::deferred, factorial,4);      // doesn't create new thread
    int x = fu.get();   // waits until child finished. Can be called only once!!!
                       
    
    cout<<"Value returned is :"<<x<<endl;
    return 0;
}