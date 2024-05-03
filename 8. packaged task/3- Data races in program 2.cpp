#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>
#include<future>
#include<functional>

#include<queue>
/*
    ADVANTAGES of Packaged Tasks
    -> Link a callable object in the future?
    Say there is a Thread that is allocating tasks to SLAVE threads
    Now we can bundle this into Packaged task, push it into a queue

    Later when a slave is free, It takes this task and executes it!

*/

using namespace std;


int factorial(int N)
{
    int ans=1;
    while(N>1)
    {
        ans*=N;
        --N;
    }
    cout<<"answer is: "<<ans<<endl;
    return ans;
}

deque<packaged_task<int()>> task_q;
mutex mux;
condition_variable cond;
void thread1()
{
    packaged_task<int()> t;

    {
        unique_lock<mutex> lck(mux);

        cond.wait(lck,[](){!task_q.empty();});      // VERY IMPORTANT TO ENSURE NO DATA RACE

        t = move(task_q.front());       // takes ownership of the packaged task
        task_q.pop_front();
    }   // after this block ends, mutex is released!

    t();    // execute
}

int main()
{
    thread t1(thread1);
    packaged_task<int()> pt(bind(factorial,6));      //<return_type(parameter_type)>
    
    {
        unique_lock<mutex> ul(mux);
        task_q.push_back(pt);       // main thread creates task, pushes into task queue
        // task_q.push_back(move(pt));  This is much better since main is not associated with this pt anymore
    
    }// releases lock here
    cond.notify_one();  // notify the waiting thread

    t1.join();
    cout<<"return value: "<<pt.get_future().get()<<endl;
    return 0;    
}

/*
    THREE WAYS TO GET A 'FUTURE'
    1. promise.get_future()
    2. packaged_task.get_future()
    3. async() returns a future
*/