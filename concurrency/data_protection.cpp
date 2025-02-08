#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <fstream>

using namespace std;

class LogFile {
    mutex mu;
    ofstream f;
public:
    LogFile() {
        f.open("logfile.txt"); // Use double quotes for string literals
        if (!f) {
            cerr << "Error opening logfile.txt\n";
            exit(1);
        }
    }
    
    ~LogFile() {
        if (f.is_open()) {
            f.close();
        }
    }

    void shared_print(const string &msg, int id) {
        lock_guard<mutex> guard(mu);
        f << msg << id << endl;
    }
};

void function1(LogFile &log) {
    for (int i = 0; i > -100; i--) {
        log.shared_print("From t1: ", i);
    }
}

int main() {
    LogFile log;
    thread t1(function1, ref(log));

    for (int i = 0; i < 100; i++) {
        log.shared_print("From main: ", i);
    }
    t1.join();
}
