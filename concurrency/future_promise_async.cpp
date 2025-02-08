#include <thread>
#include <mutex>
#include <iostream>
#include <future>

using namespace std;

int factorial(future<int> &f){
    int res = 1;
    int N = f.get();

    for(int i=1; i<=N; i++){
        res *= i;
    }
    return res;
}

int main(){
    int x;

    promise<int> p;
    future<int> f = p.get_future();
    // shared_future<int> sf = f.share() (Can be shared)

    future<int> fu = async(factorial, ref(f));

    // After some task
    p.set_value(4);
    int x = fu.get();
    cout<<"Main thread ends  :"<<x<<endl;
}