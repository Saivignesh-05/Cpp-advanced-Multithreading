#include<iostream>
#include<thread>
#include<mutex>
#include<windows.h>
#include<queue>

#include<condition_variable>

using namespace std;

/*
    SOLUTION to Busy Waiting: CONDITION VARIABLES
    CANNOT USE THE lock_guard mutex!

    Spurious Wake:
        If the Thread wakes up by itself by mistake (without being notified)
        It should not continue running
        SOLUTION: use a 'PREDICATE'
*/


queue<int> q;
mutex m;
condition_variable cond;

void func1()        // Pushes values from 10 to 1 into the queue
{
    int k=10;
    while(k>0)
    {
        unique_lock<mutex> lk(m);
        q.push(k);
        lk.unlock();

        cond.notify_one();      
        // cond.notify_all();   notifies all waiting threads
        this_thread::sleep_for(chrono::seconds(1));
        --k;
    }
}

void func2()        // retrieves the value till value == 1. Therefore all values from 10 to 1!
{
    int data=0;
    while(data!=1)  // does lot of busy waiting. i.e till the queue has an element
    {
        unique_lock<mutex> lk(m);

        // The if-else can be eliminated !!!
            cond.wait(lk);  // use the cond-variable to wait on the unique_lock
                            // Before going to sleep, It will unlock the mutex in case it gets locked in sleep
                            // when notified, it will lock the mutex

            cond.wait(lk, [](){return !q.empty();});
            data = q.front();
            q.pop();
            lk.unlock();
            cout<<"T2 has retrieved a value: "<<data<<endl;
        
    }
}

int main()
{
    thread t1(func1);
    thread t2(func2);
    
}