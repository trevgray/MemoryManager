#include "MemoryManager.h"

void* MemoryManager::allocate(std::size_t memorySize) {
	if (memorySize == 8) { //for the vector allocate
		return malloc(memorySize);
	}
	void* preIterate = &masterBlock[sixteenByteBlockIterator];
	sixteenByteList[sixteenByteBlockIterator / 16] = preIterate;
	sixteenByteBlockIterator += 16;
	return preIterate;
	//return &masterBlock[blockIterator += memorySize];
}

void MemoryManager::deallocate(void* memoryLocation, std::size_t memorySize) {
	for (int x = 0; x < 32; x++) {
		if (sixteenByteList[x] == memoryLocation) {
			sixteenByteList[x] = nullptr;
		}
	}

	if (memorySize == 8) { //for the vector deallocate
		free(memoryLocation);
		//throw std::invalid_argument("Fatal Error: Can't Find Memory Location");
	}
}

//std::shared_ptr<MemoryManager> MemoryManager::instance = 0;