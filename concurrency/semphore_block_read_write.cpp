#include <iostream>
#include <cstring>
#include <algorithm>
#include <semaphore.h>

using namespace std;

// Simulate Block Based API
const size_t BLOCK_SIZE = 8;  // Example block size
const size_t TOTAL_BLOCKS = 10; // Example total blocks

sem_t readerSem;
sem_t resourceSem;

// Shared Resources
int readers = 0;
char storage[TOTAL_BLOCKS][BLOCK_SIZE]; // Simulated block storage
size_t currentByteOffset = 0; // Byte pointer

// Block-based functions (simulated)
int bBlockSize() { return BLOCK_SIZE; }

int bSeek(size_t blockNum) {
    if (blockNum >= TOTAL_BLOCKS) return -1;
    return 0; // Simulated seek
}

int bRead(void *blockPtr) {
    size_t blockNum = currentByteOffset / BLOCK_SIZE;
    if (blockNum >= TOTAL_BLOCKS) return -1;
    memcpy(blockPtr, storage[blockNum], BLOCK_SIZE);
    return 0;
}

int bWrite(void *blockPtr) {
    size_t blockNum = currentByteOffset / BLOCK_SIZE;
    if (blockNum >= TOTAL_BLOCKS) return -1;
    memcpy(storage[blockNum], blockPtr, BLOCK_SIZE);
    return 0;
}


// Byte-based functions
int seek(size_t location) {
    sem_wait(&resourceSem);
    currentByteOffset = location;
    sem_post(&resourceSem);
    return 0;
}

// Read to the Data Pointer
int read(void *dataPtr, size_t len){
    sem_wait(&readerSem);
    readers++;
    if(readers == 1){
        sem_wait(&resourceSem);
    }
    sem_post(&readerSem);
    

    size_t bytesRead = 0;
    size_t blockNum = currentByteOffset / BLOCK_SIZE;
    size_t blockOffset = currentByteOffset % BLOCK_SIZE;

    char *dest = (char *)dataPtr; // Where data is to be read

    while(bytesRead < len){
        char blockBuffer[BLOCK_SIZE]; // Buffer to store current block
        bSeek(blockNum); // Seeking the current Block Number
        bRead(blockBuffer); // Reading all the data into the Block Buffer

        size_t toRead = min(len-bytesRead, BLOCK_SIZE - blockOffset); // Min of Amount Available to read with current offset and needed to read
        memcpy(dest+bytesRead, blockBuffer+blockOffset, toRead);

        blockOffset = 0; // Reset the Block Offest
        blockNum++; // Increased BlockNum to read
        bytesRead += toRead; 
    }
    currentByteOffset += len;

    sem_wait(&readerSem);
    readers--;
    if(readers == 0){
        sem_post(&resourceSem);
    }
    sem_post(&readerSem);
    return bytesRead;
}

// Write from the data pointer
int write(void *dataPtr, int len){
    sem_wait(&resourceSem);
    int bytesWritten = 0;
    size_t blockNum = currentByteOffset / BLOCK_SIZE;
    size_t blockOffset = currentByteOffset % BLOCK_SIZE;

    char *src = (char *)dataPtr; // Where data is to be written from

    while(bytesWritten < len){
        char blockBuffer[BLOCK_SIZE];

        // Seeking the reading the data from current block because only some parts of data is needed to modified
        bSeek(blockNum);
        bRead(blockBuffer);

        size_t toWrite = min(len-bytesWritten, BLOCK_SIZE-blockOffset);
        memcpy(blockBuffer+blockOffset, src + bytesWritten, toWrite);

        bSeek(blockNum);
        bWrite(blockBuffer);

        blockOffset = 0;
        blockNum++;
        bytesWritten += toWrite;
    }
    currentByteOffset += len;
    sem_post(&resourceSem);
    return bytesWritten;
}

// Thread functions
void writerThread() {
    char data[] = "HelloMutex";
    seek(0);
    write(data, strlen(data));
}

void readerThread() {
    char buffer[10] = {0};
    seek(0);
    read(buffer, 10);
    std::cout << "Reader read: " << buffer << std::endl;
}

int main() {
    sem_init(&readerSem, 0, 1);
    sem_init(&resourceSem, 0, 1);
    std::thread t1(writerThread);
    std::thread t2(readerThread);


    t1.join();
    t2.join();

    sem_destroy(&readerSem);
    sem_destroy(&resourceSem);

    return 0;
}