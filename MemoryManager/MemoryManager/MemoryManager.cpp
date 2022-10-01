#include "MemoryManager.h"

void* MemoryManager::allocate(std::size_t memorySize) {
	if (memorySize == 8) { //for the vector allocate
		return malloc(memorySize);
	}
	for (int nineteenByteBlockIterator = 0; nineteenByteBlockIterator < partitionSize; nineteenByteBlockIterator += 19) {
		void* preIterate = &masterBlock[nineteenByteBlockIterator];
		char* guardByteStart = &(static_cast<char*>(preIterate)[0]) + 18;
		//std::cout << *guardByteStart << std::endl;
		if (*guardByteStart != 1) { //finish first available block
			*guardByteStart = 1;      //block  unavailable

			nineteenByteList[nineteenByteBlockIterator / 19] = preIterate; //add it to the nineteen byte list
			return preIterate;
		}
	}
	return nullptr;
	//return &masterBlock[blockIterator += memorySize];
}

void MemoryManager::deallocate(void* memoryLocation, std::size_t memorySize) {
	if (memorySize == 8) { //for the vector deallocate
		free(memoryLocation);
		return;
		//throw std::invalid_argument("Fatal Error: Can't Find Memory Location");
	}
	for (int x = 0; x < nineteenByteListSize; x++) { //loop through all the nineteen byte objects
		if (nineteenByteList[x] == memoryLocation) { //check if it == the memory location
			char* guardByteStart = &(static_cast<char*>(memoryLocation)[0]) + 16; //we should probably check the guard bits here
			*guardByteStart = 0xde;
			guardByteStart++;
			*guardByteStart = 0xad;   //end of block
			guardByteStart++;
			*guardByteStart = 0;      //block  available
			return;
		}
	}
}

void MemoryManager::Initialize() {
	for (int nineteenByteBlockIterator = 0; nineteenByteBlockIterator < partitionSize; nineteenByteBlockIterator += 19) { //loop through all objects and default there values
		void* iterator = &masterBlock[nineteenByteBlockIterator];
		char* guardByteStart = &(static_cast<char*>(iterator)[0]) + 16;
		*guardByteStart = 0xde;
		guardByteStart++;
		*guardByteStart = 0xad;   //end of block
		guardByteStart++;
		*guardByteStart = 0;      //block  available
		//std::cout << *guardByteStart << std::endl;
	}
}

//std::shared_ptr<MemoryManager> MemoryManager::instance = 0;