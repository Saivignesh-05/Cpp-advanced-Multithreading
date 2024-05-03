#include<iostream>
#include<thread>
#include<string>
using namespace std;

// A PARAMETER TO THREAD is always passed "BY VALUE"

// passing parameters to the FUNCTORS
class F{
    public:
        void operator()(string &msg) // string &msg will throw ERROR
        {
            cout<<"Thread says: "<<msg<<endl;
            msg = "Thread changed to this";
        }
};

int main()
{   
    string s = "My name is Vignesh";

    thread t1((F()), ref(s));       // to pass params, Pass it to the Thread's 2nd parameter
                                     // Move passes OWNERSHIP to the THREAD
                                     // now main cannot print the string s !!
                                

    t1.join();
    cout<<"Changed string s: "<<s<<endl;
    return 0;

}

