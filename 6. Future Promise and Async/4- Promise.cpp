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
    -> FUTURE and PROMISE can be moved, not copied

*/


#include<future>    // new include

using namespace std;

int factorial(future<int> &f)
{
    int ans=1;

    int N = f.get();
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
    promise<int> p;
    future<int> f = p.get_future();

    future<int> fu = async(launch::deferred, factorial,ref(f));      // doesn't create new thread
    int x = fu.get();   // waits until child finished. Can be called only once!!!
    cout<<"Value returned is :"<<x<<endl;
                       
    // do some functioning. By this time the value of promise is EMPTY!
    this_thread::sleep_for(chrono::milliseconds(10));
    p.set_value(4); // Now the value came. This will trigger async

    //p.set_exception(make_exception_ptr(runtime_error("Sorry didnt get value")));
        // If the promise value is not given, The Thread executing get will receive this error


    return 0;
}