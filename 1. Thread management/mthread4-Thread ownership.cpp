#include<iostream>
#include<thread>
#include<string>
using namespace std;

class F{
    public:
        void operator()(string msg)
        {
            cout<<"Thread says: "<<msg<<endl;
        }
};

int main()
{   
    string s = "My name is Vignesh";

    cout<<this_thread::get_id();

    thread t1((F()), move(s));       // to pass params, Pass it to the Thread's 2nd parameter
    cout<<t1.get_id()<<endl;
                                     // Move passes OWNERSHIP to the THREAD
                                
    // thread t2 = t1; // cannot be done. Only using move,we can pass ownership
    thread t2 = move(t1);

    // t1.join();   // t1 becomes empty, Thus join with t2!
    t2.join();
    return 0;

}

