#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <semaphore.h>
#include <queue>

using namespace std;

// Constants
const int NUM_CHAIRS = 5; // Number of chairs in the waiting room

// Semaphores for synchronization
sem_t barberSem;   // Barber waits on this semaphore (sleeps when no customers)
sem_t customerSem; // Customers wait on this semaphore (wait for the barber)
sem_t mtx;       // Protects access to shared variables

// Shared variables
queue<int> waitingRoom; // Queue to track waiting customers
int numWaiting = 0;     // Number of customers waiting

// Function for the barber
void barber() {
    while (true) {
        cout<<"Barber is sleeping"<<endl;
        // Wait for a customer (sleep if no customers)
        sem_wait(&customerSem);

        // Acquire the mutex to access shared variables
        sem_wait(&mtx);

        // Serve the next customer
        int customerId = waitingRoom.front();
        waitingRoom.pop();
        numWaiting--;

        // Release the mutex
        sem_post(&mtx);

        // Barber is cutting hair
        cout << "Barber is cutting hair for customer " << customerId << endl;
        this_thread::sleep_for(chrono::seconds(2)); // Simulate haircut

        // Signal the customer that the haircut is done
        sem_post(&barberSem);
    }
}

// Function for customers
void customer(int id) {
    // Acquire the mutex to access shared variables
    sem_wait(&mtx);

    if (numWaiting < NUM_CHAIRS) {
        // There is space in the waiting room
        waitingRoom.push(id);
        numWaiting++;
        cout << "Customer " << id << " is waiting in the chair." << endl;

        // Signal the barber that a customer is available
        sem_post(&customerSem);

        // Release the mutex
        sem_post(&mtx);

        // Wait for the barber to finish the haircut
        sem_wait(&barberSem);
        cout << "Customer " << id << " has finished the haircut." << endl;
    } else {
        // No space in the waiting room, customer leaves
        cout << "Customer " << id << " left because the waiting room is full." << endl;

        // Release the mutex
        sem_post(&mtx);
    }
}

int main() {
    // Initialize semaphores
    sem_init(&barberSem, 0, 0);   // Barber starts sleeping
    sem_init(&customerSem, 0, 0); // No customers initially
    sem_init(&mtx, 0, 1);       // Mutex for shared variables

    // Create the barber thread
    thread barberThread(barber);

    // Create customer threads
    vector<thread> customerThreads;
    for (int i = 1; i <= 20; ++i) {
        customerThreads.emplace_back(customer, i);
        this_thread::sleep_for(chrono::seconds(1)); // Simulate customer arrival delay
    }

    // Join customer threads
    for (auto& t : customerThreads) {
        t.join();
    }

    // Join the barber thread (runs indefinitely)
    barberThread.join();

    // Destroy semaphores
    sem_destroy(&barberSem);
    sem_destroy(&customerSem);
    sem_destroy(&mtx);

    return 0;
}