// Consumer Process consuming from the buffer
// Producer Process producing for the buffer

// Sempahores used 
// Empty - Count the number of empty slots in buffer
// Full - Count the number of full slots in the buffer
// Mutex - Locks access to the buffer

// Pseduocode

// Wait Operation (Reduces the value of S otherwise waits till condition is true)
//Wait(S){
//   while(S<=0);
//   S--; 
//}

// Signal Operation (Increase the value of S)
// Signal(S){
//    S++;
//}

// Allows Accces to Shared Buffer in Synchronised way

#include <thread>
#include <iostream>
#include <semaphore.h>
#include <vector>
#include <chrono>

using namespace std;

class ProducerConsumer{
private:
    sem_t mutex; // Protects the Critical Section
    sem_t full; // Tracks  no of full slots
    sem_t empty; // Tracks no of empty slots
    vector<int> buffer;
    int buffer_size;

public:
    ProducerConsumer(int size) : buffer_size(size) {
        sem_init(&mutex, 0, 1);
        sem_init(&full, 0, 0);
        sem_init(&empty, 0, size);
        buffer.resize(size, 0);
    }

    //Producer Function
    void produce(int item, int id){
        while(true){
            sem_wait(&empty);
            sem_wait(&mutex);

            //Critical Section
            buffer.push_back(item);
            cout << "Producer " << id << " produced item: " << item << endl;

            sem_post(&mutex);
            sem_post(&full);

            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }

    // Consumer function
    void consume(int id){
        while(true){
            sem_wait(&full);
            sem_wait(&mutex);

            // Critical Section
            int item = buffer.back();
            buffer.pop_back();
            cout<< "Consumer "<< id<<" consumer item : "<<item<<endl;

            sem_post(&mutex);
            sem_post(&empty);

            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }

    ~ProducerConsumer() {
        sem_destroy(&mutex);
        sem_destroy(&full);
        sem_destroy(&empty);
    }
};

int main() {
    const int buffer_size = 5;  // Size of the buffer
    ProducerConsumer pc(buffer_size);

    // Create producer and consumer threads
    thread producer1(&ProducerConsumer::produce, &pc, 1, 1);
    thread producer2(&ProducerConsumer::produce, &pc, 2, 2);
    thread consumer1(&ProducerConsumer::consume, &pc, 1);
    thread consumer2(&ProducerConsumer::consume, &pc, 2);

    // Join threads to the main thread
    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();

    return 0;
}