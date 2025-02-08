#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore.h>

using namespace std;

sem_t northSouthGreen;  // Semaphore for North-South Green light
sem_t eastWestGreen;    // Semaphore for East-West Green light
sem_t northSouthRed;    // Semaphore for North-South Red light
sem_t eastWestRed;      // Semaphore for East-West Red light

// Function to simulate North-South traffic light cycle
void northSouthTraffic() {
    while (true) {
        sem_wait(&northSouthGreen);  // Wait for North-South green light
        std::cout << "North-South: Green light (Go!)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Green light for 5 seconds

        // Transition to yellow light
        std::cout << "North-South: Yellow light (Slow down!)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Yellow light for 2 seconds

        // Transition to red light
        std::cout << "North-South: Red light (Stop!)" << std::endl;
        sem_post(&northSouthRed);     // Signal East West red light
    }
}

// Function to simulate East-West traffic light cycle
void eastWestTraffic() {
    while (true) {
        sem_wait(&eastWestGreen);  // Wait for East-West green light
        std::cout << "East-West: Green light (Go!)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Green light for 5 seconds

        // Transition to yellow light
        std::cout << "East-West: Yellow light (Slow down!)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Yellow light for 2 seconds

        // Transition to red light
        std::cout << "East-West: Red light (Stop!)" << std::endl;
        sem_post(&eastWestRed);     // Signal East-West red light
    }
}

// Controller to manage light transitions
void trafficLightController() {
    while (true) {
        // Allow North-South to go green and East-West to go red
        sem_post(&northSouthGreen);  // Signal North-South green light
        sem_wait(&northSouthRed);      // Wait for North South red light
        // std::this_thread::sleep_for(std::chrono::seconds(7)); // 5 seconds green + 2 seconds yellow for North-South

        // After North-South cycle is done, allow East-West to go green
        sem_post(&eastWestGreen);    // Signal East-West green light
        sem_wait(&eastWestRed);    //Wait for East West Red Light

        // std::this_thread::sleep_for(std::chrono::seconds(7)); // 5 seconds green + 2 seconds yellow for East-West
    }
}

int main() {
    // Initialize semaphores
    sem_init(&northSouthGreen, 0, 0);  // Initialize with 0 to block North-South initially
    sem_init(&eastWestGreen, 0, 0);    // Initialize with 0 to block East-West initially
    sem_init(&northSouthRed, 0, 0);    // Initialize with 0 to block North-South red initially
    sem_init(&eastWestRed, 0, 0);      // Initialize with 0 to block East-West red initially

    // Create threads for North-South and East-West traffic
    std::thread northSouth(northSouthTraffic);
    std::thread eastWest(eastWestTraffic);

    // Start the traffic light controller
    std::thread controller(trafficLightController);

    // Join threads to the main thread to keep running
    northSouth.join();
    eastWest.join();
    controller.join();

    // Destroy semaphores (not strictly necessary, but good practice)
    sem_destroy(&northSouthGreen);
    sem_destroy(&eastWestGreen);
    sem_destroy(&northSouthRed);
    sem_destroy(&eastWestRed);

    return 0;
}