#include "MemoryManager.h"
#include <iostream>
#include <vector>

std::size_t memoryUsed;

void* operator new(std::size_t amount) {
	std::cout << "allocating " << amount << " bytes of memory\n";
	memoryUsed += amount;
	return malloc(amount);
}

void operator delete(void* memoryLocation, std::size_t amount) {
	std::cout << "freeing " << amount << " bytes of memory\n";
	memoryUsed -= amount;
	free(memoryLocation);
}

struct Vec3 {
	float x, y, z;
	Vec3() {
		x = y = z = 0.0f;
	}
};

int main() {
	using namespace MEMORYMANAGER;
	memoryUsed = 0;

	Vec3* vPtr = new Vec3();
	delete vPtr;

	std::unique_ptr<Vec3> v = std::make_unique<Vec3>();

	std::vector<Vec3> vectors;
	vectors.reserve(32);
	for (int i = 0; i < 32; i++) {
		vectors.push_back(Vec3());
	}
	vectors.~vector();
	std::cout << memoryUsed << std::endl;
}