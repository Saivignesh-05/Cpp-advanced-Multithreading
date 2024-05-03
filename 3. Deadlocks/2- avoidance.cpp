#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>
#include<windows.h>
using namespace std;
mutex m;

/* 
    the std::lock provides locking mechanism for N number of locks
    It uses Ddlk avoidance mechanism to ensure it is DEADLOCK FREE always!

    USE THIS WHEN MULTIPLE LOCKS MUST BE TAKEN 
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
            lock(m1,m2);    // this func allows locking arbitrary no. of lockable objs using some deadlock avoidance mechanisms
            lock_guard<mutex> lck(m1, adopt_lock);       // after m1 is locked, ADOPT OWNERSHIP OF THAT MUTEX. Thus when it goes out of scope, IT RELEASES it.
            lock_guard<mutex> lck2(m2, adopt_lock);
            f<<"From "<<s<<" : "<<id<<endl;
        }
        void shared_print_2(string s, int id)
        {
            lock_guard<mutex> lck2(m2,adopt_lock);     // locks m2 first
            Sleep(10);                      // since main thread is faster, I'm using sleep
            lock_guard<mutex> lck(m1, adopt_lock);
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
        lock in the same order in all functions. (OR HEIRARCHY ORDER)
        This allows FCFS, atleast one finishes first
    SOLUTION 2:
        If possible lock one by one, instead of locking all. 
        Locking required resources avoids the unnecessary stalling
    SOLUTION 3:
        Avoid calling USER defined functions after locking

*/


/****
 * COURSE GRAINED LOCKS: LOCKS HUGE NUMBER OF RESOURCES, 
 * Disadvantage: Decreases the CONCURRENCY of Threads
****/

/****
 * FINE GRAINED LOCKS: LOCKS very small no. of Resources, 
 * Disadvantage: Increases complexity of code and Deadlock occurences
****/