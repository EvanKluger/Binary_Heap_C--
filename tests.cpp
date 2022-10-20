#include <string>
#include "heap.h"
#include <iostream>
#include <queue>

heap myHeap(500);
std::string id = "";
int key = 0;
int retVal = 0;
int debug = 0;

void test1()
{

    // Insert keys from Insertion Example in the powerpoint
    myHeap.insert("A", 13);
    myHeap.insert("B", 21);
    myHeap.insert("C", 16);
    myHeap.insert("D", 24);
    myHeap.insert("E", 31);
    myHeap.insert("F", 19);
    myHeap.insert("G", 68);
    myHeap.insert("H", 65);
    myHeap.insert("I", 26);
    myHeap.insert("J", 32);
    myHeap.insert("K", 14);

    // deleteMin's and check that it's working
    int last = -999999;
    for (int i = 0; i < 11; i++)
    {
        retVal = myHeap.deleteMin(&id, &key);

        //std::cout << "\ndeleteMin returned: " << retVal << " id: " << id << " key: " << key << std::endl;

        if (key < last) {
            std::cout << "test failed" << std::endl;
        }
        last = key;
    }

    std::cout << "success" << std::endl;


}

void test2()
{
    // Sables expected output
    if (myHeap.insert("string one", 35) != 0)
        throw "test failed";
    if (myHeap.insert("string two", 55) != 0)
        throw "test failed";
    if (myHeap.insert("string three", 45) != 0)
        throw "test failed";
    if (myHeap.insert("string four", 5) != 0)
        throw "test failed";
    if (myHeap.insert("string two", 10) != 2)
        throw "test failed";
    if (myHeap.insert("string five", 80) != 0)
        throw "test failed";
    if (myHeap.insert("string six", 20) != 0)
        throw "test failed";
    if (myHeap.insert("string seven", 70) != 0)
        throw "test failed";
    if (myHeap.deleteMin(&id, &key) != 0)
        throw "test failed";
    if (id != "string four" || key != 5)
        throw "test failed";
    if (myHeap.remove("string four", &key) != 1)
        throw "test failed";
    if (myHeap.deleteMin(&id, &key) != 0)
        throw "test failed";
    if (id != "string six" || key != 20)
        throw "test failed";
    if (myHeap.setKey("string one", 50) != 0)
        throw "test failed";
    if (myHeap.remove("string two", &key) != 0)
        throw "test failed";
    if (myHeap.deleteMin(&id, &key) != 0)
        throw "test failed";
    if (id != "string three" || key != 45)
        throw "test failed";
    if (myHeap.deleteMin(&id, &key) != 0)
        throw "test failed";
    if (id != "string one" || key != 50)
        throw "test failed";
    if (myHeap.setKey("string five", 60) != 0)
        throw "test failed";
    if (myHeap.deleteMin(&id, &key) != 0)
        throw "test failed";
    if (id != "string five" || key != 60)
        throw "test failed";
    if (myHeap.deleteMin(&id, &key) != 0)
        throw "test failed";
    if (id != "string seven" || key != 70)
        throw "test failed";
    if (myHeap.deleteMin(&id, &key) != 1)
        throw "test failed"; 


}

void test3()
{

    // perform random tests until something fails
    while (1)
    {
        std::cout << "\n\n---------------------" << std::endl;

        int num = rand() % 4;
        int key = rand() % 20 - 10;
        int idNum = rand() % 20 - 10;
        std::string id = "id" + std::to_string(idNum);

        switch (num)
        {
        case 0:
            retVal = myHeap.insert(id, key);
            std::cout << "\ninsert:" << std::endl;
            std::cout << id << ": " << key;
            std::cout << "\nreturn: " << retVal << "\n" << std::endl;
            break;
        case 1:
            //TODO: this is litterally doing nothing so make id independent of key
            retVal = myHeap.setKey(id, key);
            std::cout << "\nsetKey:" << std::endl;
            std::cout << id << ": " << key;
            std::cout << "\nreturn: " << retVal << "\n" << std::endl;
            break;
        case 2:
            retVal = myHeap.remove(id, &key);
            std::cout << "\nremove:" << std::endl;
            std::cout << id << ": " << key;
            std::cout << "\nreturn: " << retVal << "\n" << std::endl;
            break;
        case 3:
            retVal = myHeap.deleteMin(&id, &key);
            std::cout << "\ndeleteMin:" << std::endl;
            std::cout << id << ": " << key;
            std::cout << "\nreturn: " << retVal << "\n" << std::endl;
            break;
        }
        myHeap.debugStuff();
        std::cout << "\ndebug: " << debug++ << std::endl;

        std::cout << "---------------------\n\n" << std::endl;
    }
}