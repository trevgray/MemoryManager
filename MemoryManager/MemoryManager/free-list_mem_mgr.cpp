#include "memmgr.h"
#include "classes.h"
#include <iostream>

void* operator new(std::size_t memorySize) {
	if (memorySize == 0) { memorySize++; }
	std::cout << "allocating " << memorySize << " bytes of memory\n";
	return malloc(memorySize);
}

int main(int argc, char* argv[])
  {
    /*std::forward_list<int> Byte8PtrList;
    for (long i = 0; i < 100; ++i)
    {
        Byte8PtrList.push_front(1);
    }*/



  for(long i = 0; i < 50; ++i)
    {
    //JobScheduler* scheduler = new JobScheduler;
    //Coordinate*   point  = new Coordinate;
    Complex*      number = new Complex;

    //delete scheduler;
    //delete point;
    delete number;
    }
  return 0;
  }

