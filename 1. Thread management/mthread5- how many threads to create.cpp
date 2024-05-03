#include<iostream>
#include<thread>


/*
 "oversubscription" is when you create MORE threads than the H/W can handle
 Creates a lot of context switching - DEGRADES PERFORMANCE
*/
using namespace std;

int main()
{
    cout<<thread::hardware_concurrency(); // How many threads can be truly running in the h/w
}