#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

using namespace std;
mutex m;

/* 
    Consider this program of popping elements from stack
    Is this program Thread safe
    FIND INSTANCES WHERE THIS WILL FAIL
    * P.S : Answer at the bottom *
 */   

class stack
{
    int *data;
    mutex mu;
public:
    void pop();
    int &top();
};

void tfunc(stack &s)
{
    int v = s.top();
    s.pop();
    // call some func to process 'v'
}

int main()
{
    stack lf;
    thread t1(tfunc, ref(lf));
    
    int v = lf.top();
    lf.pop();

    t1.join();
}





/*
    This is not thread safe. WHY?
    Say Thread t1 first gets top() {example value : 6}
    Next Thread t2 waiting behind t1, also gets top() = 6
    Now t1 pop() and t2 pop(). Both of them processed the same value!
    The value below 6 was simply Popped, not processed
*/

/*
    SOLUTION: Make top and pop in the same function instead of two different calls
    
*/