#include <mutex>
#include <condition_variable>

using namespace std;

const int SIZE = 100;
char buffer[SIZE];
int start = 0;
int buffer_count = 0;
int buffer_end = 0;

mutex mtx;
condition_variable cv;

void put(char c) {
    unique_lock<mutex> lock(mtx);  // Locking the mutex

    // Wait if the buffer is full
    while (buffer_count == SIZE) {
        cv.wait(lock);
    }

    // Insert the character into the buffer
    buffer[start] = c;
    start = (start + 1) % SIZE;  // Circular buffer handling
    buffer_count++;

    // Notify all threads (if waiting)
    cv.notify_all();
}

char get() {
    unique_lock<mutex> lock(mtx);

    // Wait if the buffer is empty
    while (buffer_count == 0) {
        cv.wait(lock);
    }

    // Retrieve the character from the buffer
    char c = buffer[buffer_end];
    buffer_end = (buffer_end + 1) % SIZE;  // Circular buffer handling
    buffer_count--;

    // Notify all threads (if waiting)
    cv.notify_all();

    return c;
}