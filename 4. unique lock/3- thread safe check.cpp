#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

using namespace std;
mutex m;

/* 
    By doing LAZY INIT, we need to check if the program is thread safe
    Before we open the file, we need to lock it. 
    This lock must be placed before the 'if clause'
    NOTE: It must be a different lock, since its purpose is different

    This way we waste lot of CPU CYCLES by locking and unlocking many times
 */   

class logging{
    mutex m;
    mutex flock;
    ofstream f; // must not be shared at any cost outside this class
public:        
    void shared_print(string s, int id)
    {
        unique_lock<mutex>l2(flock);
        if(!f.is_open())     // lazy initialization
        {
            f.open("log.txt");
        }   
        l2.unlock();

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
