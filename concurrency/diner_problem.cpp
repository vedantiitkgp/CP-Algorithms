#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <semaphore.h>

using namespace std;

const int NUM_PHILOSOPHERS = 5; // Number of philosophers

// Semaphores representing the forks
vector<sem_t> forks(NUM_PHILOSOPHERS);

// Function to simulate a philosopher's actions
void philosopher(int id) {
    int leftFork = id;
    int rightFork = (id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        // Think for a while
        cout << "Philosopher " << id << " is thinking..." << endl;
        this_thread::sleep_for(chrono::seconds(1));

        // Acquire the left fork
        sem_wait(&forks[leftFork]);
        cout << "Philosopher " << id << " picked up fork " << leftFork << " (left)." << endl;

        // Acquire the right fork
        sem_wait(&forks[rightFork]);
        cout << "Philosopher " << id << " picked up fork " << rightFork << " (right)." << endl;

        // Eat for a while
        cout << "Philosopher " << id << " is eating..." << endl;
        this_thread::sleep_for(chrono::seconds(2));

        // Release the right fork
        sem_post(&forks[rightFork]);
        cout << "Philosopher " << id << " put down fork " << rightFork << " (right)." << endl;

        // Release the left fork
        sem_post(&forks[leftFork]);
        cout << "Philosopher " << id << " put down fork " << leftFork << " (left)." << endl;
    }
}

int main() {
    // Initialize the semaphores (forks)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&forks[i], 0, 1); // Initialize each fork semaphore with value 1
    }

    // Create threads for each philosopher
    vector<thread> philosophers;
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(philosopher, i);
    }

    // Wait for all philosopher threads to finish (they won't, as they run indefinitely)
    for (auto& t : philosophers) {
        t.join();
    }

    // Destroy the semaphores (not strictly necessary, but good practice)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_destroy(&forks[i]);
    }

    return 0;
}