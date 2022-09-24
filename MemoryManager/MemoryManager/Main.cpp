#include <iostream>
#include <memory>
#include <vector>

void* operator new(std::size_t amount) {
	std::cout << "allocating " << amount << " bytes of memory\n";
	return malloc(amount);
}

void operator delete(void* memoryLocation, std::size_t amount) {
	std::cout << "freeing " << amount << " bytes of memory\n";
	free(memoryLocation);
}

struct Vec3 {
	float x, y, z;
	Vec3() {
		x = y = z = 0.0f;
	}
};

int main() {
	Vec3* vPtr = new Vec3();
	delete vPtr;

	std::unique_ptr<Vec3> v = std::make_unique<Vec3>();

	std::vector<Vec3> vectors;
	vectors.reserve(32);
	for (int i = 0; i < 32; i++) {
		vectors.push_back(Vec3());
	}
}