#include <iostream>
#include <vector>

using byte = unsigned char; //basically just 8 bytes

struct header_t {
	std::size_t size;
	bool isFree; //this block does not get removed, it is just no longer used
	header_t* next;
};

class MemoryManager { //https://developer.ibm.com/tutorials/au-memorymanager/
private:
	static std::shared_ptr<MemoryManager> instance;
	byte* masterBlock; //collection of bytes
	std::size_t blockIterator;

	MemoryManager(std::size_t masterBlockSize) :masterBlock(nullptr) {
		masterBlock = static_cast<byte*>(malloc(masterBlockSize));
		blockIterator = 0;
		std::cout << "Master block is " << masterBlockSize << " bytes" << std::endl;
	}
public:

	static std::shared_ptr<MemoryManager> GetInstance() {
		if (!instance) {
			instance = std::shared_ptr<MemoryManager>(new MemoryManager(1024));
		}
		return instance;
	}
	void* allocate(std::size_t memorySize) {
		void* preIterate = &masterBlock[blockIterator];
		blockIterator += memorySize;
		return preIterate;
		//return &masterBlock[blockIterator += memorySize];
	}
	~MemoryManager() {
		if (masterBlock) free(masterBlock);
		std::cout << "Freed the MasterBlock" << std::endl;
	}
};
std::shared_ptr<MemoryManager> MemoryManager::instance = 0;

static std::size_t memoryAllocated = 0;

void* operator new(std::size_t memorySize) {
	if (memorySize == 0) { memorySize++; }
	std::cout << "allocating " << memorySize << " bytes of memory\n";
	memoryAllocated += memorySize;
	return MemoryManager::GetInstance()->allocate(memorySize);
	//return malloc(memorySize);
}

void operator delete(void* memoryLocation, std::size_t memorySize) {
	std::cout << "freeing " << memorySize << " bytes of memory\n";
	memoryAllocated -= memorySize;
	free(memoryLocation);
}

struct Vec3 {
	float x, y, z;
	Vec3() {
		x = y = z = 0.0f;
	}
};

int main(int agrc, char* argv[]) {
	MemoryManager::GetInstance();

	Vec3* vPtr = new Vec3();
	delete vPtr;

	std::unique_ptr<Vec3> v = std::make_unique<Vec3>();

	std::vector<Vec3> vectors;
	vectors.reserve(32);
	for (int i = 0; i < 32; i++) {
		vectors.push_back(Vec3());
	}
	vectors.~vector();
	std::cout << memoryAllocated << std::endl;
}