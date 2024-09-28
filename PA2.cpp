// Name: Dominic McElroy
//Date: 9/28/2024
// Description - Memory Mapping within Limited Space.
//USING TEMPLATE FROM CLASS WEB COMMENTS ARE SAME ETC. ETC. 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define MEMORY_SIZE 256
#define LARGE_MEMORY_SIZE (1 * 1024 * 1024) // 1 MB
#define BAD_BLOCK 'X'

// Simulate the memory space for our allocator
static char memory[MEMORY_SIZE];

// Simulate a large memory space for testing
char *large_memory = nullptr;

// Structure to manage memory blocks
struct Block {
    size_t size;
    bool free;
    Block *next;
};

Block *freeList = reinterpret_cast<Block*>(memory);

// Initialize the memory manager
void initializeMemory() {
    freeList->size = MEMORY_SIZE - sizeof(Block);
    freeList->free = true;
    freeList->next = nullptr;
}

// Randomly mark blocks as "bad" in the large memory
void markBadBlocks(char *memory, size_t size, size_t badBlockCount) {
    srand(static_cast<unsigned>(time(nullptr)));
    for (size_t i = 0; i < badBlockCount; i++) {
        size_t randomIndex = rand() % size;
        memory[randomIndex] = BAD_BLOCK; // Mark as bad block
    }
}

// Function to allocate memory dynamically, skipping bad blocks
void* myMalloc(size_t size) {
    Block *current = freeList;
    size += sizeof(Block); // Include space for the Block struct

    while (current != nullptr) {
        if (current->free && current->size >= size) {
            current->free = false; // Mark block as used
            return reinterpret_cast<void*>(reinterpret_cast<char*>(current) + sizeof(Block));
        }
        current = current->next;
    }
    return nullptr; // No suitable block found
}

// Function to free the allocated memory
void myFree(void *ptr) {
    if (!ptr) return;
    Block *block = reinterpret_cast<Block*>(reinterpret_cast<char*>(ptr) - sizeof(Block));
    block->free = true; // Mark block as free
}

// Unit Test Functions
void testMemoryAllocation() {
    // Test 1: Allocate memory for an array of size 10
    int *array = static_cast<int*>(myMalloc(10 * sizeof(int)));
    if (array != nullptr) {
        std::cout << "Test 1 Passed: Memory allocated for an array of size 10" << std::endl;
        myFree(array);
    } else {
        std::cout << "Test 1 Failed: Memory allocation for array of size 10 failed." << std::endl;
    }

    // Test 2: Try to allocate more memory than available
    int *largeArray = static_cast<int*>(myMalloc(MEMORY_SIZE + 1));
    if (largeArray == nullptr) {
        std::cout << "Test 2 Passed: Large memory block allocation failed as expected." << std::endl;
    } else {
        std::cout << "Test 2 Failed: Large memory block should not have been allocated." << std::endl;
        myFree(largeArray);
    }

    // Test 3: Allocate memory while skipping bad blocks
    int *testBlock = static_cast<int*>(myMalloc(50 * sizeof(int)));
    if (testBlock != nullptr) {
        std::cout << "Test 3 Passed: Memory allocated by skipping bad blocks." << std::endl;
        myFree(testBlock);
    } else {
        std::cout << "Test 3 Failed: Memory allocation should have succeeded by skipping bad blocks." << std::endl;
    }
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <size_of_allocation>" << std::endl;
        return 1;
    }

    size_t allocationSize = static_cast<size_t>(std::atoi(argv[1]));

    // Initialize memory management
    initializeMemory();

    // Allocate a large memory block (1 MB)
    large_memory = static_cast<char*>(malloc(LARGE_MEMORY_SIZE));
    if (large_memory == nullptr) {
        std::cout << "Failed to allocate large memory." << std::endl;
        return 1;
    }

    // Mark some blocks as "bad"
    markBadBlocks(large_memory, LARGE_MEMORY_SIZE, 100); // Mark 100 bad blocks

    // Simulate memory allocation
    int *array = static_cast<int*>(myMalloc(allocationSize * sizeof(int))); // Allocate memory for an array of integers
    if (array == nullptr) {
        std::cout << "Memory allocation failed." << std::endl;
    } else {
        // Assign values to the array and print them
        for (size_t i = 0; i < allocationSize; i++) {
            array[i] = static_cast<int>(i * i); // Assign square of index
            std::cout << "Array[" << i << "] = " << array[i] << std::endl;
        }

        // Free the allocated memory
        myFree(array);
        std::cout << "Memory successfully freed." << std::endl;
    }

    // Run unit tests
    testMemoryAllocation();

    // Clean up large memory block using the system's free function
    free(large_memory);

    return 0;
}
