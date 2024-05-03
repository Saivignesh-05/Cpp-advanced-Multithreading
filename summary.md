# CREATING THREAD
- thread t1(function, param1,param2,...)
- async(function,params) : \
    future<return_type> f = async(factorial,6)
- call_once()
- 

# MUTEX TYPES
- mutex mu
- lock_guard<mutex> lck(mu)
- unique_lock<mutex> ulck(mu)

# CONDITION VARIABLES
- condtition_variable cond

# FUTURE AND PROMISE
- promise<int> p
- future<int> f = p.get_future()

# PACKAGED TASKS
- packaged_tasks<return_type(param1,param2,..)> pt(function)
- future<return_type> f = pt.get_return()