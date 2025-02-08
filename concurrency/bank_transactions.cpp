#include <thread>
#include <iostream>
#include <semaphore.h>

using namespace std;

int accountBalance = 1000;

sem_t accountSemaphore;

void transaction(int transactionId, int amount) {
    // Acquire the semaphore to lock the account
    sem_wait(&accountSemaphore);

    // Critical Section: Access and modify the account balance
    cout << "Transaction " << transactionId << " started. Current balance: " << accountBalance << endl;

    // Simulate some processing time
    this_thread::sleep_for(chrono::seconds(1));

    // Perform the transaction (credit or debit)
    if (amount > 0) {
        cout << "Transaction " << transactionId << " crediting " << amount << " to the account." << endl;
    } else {
        cout << "Transaction " << transactionId << " debiting " << -amount << " from the account." << endl;
    }

    // Update the account balance
    accountBalance += amount;

    // Display the updated balance
    cout << "Transaction " << transactionId << " completed. New balance: " << accountBalance << endl;

    // Release the semaphore to unlock the account
    sem_post(&accountSemaphore);
}

int main() {
    // Initialize the semaphore with value 1 (binary semaphore)
    sem_init(&accountSemaphore, 0, 1);

    // List of transactions (positive for credit, negative for debit)
    vector<int> transactions = {200, -100, 300, -50, 150};

    // Vector to hold thread objects
    vector<thread> threads;

    // Create threads for each transaction
    for (size_t i = 0; i < transactions.size(); ++i) {
        threads.emplace_back(transaction, i + 1, transactions[i]);
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    // Destroy the semaphore
    sem_destroy(&accountSemaphore);

    // Final account balance
    cout << "All transactions completed. Final account balance: " << accountBalance << endl;

    return 0;
}