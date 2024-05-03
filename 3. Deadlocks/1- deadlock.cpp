#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>
#include<windows.h>
using namespace std;
mutex m;

/* 
    Say we need two mutex to lock resources
    Shared_print_1 locks m1 first then m2
    Shared_print_2 locks m2 first then m1

    Thread t1 calls shared_print_1
    Main calls shared_print_2
 */   

class logging{
    mutex m1;
    mutex m2;
    ofstream f; // must not be shared at any cost outside this class
    public:
        logging()
        {
            f.open("log.txt");
        }
        void shared_print_1(string s, int id)
        {
            lock_guard<mutex> lck(m1);       // locks m1 first
            // Sleep(5);
            lock_guard<mutex> lck2(m2);
            f<<"From "<<s<<" : "<<id<<endl;
        }
        void shared_print_2(string s, int id)
        {
            lock_guard<mutex> lck2(m2);     // locks m2 first
            Sleep(10);                      // since main thread is faster, I'm using sleep
            lock_guard<mutex> lck(m1);
            f<<"From "<<s<<" : "<<id<<endl;
        }
};

void tfunc(logging &lf)
{
    for(int i=0;i>-10;--i)
    {
        lf.shared_print_1(string("print from THREAD "),i);
    }
}

int main()
{
    logging lf;
    thread t1(tfunc, ref(lf));
    for(int i=0;i<10;++i)
    {
        lf.shared_print_2(string("print from MAIN "),i);
    }
    t1.join();
}

/*
    SOLUTION 1:
        lock in the same order in all functions.
        This allows FCFS, atleast one finishes first
*/