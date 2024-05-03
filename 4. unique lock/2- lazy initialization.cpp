#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

using namespace std;
mutex m;

/* 
    LAZY INITIALIZATION or INIT upon FIRST USE
    -> Unlike the previous program, We dont open the file unless the Shared print is called
    -> This way, if obj is just created, Logfile is not created!
 */   

class logging{
    mutex m;
    ofstream f; // must not be shared at any cost outside this class
public:        
    void shared_print(string s, int id)
    {
        if(!f.is_open())     // lazy initialization
        {
            f.open("log.txt");
        }   
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
