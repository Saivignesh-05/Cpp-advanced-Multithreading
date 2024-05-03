#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

/*
    What if I want the Thread to Return to the Parent
    Then we have to use Condition variables and send reference variable from main to function

    But there is a simpler way
    -> async is a function which creates another Thread
    -> send which func to be run to async
    
    -> The future class allows values to be got in the future

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
    future<int> fu = async(factorial,4);
    int x = fu.get();   // waits until child finished. Can be called only once!!!
                       
    
    cout<<"Value returned is :"<<x<<endl;
    return 0;
}