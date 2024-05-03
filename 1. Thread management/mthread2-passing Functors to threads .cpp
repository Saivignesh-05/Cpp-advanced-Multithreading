#include<iostream>
#include<thread>

using namespace std;
// Exercise 3:
/*
Main is executing something. The thread prints randomly in the middle of the main thread prints
*/
void myFunc()
{
    cout<<"Hello, Iam a thread"<<endl;
}


// int main()
// {
//     thread t1(myFunc);

//     for(int i=0;i<10;++i)
//     {
//         cout<<"message from main "<<i<<endl;
//     }
//     t1.join();
//     return 0;
// }

// Exercise 4
/*
    What if main exits before the thread
    For example, the parent throws some error, thus exiting the program
*/

// solution 1
// int main()
// {
//     thread t(myFunc);
//     try
//     {
//         for(int i=0;i<10;++i)
//         {
//             cout<<"message from main "<<i<<endl;
//         }
//     }
//     catch(...)  // ... means any exception is caught
//     {
//         t.join();  // main waits for thread to join ALWAYS
//         throw;
//     }
//     t.join();       // if main executes properly
    
// }

// solution 2
class F{
    public:
        void operator()()
        {
            for(int i=0;i>-10;--i)
            {
                cout<<"printing from thread "<<i<<endl;
            }
        }
};

int main()
{
    F functor;
    thread t(functor);      // PARAMETER: pointer to another function 
    // thread t1(F())       // This throws error, Cannot create functor on the fly
                            // READ ABOUT MOST VEXING PARSE
                            // The C++ grammar is not able to distinguish if it is creation of object OR Function

    thread t1((F()));       // Adding additional () makes it parse as a FUNCTOR!
    for(int i=0;i<10;++i)
    {
        cout<<"message from main "<<i<<endl;
    }

    t.join();
    t1.join();
    return 0;

}

