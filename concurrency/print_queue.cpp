#include <thread>
#include <semaphore.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> printTasks;
sem_t printSemaphore;

void printTask(int id, string task_value) {
    sem_wait(&printSemaphore);
    
    cout << "Received a Print task: " << task_value << endl;
    this_thread::sleep_for(chrono::seconds(1));

    // Ensure `printTasks` is accessed within the semaphore-locked section
    printTasks.push_back(task_value);
    
    sem_post(&printSemaphore);
}

int main() {
    sem_init(&printSemaphore, 0, 1);

    // Ensure proper thread argument passing
    thread printThread1(printTask, 0, "Graduation Ceremony");
    thread printThread2(printTask, 1, "Hope");
    thread printThread3(printTask, 2, "UC Irvine");

    printThread1.join();
    printThread2.join();
    printThread3.join();

    sem_destroy(&printSemaphore);

    // Print the collected items
    cout << "Print Items:" << endl;
    for (const auto& printItem : printTasks) {
        cout << printItem << endl;
    }

    return 0;
}