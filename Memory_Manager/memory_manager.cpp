#include <iostream>

using namespace std;

#define MEMORY_POOL_SIZE 1024

//Set the memory size
char memoryPool[1024];
int offset = 0;
void* memLoc(size_t size) {
    if (offset + size > MEMORY_POOL_SIZE) {
        cout << "You don't have enough memory" << endl;
        return nullptr;
    }

    void*ptr = memoryPool + offset;
    offset = offset + size;
    return ptr;
}

void memFree(void* ptr, size_t size) {
    offset = offset - size;
    if (offset < 0) offset = 0;
}

int main() {
    
    cout << "The size of the memory is " << MEMORY_POOL_SIZE << endl;

    while (true) {
        int choice;
        int size;

        cout << "What would you like to do?" << endl;
        cout << "1. Check the remaining memory size" << endl;
        cout << "2. Borrow a memory" << endl;
        cout << "3. Return a memory" << endl;
        cout << "4. End the program" << endl;
        cin >> choice;

        if (choice == 1) {
            cout << "The remaining memory size is: " << MEMORY_POOL_SIZE - offset << endl;
        }
        
        if (choice == 2) {
            cout << "The remaining memory size is: " << MEMORY_POOL_SIZE - offset << endl;
            cout << "How much do you want to take? " << endl;
            cin >> size;
            if (size > MEMORY_POOL_SIZE - offset) {
                cout << "You can't take bigger than what is available" << endl;
                continue;
            }
            void* ptr = memLoc(size);

        }

        if (choice == 3) {
            cout << "The remaining memory size is: " << MEMORY_POOL_SIZE - offset << endl;
            cout << "How much are you returning?" << endl;
            cin >> size;
            memFree(nullptr, size);
                cout << "The remaining memory is: " << MEMORY_POOL_SIZE - offset << endl;
        }

        if (choice == 4) {
            cout << "Thank you. Good bye!" <<endl;
            break;
        }

    }
    return 0;
}