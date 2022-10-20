#include <vector>
#include <string>
#include <iostream>
#include "hash.h"
#include <stdlib.h>
#include <iostream>


using namespace std;

// The constructor initializes the hash table.
// Uses getPrime to choose a prime number at least as large as
// the specified size for the initial size of the hash table.
hashTable::hashTable(int size){
    capacity = getPrime(size);
    data.resize(capacity);
    filled = 0;
}
// Insert the specified key into the hash table.
// If an optional pointer is provided,
// associate that pointer with the key.
// Returns 0 on success,
// 1 if key already exists in hash table,
// 2 if rehash fails.
int hashTable::insert(const std::string &key, void *pv){
    if(filled >= (capacity/2)){
        bool success = rehash();
        if(success != true){
            return 2;
            }
        }
    int value = hash(key);
    int value_start = value;
    int k = 0;
    while(data[value].isOccupied == true && data[value].isDeleted == false){
        if(key == data[value].key){
            return 1;
        }
        value = (value_start + k) % capacity;
        k = k + 1;
        }
    data[value].key = key;
    data[value].isOccupied = true;
    data[value].pv = pv;
    data[value].isDeleted = false;

    filled = filled + 1;
    return 0;  
}  
// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const std::string &key){
    int value = hash(key);
    int value_start = value;
    int k = 0;
    while (data[value].isOccupied == true && data[value].isDeleted == false){
        if (data[value].key == key){
            return true;
        }
        value = (value_start + k) % capacity;
        k = k + 1;
    }
    return false;
}
// Get the pointer associated with the specified key.
// If the key does not exist in the hash table, return nullptr.
// If an optional pointer to a bool is provided,
// set the bool to true if the key is in the hash table,
// and set the bool to false otherwise.
void *hashTable::getPointer(const std::string &key, bool *b){
    int temp = findPos(key);
        if(temp == -1){
            if(b != nullptr){
                *b = false;
            }
                return nullptr;
        }
        else{
            if(b != nullptr){
                *b = true;
            }
            return data[temp].pv;
        }

}


// Set the pointer associated with the specified key.
// Returns 0 on success,
// 1 if the key does not exist in the hash table.

int hashTable::setPointer(const std::string &key, void *pv){
    int temp = findPos(key);
    if(temp == -1){
        return 1;
    }
    else{
        data[temp].pv = pv;
        return 0;
    }
}


// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.

bool hashTable::remove(const std::string &key){
    int temp = findPos(key);
    if(temp == -1){
        return false;
    }
    else{
        data[temp].isDeleted = true;
    }
}

// Each item in the hash table contains:
// key - a string used as a key.
// isOccupied - if false, this entry is empty,
//              and the other fields are meaningless.
// isDeleted - if true, this item has been lazily deleted.
// pv - a pointer related to the key;
//      nullptr if no pointer was provided to insert.


// The hash function.
int hashTable::hash(const std::string &key){
    unsigned int hashVal = 0;

    for (char ch : key)
        hashVal = 37 * hashVal + ch;
    return hashVal % capacity;
}

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const std::string &key){
    int value = hash(key);
    int value_start = value;
    int k = 0;
    while (data[value].isOccupied == true && data[value].isDeleted == false){
        if (data[value].key == key){
            return value;
        }
        value = (value_start + k) % capacity;
        k = k + 1;
    }
    return -1;
}
// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash(){
    try {
        filled = 0;
        int old_capacity = capacity;
        capacity = getPrime(capacity);
        vector<hashItem> old_data = data;
        data.resize(capacity);
        for(int idx = 0; idx < capacity; idx++){
            data[idx].isOccupied = false;
        }
        for(int idx = 0; idx < old_capacity; idx++){
            if(old_data[idx].isOccupied){
                insert(old_data[idx].key);

            }
        }
        return true;
    } 
    catch (bad_alloc&) {
    cerr << "Unable to allocate memory"<< endl;
    }
    return false;
}
// Return a prime number at least as large as size.
// Uses a precomputed sequence of selected prime numbers.
unsigned int hashTable::getPrime(int size){
    int primes[] = {100733, 202549, 410009,850349,1700021,3700097,7201153,16000781};
    for(int i = 0; i<7; i++){
        if(primes[i] > size){
            
            return primes[i];
        }
    }
    return 0;
}
