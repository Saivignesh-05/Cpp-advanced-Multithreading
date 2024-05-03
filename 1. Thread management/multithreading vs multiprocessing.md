# Multithreading vs Multiprocessing
Multiprocessing : 
> Multiple processors running different processes. Note only one process per processor. Uses IPC

Multithreading:
> Multiple threads of a single process. Shares memory unlike multiprocesssing

Advantages of Threading
- it is lightweight process. Thus Faster to start than a process (requires less resources to be allocated by OS)
- Low overhead
- Shared memory

Disadvantages:
- Bugs difficult to overcome
- Cannot run on distributed systems



