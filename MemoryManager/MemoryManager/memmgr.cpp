#include <stdio.h>
#include <vector>
#include <string>
using namespace std;



#include "memmgr.h"
#include "classes.h"
#include <iostream>

MemoryManager gMemoryManager;

void* MemoryManager::allocate(size_t size)
  {
  void* base = 0;
  switch(size)
    {
    case JOB_SCHEDULER_SIZE :  //28
      {
      if(Byte32PtrList.empty())
        {
        base = new char [32 * POOL_SIZE];
        MemoryPoolList.push_back(base);
        InitialiseByte32List(base);
        }
      void* blockPtr =  Byte32PtrList.front();
      *((static_cast<char*>(blockPtr)) + 30) = 32; //size of block set
      *((static_cast<char*>(blockPtr)) + 31) = 0; //block is no longer free
      Byte32PtrList.pop_front();
      return blockPtr;
      }         
    case COORDINATE_SIZE :  //36
      {
      if(Byte40PtrList.empty())
        {
        base = new char [40 * POOL_SIZE];
        MemoryPoolList.push_back(base);
        InitialiseByte40List(base);
        }
      void* blockPtr =  Byte40PtrList.front();
      *((static_cast<char*>(blockPtr)) + 38) = 40; //size of block set
      *((static_cast<char*>(blockPtr)) + 39) = 0; //block is no longer free
      Byte40PtrList.pop_front();
      return blockPtr;
      }         
    case COMPLEX_SIZE : //16
      {
      if(Byte24PtrList.empty())
        {
        base = new char [24 * POOL_SIZE];
        MemoryPoolList.push_back(base);
        InitialiseByte24List(base);
        }
      void* blockPtr =  Byte24PtrList.front();
      *((static_cast<char*>(blockPtr)) + 22) = 32; //size of block set
      *((static_cast<char*>(blockPtr)) + 23) = 0; //block is no longer free
      //std::cout << &(static_cast<char*>(blockPtr)[0]) + 20 << std::endl;
      //std::cout << &(static_cast<char*>(blockPtr)[0]) + 21 << std::endl;
      Byte24PtrList.pop_front();
      return blockPtr;
      }
    default : break;
    }
  return 0;
  }

void MemoryManager::deallocate(void* object) {
  char* init = static_cast<char*>(object);
  //std::cout << &(static_cast<char*>(object)[0]) + 20 << std::endl;
  //std::cout << init + 20 << std::endl;

  //char* test1 = &(static_cast<char*>(object)[0]) + 20;
  //char* test2 = &(static_cast<char*>(object)[0]) + 21;

  /*for (size_t x = 0; x < 100; x++) {
      std::cout << &(static_cast<unsigned int*>(object)[0]) + x << "  |||||  " << guardByte1 << std::endl;
  }*/

  //std::cout << &(static_cast<char*>(object)[0]) + 29 << "  |||||  " << guardByte1 << std::endl;
  
  while(true) {
    int count = 0;
    while(*init != guardByte1) {//this loop shall never iterate more than 
                          // MAX_BLOCK_SIZE times and hence is O(1)
        std::cout << *init << " |||| " << guardByte1 << std::endl;
    init++;
    count++;
    if(count > MAX_BLOCK_SIZE) {
        std::cout << *init << "  |||||  " << guardByte1 << std::endl;
        printf ("runtime heap memory corruption near %d", object);
        exit(1);
        } 
    }
    if((*++init) == guardByte2)  // we have hit the guard bytes
      break;  // from the outer while 
    }
  init++;  // ignore size byte
  init++;
  *init = 1; // set free/available byte   

  //guardByte1 = guardByte1; //what is happening here????
  }

void MemoryManager::InitialiseByte24List(void* base)
  {
  for (int i = 0; i< POOL_SIZE; ++i)
    {
    char* guardByteStart = &(static_cast<char*>(base)[i*24]) + 20;
    *guardByteStart = 0xde;
    guardByte1 = *guardByteStart;

    guardByteStart++; 
    *guardByteStart = 0xad;   //end of block
    guardByte2 = *guardByteStart;

    guardByteStart++;
    *guardByteStart = 24;     //sizeof block
    guardByteStart++;
    *guardByteStart = 1;      //block  available
    Byte24PtrList.push_front(&(static_cast<char*>(base)[i*24])); 
    }
  }

void MemoryManager::InitialiseByte32List(void* base)
  {
  for (int i = 0; i< POOL_SIZE; ++i)
    {
    char* guardByteStart = &(static_cast<char*>(base)[i*32]) + 28;
    *guardByteStart = 0xde;
    guardByte1 = *guardByteStart;

    guardByteStart++; 
    *guardByteStart = 0xad;   //end of block
    guardByte2 = *guardByteStart;

    guardByteStart++;
    *guardByteStart = 32;     //sizeof block
    guardByteStart++;
    *guardByteStart = 1;      //block  available
    Byte32PtrList.push_front(&(static_cast<char*>(base)[i*32])); 
    }
  }

void MemoryManager::InitialiseByte40List(void* base)
  {
  for (int i = 0; i< POOL_SIZE; ++i)
    {
    char* guardByteStart = &(static_cast<char*>(base)[i*40]) + 36;
    *guardByteStart = 0xde;
    guardByteStart++; 
    *guardByteStart = 0xad;   //end of block
    guardByteStart++;
    *guardByteStart = 40;     //sizeof block
    guardByteStart++;
    *guardByteStart = 1;      //block  available
    Byte40PtrList.push_front(&(static_cast<char*>(base)[i*40]));
    }
  }
