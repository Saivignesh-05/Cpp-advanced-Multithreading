#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

using namespace std;
mutex m;

/* 
    There are three ways of locking
    1. using mutex.lock and mutex.unlock
    2. lock_guard<mutex> l(mutex)
    These two we have seen

    3. Unique_lock<mutex>(mutex)
        Similar to lock_guard, BUT FLEXIBLE
        -> Fine-grained lock
        ->Can be MOVED (transfer ownership) unlike lock_guard
    DISADVANTAGES:
        ->Complex for the C++ runner. This is "heavier" than lock_guard
 */   

class logging{
    mutex m;
    ofstream f; // must not be shared at any cost outside this class
    public:
        logging()
        {
            f.open("log.txt");
        }
        // ADVANTAGE 1: UNLOCK EARLY
        void shared_print(string s, int id)
        {
            unique_lock<mutex> lck(m);
            f<<"From "<<s<<" : "<<id<<endl;
            lck.unlock();   // allows to unlock EARLY
            //
            //
            // Post processing not linked to mutex
            //
            lck.lock(); // CAN LOCK AGAIN ANYTIME!

            unique_lock<mutex> lock2 = move(lck);
        }
    // ADVANTAGE 2: Create the lock object without locking immediately
        void shared_print(string s, int id)
        {
            unique_lock<mutex> lck(m, defer_lock);
            //
            //
            //Pre-processing
            //
            lck.lock();
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
