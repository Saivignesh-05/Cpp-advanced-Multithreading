#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

using namespace std;
mutex m;

/* 
    The once_flag variable
    use the call_once function
    called only once for all threads accessing this function
 */   

class logging{
    mutex m;
    once_flag flag;
    ofstream f; // must not be shared at any cost outside this class
public:        
    void shared_print(string s, int id)
    {
        call_once(flag, [&](){f.open("log.txt"); });    // provide the lambda function as parameter

        unique_lock<mutex> lck(m);
        f<<"From "<<s<<" : "<<id<<endl;
        lck.unlock();   // allows to unlock EARLY
    }
};

void tfunc(logging &lf)
{
    for(int i=0;i>-10;--i)
    {
        lf.shared_print(string("print from THREAD "),i);
    }
}

int main()
{
    logging lf;
    thread t1(tfunc, ref(lf));
    for(int i=0;i<10;++i)
    {
        lf.shared_print(string("print from MAIN "),i);
    }
    t1.join();
}
