#pragma once
#include <memory>
#include <iostream>
#include "SList.h"

//struct MemorySegment {
//	MemorySegment(void* memoryLocation_, bool isFree_) {
//		memoryLocation = memoryLocation_;
//		isFree = isFree_;
//	}
//	void* memoryLocation;
//	bool isFree = false;
//};

#define SIXTEEN_BYTES = 16;
#define ONE_HUNDRED_BYTES = 128;
#define ONE_THOUSAND_BYTES = 1024;
#define EIGHT_THOUSAND_BYTES = 8192;
#define THIRTY_TWO_THOUSAND_BYTES = 32768;

using byte = unsigned char; //basically just 8 bytes
	class MemoryManager { //https://developer.ibm.com/tutorials/au-memorymanager/
	private:
		//static std::shared_ptr<MemoryManager> instance;
		byte* masterBlock; //collection of bytes
		std::size_t sixteenByteBlockIterator;
		std::size_t oneHundredByteBlockIterator;
		std::size_t oneThousandByteBlockIterator;
		std::size_t eightThousandByteBlockIterator;
		std::size_t thirtyTwoThousandByteBlockIterator;

		std::size_t partitionSize;


		SList<void*> sixteenByteList;
		SList<void*> oneHundredByteList;
		SList<void*> oneThousandByteList;
		SList<void*> eightThousandByteList;
		SList<void*> thirtyTwoThousandByteList;

		MemoryManager() {
			masterBlock = static_cast<byte*>(malloc(1024));
			//blockIterator = 0;
			partitionSize = 1024 / 4;

			sixteenByteBlockIterator = 0;
			oneHundredByteBlockIterator = partitionSize;
			oneThousandByteBlockIterator = (partitionSize * 2);
			eightThousandByteBlockIterator = (partitionSize * 3);
			thirtyTwoThousandByteBlockIterator = (partitionSize * 4);

			std::cout << "Master block is " << 1024 << " bytes" << std::endl;
		}

	public:
		MemoryManager(std::size_t masterBlockSize) :masterBlock(nullptr) {
			masterBlock = static_cast<byte*>(malloc(masterBlockSize));
			partitionSize = masterBlockSize / 5;

			sixteenByteBlockIterator = 0;
			oneHundredByteBlockIterator = partitionSize;
			oneThousandByteBlockIterator = (partitionSize * 2);
			eightThousandByteBlockIterator = (partitionSize * 3);
			thirtyTwoThousandByteBlockIterator = (partitionSize * 4);

			std::cout << "Master block is " << masterBlockSize << " bytes" << std::endl;
		}
		/*static std::shared_ptr<MemoryManager> GetInstance() {
			if (!instance) {
				instance = std::shared_ptr<MemoryManager>(new MemoryManager);
			}
			return instance;
		}*/

		~MemoryManager() {
			if (masterBlock) free(masterBlock);
			std::cout << "Freed the MasterBlock" << std::endl;
		}
		void* allocate(std::size_t memorySize);
		void deallocate(void* memoryLocation, std::size_t memorySize);
	};

