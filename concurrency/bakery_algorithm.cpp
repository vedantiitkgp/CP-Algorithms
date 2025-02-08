#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#define THREAD_COUNT 8

using namespace std;

vector<int> tickets(THREAD_COUNT);
vector<bool> choosing(THREAD_COUNT);
volatile int resource = 0;

mutex mtx;

void lock(int thread){

    choosing[thread] = 1;

    atomic_thread_fence(memory_order_seq_cst);
    int max_ticket = 0;
    for (int i = 0; i < THREAD_COUNT; ++i) {
        int ticket = tickets[i];
        max_ticket = ticket > max_ticket ? ticket : max_ticket;
    }
    tickets[thread] = max_ticket + 1;
    atomic_thread_fence(memory_order_seq_cst);


    choosing[thread] = 0;

    for (int other = 0; other < THREAD_COUNT; ++other) {
        while (choosing[other]) {
        }

        atomic_thread_fence(memory_order_seq_cst);

        while (tickets[other] != 0 && (tickets[other] < tickets[thread]
                   || (tickets[other] == tickets[thread] && other < thread))) {
        }
    }
}

void unlock(int thread)
{
    atomic_thread_fence(memory_order_seq_cst);
    tickets[thread] = 0;
}

void use_resource(int thread)
{
    lock_guard<mutex> lock(mtx);

    if (resource != 0) {
        cout << "Resource was acquired by " << thread
                  << ", but is still in-use by " << resource
                  << "!\n";
    }

    resource = thread;
    cout << thread << " using resource...\n";

    atomic_thread_fence(memory_order_seq_cst);
    this_thread::sleep_for(chrono::seconds(2));
    resource = 0;
}

void thread_body(int thread)
{
    lock(thread);
    use_resource(thread);
    unlock(thread);
}

int main()
{
    fill(tickets.begin(), tickets.end(), 0);
    fill(choosing.begin(), choosing.end(), 0);
    resource = 0;

    vector<thread> threads;

    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads.emplace_back(thread_body, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}