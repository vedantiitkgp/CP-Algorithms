#include <iostream>
#include <thread>
#include <future>
#include <mutex>

using namespace std;

int factorial(int N){
    int res = 1;

    for(int i=1; i<=N; i++){
        res *= i;
    }
    return res;
}

int main(){
    /* Thread */
    thread t1(factorial, 6);
    this_thread::sleep_for(chrono::milliseconds(200));
    chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::microseconds(4);
    this_thread::sleep_until(tp);

    /* Mutex */
    mutex mu;
    lock_guard<mutex> locker(mu);
    unique_lock<mutex> uLocker(mu);
    uLocker.try_lock();
    uLocker.try_lock_for(chrono::nanoseconds(500));
    uLocker.try_lock_until(tp);

    /* Conditional Variables */
    condition_variable cond;
    cond.wait_for(uLocker, chrono::nanoseconds(400));
    cond.wait_until(uLocker, tp);

    /* Future */
    promise <int> p;
    future <int> f = p.get_future();
    f.get(); // Internally calls below functions when does'nt receive results

    f.wait();
    f.wait_for(chrono::milliseconds(500));
    f.wait_until(tp);

    /* Async */
    future<int> fu = async(factorial, 6);

    /* Packaged Tasks */
    packaged_task<int(int)> t(factorial);
    future<int> fu2 = t.get_future();
    fu2.get();
    t(6);
}


