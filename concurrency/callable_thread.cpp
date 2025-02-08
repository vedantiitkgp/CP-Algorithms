#include <thread>
#include <iostream>
#include <future>

using namespace std;

once_flag f;

class A {
public:
    void f(int x, char c) {}

    long g(double x) { return 0; }

    int operator()(int N) { 
        return 0;
    } // Operator overloading allows calling it like a function
};

int foo(int x){ 
    return x*x;
}

int main() {
    A a;

    // Creating a thread using functor
    thread t1(a, 6);  // Creating a copy of a() in child thread
    // thread t2(ref(a), 6); // Calling a() in child thread
    // thread t3(A(), 6); // Temporary a moved in child thread
    // thread t4([](int x){ return x*x;}, 6); // lambda function
    // thread t5(foo, 7); // Normal functions
    // thread t6(&A::f, a, 8, 'w'); // Copy of a and calling a.f functions
    // thread t7(&A::f, &a, 8, 'w'); // calling a.f functions
    // thread t8(move(a), 6); // Move a from main to child thread

    //Call above for all functions

    // Async execution
    future<int> result = async(launch::async, a, 6);

    // Bind Function
    bind(a, 6);

    // Call Once Function
    call_once(f, a, 6);

    t1.join();  // Ensure thread completes

    cout << "Async result: " << result.get() << endl;  // Retrieve async result

    return 0;
}
