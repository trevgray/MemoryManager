#include "MemoryManager.h"

void* MemoryManager::allocate(std::size_t memorySize) {
	if (memorySize == 8) { //for the vector allocate
		return malloc(memorySize);
	}
	void* preIterate = &masterBlock[sixteenByteBlockIterator];
	sixteenByteBlockIterator += memorySize;
	sixteenByteList.push_front(preIterate);
	return preIterate;
	//return &masterBlock[blockIterator += memorySize];
}

void MemoryManager::deallocate(void* memoryLocation, std::size_t memorySize) {
	if (sixteenByteList.size() != 0) {
		sixteenByteBlockIterator -= memorySize;
		SList<void*>::Iterator location = sixteenByteList.find(memoryLocation);
		sixteenByteList.erase(location);
	}
	else { //for the vector deallocate
		free(memoryLocation);
		//throw std::invalid_argument("Fatal Error: Can't Find Memory Location");
	}
}

//std::shared_ptr<MemoryManager> MemoryManager::instance = 0;