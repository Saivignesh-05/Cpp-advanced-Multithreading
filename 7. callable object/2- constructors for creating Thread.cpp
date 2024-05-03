#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>
#include<future>

using namespace std;

class A
{
public:
    void f(int x, char c)
    {

    }
    long g(double x)
    {return 0;}
    int operator()(int N)       // indicated class A is a functor
    {
        return 0;
    }
};

void foo(int x){}

int main()
{
    A a;    // This is a callable object
    
    thread t1(a,6);         // Copy of 'a' is sent, invokes it as Functor in Different Thread
    thread t2(ref(a),6);    // Launch 'a' as a functor in a Different Thread
    thread t3(A(),6);       // creates temporaty A object. It is moved into the thread object, then created thread
    thread t4([](int x){return x*x;},6);  // using Lambda function
    thread t5(foo,6);

    // using member functions
    thread t6(&A::f, a,6,'w');      // makes a copy of object 'a'
                                    // invokes the function 'f' in class 'A' (i.e a.f(6,'w')) in a different thread
    thread t7(&A::f,&a,6,'w');      // Dont want to make a copy of object 'a'. Same as above

    thread t8(move(a),6);           // I dont want to pass 'a' as reference and dont want to make a copy of it
                                    // This transfers ownership


    // same above goes with
    /*
        bind()
        async()
        call_once()
    */

    return 0;
}