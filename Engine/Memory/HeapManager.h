#pragma once

#include "../Containers/LinkedList.h"

namespace Engine
{
	namespace Memory
	{

		struct blockHeader
		{
			size_t size;
			unsigned int free;
			struct blockHeader * next;
			size_t padding;
		};

		class HeapManager
		{
			friend bool	HeapManager_UnitTest();
		public:
			// create a new HeapManager
			static HeapManager * create(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);
			// destroy the HeapManager
			void	destroy();

			// allocate - with and without alignment requirement
			void *	_alloc(size_t i_size);
			blockHeader * get_first_free(size_t size);
			void *	_alloc(size_t i_size, unsigned int i_alignment);
			// free
			bool	_free(void * i_ptr);

			// run garbage collection
			void	collect();

			// query whether a given pointer is within this Heaps memory range
			bool	Contains(void * i_ptr) const;
			// query whether a given pointer is an outstanding allocation
			bool	IsAllocated(void * i_ptr) const;

			size_t	getLargestFreeBlock() const;
			size_t	getTotalFreeMemory() const;

			void ShowAllocs() const;
			void ShowFreeBlocks() const;
		private:
			void * head;
			blockHeader * bhead;
			void * initHeap;
			size_t totSize;
			size_t freeCount;
			LinkedList<char *> freeList;
		};
	}
}