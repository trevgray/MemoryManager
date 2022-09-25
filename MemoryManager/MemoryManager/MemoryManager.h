#pragma once
#include <memory>
#include <iostream>
namespace MEMORYMANAGER {
	class MemoryManager
	{
		void* operator new(std::size_t amount) {
			std::cout << "allocating " << amount << " bytes of memory\n";
			return malloc(amount);
		}

		void operator delete(void* memoryLocation, std::size_t amount) {
			std::cout << "freeing " << amount << " bytes of memory\n";
			free(memoryLocation);
		}
	};
}
