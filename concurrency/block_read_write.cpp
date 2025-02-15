#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// Simulate Block Based API
const size_t BLOCK_SIZE = 8;  // Example block size
const size_t TOTAL_BLOCKS = 10; // Example total blocks

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
    currentByteOffset = location;
    return 0;
}

// Read to the Data Pointer
int read(void *dataPtr, size_t len){
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
    return bytesRead;
}

// Write from the data pointer
int write(void *dataPtr, int len){
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
    return bytesWritten;
}

// Main function to test the implementation
int main() {
    char data1[] = "HelloWorld"; // 10 bytes
    char data2[] = "123456"; // 6 bytes
    char readBuffer[16];

    seek(12);
    write(data1, 10);
    write(data2, 6);

    seek(17);
    read(readBuffer, 2);
    readBuffer[2] = '\0';  // Null terminate for printing

    std::cout << "Read Data: " << readBuffer << std::endl; // Expected: "lo"
    
    return 0;
}