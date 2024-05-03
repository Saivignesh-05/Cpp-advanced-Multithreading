#include<iostream>
#include<thread>

using namespace std;

//* Exercise 1
// void myFunc()
// {
//     cout<<"Hello, Iam a thread"<<endl;
// }

// int main()
// {
//     thread t1(myFunc);
//     t1.join();
    
//     return 1;
// }


// Exercise 2
// *** The main thread holds the cout object. If it ends before t1, the resource is released. 
// Thus t1 cannot print its message

// If the Thread t1 finishes before the main thread, Then we will see the message. 
// or else, it will finish after, thus MESSAGE NOT DISPLAYED!
// Usually main finished before thread since it has no job (Probabilistic)
// void myFunc()
// {
//     cout<<"Hello, Iam a thread"<<endl;
// }


// int main()
// {
//     thread t1(myFunc);
//     t1.detach();    // parent detaches from child (daemon process)
    

//     if(t1.joinable()) // Allows parent to check on status of child using pid
//     {
//         t1.join();
//     }

//     return 0;
// }


