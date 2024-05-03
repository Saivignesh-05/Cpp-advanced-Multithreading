#include<iostream>
#include<thread>
#include<mutex>
#include<windows.h>
#include<queue>

using namespace std;

/*
BUSY WAITING:
    If the sleep time is too long, we may skip the data, it will be missed
    If the sleep time is short, too many cycles of lock and unlock wasted
    
    SOLUTION: Condition Variables
*/


queue<int> q;
mutex m;

void func1()
{
    int k=10;
    while(k>0)
    {
        unique_lock<mutex> lk(m);
        q.push(k);
        lk.unlock();
        this_thread::sleep_for(chrono::seconds(1));
        --k;
    }
}

void func2()
{
    int data=0;
    while(data!=1)  // does lot of busy waiting. i.e till the queue has an element
    {
        unique_lock<mutex> lk(m);
        if(!q.empty())
        {
            data = q.front();
            q.pop();
            lk.unlock();
            cout<<"T2 has retrieved a value: "<<data<<endl;
        }
        else
        {
            lk.unlock();
            this_thread::sleep_for(chrono::microseconds(10));   // BUT HOW WILL YOU DECIDE THE OPTIMAL TIME TO SLEEP
        }
    }
}

int main()
{
    thread t1(func1);
    thread t2(func2);
    
}