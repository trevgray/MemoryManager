#include <iostream>
#include <vector>
#include "MemoryManager.h"

static std::size_t memoryAllocated = 0;

MemoryManager mm = MemoryManager(5000000);

void* operator new(std::size_t memorySize) {
	if (memorySize == 0) { memorySize++; }
	std::cout << "allocating " << memorySize << " bytes of memory\n";
	memoryAllocated += memorySize;
	return mm.allocate(memorySize);
}

void operator delete(void* memoryLocation, std::size_t memorySize) {
	std::cout << "freeing " << memorySize << " bytes of memory\n";
	memoryAllocated -= memorySize;
	mm.deallocate(memoryLocation, memorySize);
}

struct Vec3 {
	float x, y, z;
	Vec3() {
		x = y = z = 0.0f;
	}
};

int main(int agrc, char* argv[]) {

	Vec3* vPtr = new Vec3();
	
	//std::unique_ptr<Vec3> v = std::make_unique<Vec3>();

	//std::vector<Vec3> vectors;
	////vectors.reserve(32);
	//for (int i = 0; i < 32; i++) {
	//	vectors.push_back(Vec3());
	//}
	
	Vec3* vPtr2 = new Vec3();
	delete vPtr;
	delete vPtr2;
	Vec3* vPtr3 = new Vec3();
	delete vPtr3;
	//vectors.~vector();

	std::cout << memoryAllocated << std::endl;
}