#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "hash.h"
#include "heap.h"


using namespace std;

// heap - The constructor allocates space for the nodes of the heap
// and the mapping (hash table) based on the specified capacity
heap::heap(int capacity_heap_1){
    capacity_heap = capacity_heap_1 + 1;
    hashTable mapping(capacity_heap*2);
    data.resize(capacity_heap);
    current_size = 1;
}

// insert - Inserts a new node into the binary heap

// Inserts a node with the specified id string, key,
// and optionally a pointer. They key is used to
// determine the final position of the new node.
//
// Returns:
// 0 on success
// 1 if the heap is already filled to capacity
// 2 if a node with the given id already exists (but the heap
// is not filled to capacity)
//

int heap::insert(const std::string &id, int key, void *pv){
    if(current_size == capacity_heap){
        return 1;
    }
    else{
        if(mapping.contains(id) == true){
            return 2;
        }
        data[current_size].key = key;
        data[current_size].id = id;
        data[current_size].pv = pv;
        mapping.insert(id, &data[current_size]);
        percolateUp(current_size);
        current_size++;
        return 0;
        }
}

//
// setKey - set the key of the specified node to the specified value
//

// I have decided that the class should provide this member function
// instead of two separate increaseKey and decreaseKey functions.
//
// Returns:
// 0 on success
// 1 if a node with the given id does not exist
//
int heap::setKey(const std::string &id, int key){
    for(int idx = 1; idx<current_size; idx++){
        if(data[idx].id == id){
            data[idx].key = key;
            percolateUp(idx);
            percolateDown(idx);
            return 0;
            }
        }
    return 1;
    }
    
//
// deleteMin - return the data associated with the smallest key
// and delete that node from the binary heap
//

// If pId is supplied (i.e., it is not nullptr), write to that address
// the id of the node being deleted. If pKey is supplied, write to
// that address the key of the node being deleted. If ppData is
// supplied, write to that address the associated void pointer.
//
// Returns:
// 0 on success
// 1 if the heap is empty
//
int heap::deleteMin(std::string *pId, int *pKey, void *ppData){

    if(current_size < 2){
        return 1;
    }
    else{
        if(pKey != nullptr){
        *pKey = data[1].key;
        }
        if(pId != nullptr){
        *pId = data[1].id;
        }
        mapping.remove(data[1].id);
        data[1] = data[current_size-1];
        mapping.setPointer(data[current_size-1].id, &data[1]);
        percolateDown(1);
        current_size--;
        
        //*(static_cast<void **> (ppData)) = data[1].pData;
        return 0;
    }
}
//
// remove - delete the node with the specified id from the binary heap
//

// If pKey is supplied, write to that address the key of the node
// being deleted. If ppData is supplied, write to that address the
// associated void pointer.
//
// Returns:
// 0 on success
// 1 if a node with the given id does not exist
//
int heap::remove(const std::string &id, int *pKey, void *ppData){
for(int idx = 1; idx<current_size; idx++){
    if(data[idx].id == id){
        *pKey = data[idx].key;
        int temp = *pKey; 
        data[idx].key = data[1].key-1;
        percolateUp(idx);
        deleteMin(nullptr, pKey, ppData);
        *pKey = temp;
        return 0;
    }
}
return 1;
}

