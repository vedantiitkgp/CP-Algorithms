// struct semaphore {
  
//     enum value(0, 1);

//     // q contains all Process Control Blocks (PCBs)
//     // corresponding to processes got blocked
//     // while performing down operation.
//     Queue<process> q;

// };

// P(semaphore s)
// {
//     if (s.value == 1) {
//         s.value = 0;
//     }
//     else {
//         // add the process to the waiting queue
//         q.push(P) sleep();
//     }
// }
// V(semaphore s)
// {
//     if (s.q is empty) {
//         s.value = 1;
//     }
//     else {

//         // select a process from waiting queue
//         Process p = q.front();
//         // remove the process from waiting as it has been
//         // sent for CS
//         q.pop();
//         wakeup(p);
//     }
// }



#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    int value;
    std::queue<std::thread::id> q;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Semaphore(int init_value = 1) : value(init_value) {}

    void P() {
        std::unique_lock<std::mutex> lock(mtx);
        std::thread::id this_id = std::this_thread::get_id();
        q.push(this_id);
        while (value == 0 || q.front() != this_id) {
            cv.wait(lock);
        }
        q.pop();
        value = 0;
    }

    void V() {
        std::unique_lock<std::mutex> lock(mtx);
        value = 1;
        if (!q.empty()) {
            cv.notify_all();
        }
    }
};

void critical_section(int id, Semaphore &sem) {
    sem.P();
    std::cout << "Thread " << id << " is in the critical section." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " is leaving the critical section." << std::endl;
    sem.V();
}

int main() {
    Semaphore sem(1);
    std::thread t1(critical_section, 1, std::ref(sem));
    std::thread t2(critical_section, 2, std::ref(sem));
    std::thread t3(critical_section, 3, std::ref(sem));
    
    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}