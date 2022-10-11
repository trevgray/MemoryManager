#include <iostream>
#include <vector>
#include "MemoryManager.h"

static std::size_t memoryAllocated = 0;
static std::size_t timesNewCalled = 0;
static std::size_t timesDeleteCalled = 0;

static std::size_t maxMemoryAllocated = 0;
static std::size_t minMemoryAllocated = 0;

MemoryManager mm = MemoryManager(6000000);

void* operator new(std::size_t memorySize) {
	if (memorySize == 0) { memorySize++; }

	if (memorySize < minMemoryAllocated || minMemoryAllocated == 0) { minMemoryAllocated = memorySize; }
	if (memorySize > maxMemoryAllocated) { maxMemoryAllocated = memorySize; }
	//std::cout << "allocating " << memorySize << " bytes of memory\n";
	memoryAllocated += memorySize;
	timesNewCalled++;
	return mm.allocate(memorySize);
}

void operator delete(void* memoryLocation, std::size_t memorySize) {
	//std::cout << "freeing " << memorySize << " bytes of memory\n";
	memoryAllocated -= memorySize;
	timesDeleteCalled++;
	mm.deallocate(memoryLocation, memorySize);
}

void* operator new[](std::size_t memorySize)
{
	if (memorySize == 0) { memorySize++; }

	if (memorySize < minMemoryAllocated || minMemoryAllocated == 0) { minMemoryAllocated = memorySize; }
	if (memorySize > maxMemoryAllocated) { maxMemoryAllocated = memorySize; }
	//std::cout << "allocating " << memorySize << " bytes of memory\n";
	memoryAllocated += memorySize;
	timesNewCalled++;
	return mm.allocate(memorySize);
}

//void operator delete[](void* memoryLocation, std::size_t memorySize) noexcept
//{
//	mm.deallocate(memoryLocation, memorySize);
//}

//void operator delete[](void* memoryLocation)
//{
//	std::cout << _msize(memoryLocation) << std::endl;
//	mm.deallocate(memoryLocation, 11);
//}

struct Vec3 {
	float x, y, z;
	Vec3() {
		x = y = z = 0.0f;
	}
	Vec3(int a) {
		x = y = z = 1.0f;
	}
};

int main(int agrc, char* argv[]) {
	char* buffer = nullptr;
	int bufferSize = 10;
	//buffer = new char;
	buffer = new char[(int)(bufferSize + 1)];

	::operator delete(buffer, 11);

	Vec3* vPtr = new Vec3();
	
	//std::unique_ptr<Vec3> v = std::make_unique<Vec3>();

	std::vector<Vec3> vectors;
	//vectors.reserve(32);
	for (int i = 0; i < 32; i++) {
		vectors.push_back(Vec3());
	}
	
	Vec3* vPtr2 = new Vec3();
	Vec3* vPtr3 = new Vec3(1);
	delete vPtr;
	delete vPtr2;
	delete vPtr3;
	vectors.~vector();

	std::cout << "memoryAllocated " << memoryAllocated << std::endl;
	std::cout << "timesNewCalled " << timesNewCalled << std::endl;
	std::cout << "timesDeleteCalled " << timesDeleteCalled << std::endl;
	std::cout << "maxMemoryAllocated " << maxMemoryAllocated << std::endl;
	std::cout << "minMemoryAllocated " << minMemoryAllocated << std::endl;
}