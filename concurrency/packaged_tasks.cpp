#include <thread>
#include <iostream>
#include <mutex>
#include <future>
#include <deque>

using namespace std;

/* Packaged task */
int factorial(int N){
    int res = 1;
    for(int i=N; i>=1; i--){
        res *= i;
    }
    cout<<"Result is :"<<res<<endl;
    return res;
}

deque<packaged_task<int()>> task_q;
mutex mu;
condition_variable cond;

void thread1(){
    packaged_task<int()> t;
    unique_lock<mutex> lock(mu);
    cond.wait(lock, [](){ return !task_q.empty();});
    t = move(task_q.front());
    task_q.pop_front();
    lock.unlock();
    t();
}

int main(){
    // thread t1(factorial, 6)   //Normal Thread
    packaged_task<int(int)> t(factorial); // Function that tasked integer and return integer
    packaged_task<int()> t2(bind(factorial, 6)); // Binded function with parameter 
    future<int> fu = t2.get_future(); 
    thread t1(thread1);

    cout<<fu.get()<<endl;
    unique_lock<mutex> lock(mu);
    task_q.push_back(t2);
    cond.notify_one();
    lock.unlock();

    t1.join();
    //.....
    t(6); // Task can be passed around and executed later
    // t2(); Binded execution


    // int x = t.get_future().get() // To get value
}

/*
3 ways to get future
 1. Promises get future
 2. Packaged Tasks get future
 3. Async function get future
*/