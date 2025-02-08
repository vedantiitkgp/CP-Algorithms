#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <semaphore.h>

using namespace std;

// Shared resource (data)
int sharedData = 0;

// Semaphores for synchronization
sem_t readMutex;      // Protects the reader count
sem_t resourceMutex;  // Ensures exclusive access for writers
sem_t writeMutex;    // Protects the writer count
sem_t readerMutex;    // Blocks new readers when a writer is waiting

int readerCount = 0;  // Number of active readers
int writerWaiting = 0; // Number of waiting writers

// Function for readers
void reader(int id) {
    while (true) {
        // Block new readers if there are waiting writers
        sem_wait(&readerMutex);

        // Enter critical section for reader count
        sem_wait(&readMutex);
        readerCount++;
        if (readerCount == 1) {
            // First reader locks the resource
            sem_wait(&resourceMutex);
        }
        sem_post(&readMutex);

        // Allow new readers to proceed (if no writers are waiting)
        sem_post(&readerMutex);

        // Read the shared data
        cout << "Reader " << id << " is reading data: " << sharedData << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); // Simulate reading

        // Exit critical section for reader count
        sem_wait(&readMutex);
        readerCount--;
        if (readerCount == 0) {
            // Last reader unlocks the resource
            sem_post(&resourceMutex);
        }
        sem_post(&readMutex);

        // Simulate some delay before next read
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

// Function for writers
void writer(int id) {
    while (true) {
        // Enter critical section for writer count
        sem_wait(&writeMutex);
        writerWaiting++;
        if (writerWaiting == 1) {
            // First waiting writer blocks new readers
            sem_wait(&readerMutex);
        }
        sem_post(&writeMutex);

        // Enter critical section for writing
        sem_wait(&resourceMutex);

        // Write to the shared data
        sharedData++;
        cout << "Writer " << id << " is writing data: " << sharedData << endl;
        this_thread::sleep_for(chrono::milliseconds(1000)); // Simulate writing

        // Exit critical section for writing
        sem_post(&resourceMutex);

        // Exit critical section for writer count
        sem_wait(&writeMutex);
        writerWaiting--;
        if (writerWaiting == 0) {
            // No more waiting writers, allow new readers
            sem_post(&readerMutex);
        }
        sem_post(&writeMutex);

        // Simulate some delay before next write
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}

int main() {
    // Initialize semaphores
    sem_init(&readMutex, 0, 1);      // Binary semaphore for reader count
    sem_init(&resourceMutex, 0, 1);  // Binary semaphore for resource access
    sem_init(&writeMutex, 0, 1);    // Binary semaphore for writer count
    sem_init(&readerMutex, 0, 1);    // Binary semaphore to block new readers

    // Create reader and writer threads
    vector<thread> readers;
    vector<thread> writers;

    for (int i = 0; i < 5; ++i) {
        readers.emplace_back(reader, i);
    }

    for (int i = 0; i < 2; ++i) {
        writers.emplace_back(writer, i);
    }

    // Join threads (run indefinitely)
    for (auto& t : readers) {
        t.join();
    }
    for (auto& t : writers) {
        t.join();
    }

    // Destroy semaphores
    sem_destroy(&readMutex);
    sem_destroy(&resourceMutex);
    sem_destroy(&writeMutex);
    sem_destroy(&readerMutex);

    return 0;
}