void heap::percolateUp(int posCur){
    node temp = data[posCur];
    int parent_idx = (posCur)/2;
    //TODO : Pointer Stuff Maybe
    //TODO : Works but not for the root of heap
    
    while(data[parent_idx].key > temp.key){
        if(parent_idx == 0){
            data[posCur] = temp;
            mapping.setPointer(temp.id, &data[posCur]);
            return;
        }
        if(posCur == 1){
            return;;
        }
        mapping.setPointer(data[parent_idx].id, &data[posCur]);
        data[posCur] = data[parent_idx];
        posCur = parent_idx;  
        parent_idx = (posCur)/2;
    }
    data[posCur] = temp;
    mapping.setPointer(temp.id, &data[posCur]);
    return;
}
void heap::percolateDown(int posCur){
    node temp = data[posCur];
    int child_idx_2 = (posCur*2)+1;
    int child_idx_1 = (posCur*2);
    //TODO : Pointer Stuff Maybe

    while(temp.key > data[child_idx_1].key ||  temp.key > data[child_idx_2].key){
        if(posCur * 2 >= current_size){
            data[posCur] = temp;
            mapping.setPointer(temp.id, &data[posCur]);
            return;
        }
        if(child_idx_2 == current_size){
            if(temp.key > data[child_idx_1].key){
                data[posCur] = data[child_idx_1];
                mapping.setPointer(data[child_idx_1].id, &data[posCur]);
                posCur = child_idx_1;
                child_idx_2 = (posCur*2)+1;
                child_idx_1 = (posCur*2);
                data[posCur] = temp;
                mapping.setPointer(temp.id, &data[posCur]);
                return;
            }
            data[posCur] = temp;
            mapping.setPointer(temp.id, &data[posCur]);
            return;
        }
        if(data[child_idx_1].key <= data[child_idx_2].key){
                data[posCur] = data[child_idx_1];
                mapping.setPointer(data[child_idx_1].id, &data[posCur]);
                posCur = child_idx_1;
                child_idx_2 = (posCur*2)+1;
                child_idx_1 = (posCur*2);
                continue;
        }
        if(data[child_idx_1].key > data[child_idx_2].key){
            data[posCur] = data[child_idx_2];
            mapping.setPointer(data[child_idx_2].id, &data[posCur]);
            posCur = child_idx_2;
            child_idx_2 = (posCur*2)+1;
            child_idx_1 = (posCur*2);
            continue;
        }
    }
    data[posCur] = temp;
    mapping.setPointer(temp.id, &data[posCur]);
    return;
}

int heap::getPos(node *pn){
    int pos = pn - &data[0];
    return pos;
}
/*
void heap::printHeap()
{
    //print the heap so that it looks like a binary tree
    int level = 0;
    int levelSize = 1;
    int levelCount = 0;
    int numLevels = std::log2(current_size) + 1;
    for (int i = 1; i != current_size; i++)
    {

        if(!mapping.contains(data[i].id))
        {
            // the data is in the heap, but it's not in the hash table
            throw "THIS IS BREAKING HERE";
        }
        // print appropriate beginning tabs where the first level has the most tabs and the last level has none
        if(levelCount == 0)
        {
            for (int j = 0; j < std::pow(2,numLevels - (level+1)); j++)
            {
                std::cout << "\t";
            }
        }
        std::cout << data[i].id << ": " << data[i].key;
        // print appropriate intermediate tabs
        if (levelCount < levelSize - 1)
        {
            for (int j = 0; j < std::pow(2,numLevels - (level+1)); j++)
            {
                // if we are in the middle
                if( levelCount == levelSize/2 -1)
                {
                    for (int j = 0; j < std::pow(2,numLevels - 1); j++)
                    {
                        std::cout << "\t";
                    }
                    break;
                }
                else
                {
                    std::cout << "\t";
                }
            }
        }
        levelCount++;
        if (levelCount == levelSize)
        {
            std::cout << std::endl;
            level++;
            levelSize = std::pow(2, level);
            levelCount = 0;
        }
    }
    std::cout << std::endl;
}
void heap::debugStuff()
{
    std::cout << "Heap: " << std::endl;
    printHeap();
    std::cout << "\nHash Table: " << std::endl;
    int mapping_filled = 0;
    // loops through the hash table
    // make sure nothing in the hash table is pointing to something that isn't in the heap
    for (int i = -10; i <= 10; i++)
    {
        std::string id = "id" + std::to_string(i);
        if (mapping.contains(id)) 
        {
            int key = static_cast<node*>(mapping.getPointer(id))->key;
            std::cout << "id" << i << ": " << key << std::endl;
            mapping_filled++;
           }
        node *node_ptr = static_cast<node *>(mapping.getPointer(id));
        if(node_ptr != NULL){
        int position = getPos(node_ptr);

        if(position > current_size)
        {
            throw "THIS IS BREAKING HERE";
        }
        }
    }
}
*/