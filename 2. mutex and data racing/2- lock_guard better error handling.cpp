#include<iostream>
#include<thread>
#include<mutex>
#include<windows.h>

using namespace std;
mutex m;

/* 
    What if the Thread locked mutex, recieved ERROR, EXITED!
    The lock is stuck, no one can unlock

    Therefore use lock_guard

    Upon construction, LOCKS mutex, keeps a REFERENCE to it.
    Upon destruction (i.e. when the guard's scope is left), it unlocks

    the lock_guard object gets destroyed automatically whenever the
    function is exited – ** regardless how it is exited **
 */   

void shared_print(string s, int id)
{
    lock_guard<mutex> guard(m);
    cout<<s<<id<<endl;
    
}

void tfunc()
{
    for(int i=0;i>-10;--i)
    {
        shared_print(string("print from THREAD "),i);
    }
}

int main()
{
    thread t1(tfunc);
    for(int i=0;i<10;++i)
    {
        shared_print(string("print from MAIN "),i);
    }
    t1.join();
}




// #include <iostream>
// #include <thread>
// #include <list>
// #include <algorithm>
// #include <mutex>

// using namespace std;

// // a global variable
// std::list<int>myList;

// // a global instance of std::mutex to protect global variable
// std::mutex myMutex;

// void addToList(int max, int interval)
// {
//     // the access to this function is mutually exclusive
//     std::lock_guard<std::mutex> guard(myMutex);
//     for (int i = 0; i < max; i++) {
//         if( (i % interval) == 0) myList.push_back(i);
//     }
// }

// void printList()
// {
//     // the access to this function is mutually exclusive
//     std::lock_guard<std::mutex> guard(myMutex);
//     for (auto itr = myList.begin(), end_itr = myList.end(); itr != end_itr; ++itr ) {
//         cout << *itr << ",";
//     }
// }

// int main()
// {
//     int max = 100;

//     std::thread t1(addToList, max, 1);
//     std::thread t2(addToList, max, 10);
//     std::thread t3(printList);

//     t1.join();
//     t2.join();
//     t3.join();

//     return 0;
// }
