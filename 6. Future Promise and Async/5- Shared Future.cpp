#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>
#include<future>
/*
    What if I want many threads to receive the Future value set by main thread
    The Future object cannot be shared by many. Once get happens, cannot use .get() again

    -> Shared Future sends the future NOT by REFERENCE, but by VALUE.

*/


#include<future>    // new include

using namespace std;

int factorial(shared_future<int> f)
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
    shared_future<int> sf = f.share();


    future<int> fu = async(factorial,sf);
    future<int> fu1 = async(factorial,sf);
    future<int> fu2 = async(factorial,sf);
    future<int> fu3 = async(factorial,sf);
    int x = fu.get();   // waits until child finished. Can be called only once!!!
                       
    
    cout<<"Value returned is :"<<x<<endl;
    return 0;
}