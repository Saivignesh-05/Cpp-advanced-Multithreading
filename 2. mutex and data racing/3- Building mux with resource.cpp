#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

using namespace std;
mutex m;

/* 
    Lock_Guard is great, BUT what if the Resource is GLOBAL!
    Anyone can still access it

    Thus we need to BUNDLE Resource with MUTEX
 */   

class logging{
    mutex m;
    ofstream f; // must not be shared at any cost outside this class
    public:
        logging()
        {
            f.open("log.txt");
        }
        void shared_print(string s, int id)
        {
            lock_guard<mutex> lck(m);
            f<<"From "<<s<<" : "<<id<<endl;
        }

        /*
        MISTAKE 1: Never return 'f' resource outside scope
        ofstream &getstream()
        {
            return f;   // f gets exposed
        }
        */
       /*
       MISTAKE 2: Never pass f as ARGUMENT to another function
       void processMyFstream(void func (ofstream&))
       {
            fun(f);
       }
       */
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
