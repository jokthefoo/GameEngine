#include "HeapManager.h"
#include <stdio.h>
#include "../Containers/LinkedList.h"

namespace Engine
{
	namespace Memory
	{
		HeapManager * HeapManager::create(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
		{
			HeapManager * man = new HeapManager();
			if (!man)
			{
				return nullptr;
			}
			(*man).initHeap = i_pMemory;
			(*man).totSize = i_sizeMemory;
			
			//printf("%d   %p\n", i_sizeMemory,i_pMemory);

			struct blockHeader * header;
			struct blockHeader * endBlock;


			//End block so we don't go out of our allocated memory
			void* endLoc = static_cast<char*>(i_pMemory) + i_sizeMemory - sizeof(struct blockHeader);
			endBlock = static_cast<blockHeader*>(endLoc);

			endBlock->size = 0;
			endBlock->free = 0;
			endBlock->next = NULL;
			endBlock->padding = 0;



			header = static_cast<blockHeader*>(i_pMemory);

			size_t size = i_sizeMemory - sizeof(struct blockHeader) * 2;

			header->size = size;
			header->free = 1;
			header->next = NULL;
			header->padding = 0;

			(*man).freeCount++;

			//void * firstFree = static_cast<void*>(header+1);

			(*man).head = header;
			(*man).bhead = header;
			//(*man).freeList.Add(static_cast<char*>(firstFree));


			/*
			*(static_cast<size_t*>(i_pMemory)) = i_sizeMemory - sizeof(size_t);

			void * end = (char*)i_pMemory + i_sizeMemory - sizeof(size_t);
			*(static_cast<size_t*>(end)) = 0;

			void * firstFree = static_cast<char*>(i_pMemory) + sizeof(size_t);

			(*man).head = firstFree;
			(*man).freeList.Add(static_cast<char*>(firstFree));
			*/

			return man;
		}

		void HeapManager::destroy()
		{
		}

		void * HeapManager::_alloc(size_t i_size)
		{
			if (i_size == 0)
				return nullptr;

			struct blockHeader* header;
			header = get_first_free(i_size);
			if (header)
			{
				if (header->size >= i_size + sizeof(struct blockHeader) * 2)
				{
					size_t newSize = header->size - i_size;
					struct blockHeader * newFree;

					//Split free block before allocating
					void* newFreeLoc = (static_cast<char*>(static_cast<void*>(header + 1))) + i_size;
					newFree = static_cast<blockHeader*>(newFreeLoc);

					header->size = i_size;
					header->free = 0;
					header->padding = 0;

					newFree->size = newSize - sizeof(struct blockHeader);
					newFree->free = 1;
					newFree->next = NULL;
					newFree->padding = 0;

					//fix free list
					if (!bhead->free)
					{
						bhead = bhead->next;
					}

					if (!bhead)
					{
						bhead = newFree;
					}
					else
					{
						newFree->next = bhead;
						bhead = newFree;
					}

					header->next = NULL;
				}
				else
				{
					freeCount--;
					header->free = 0;
					header->next = NULL;
					header->padding = 0;
				}
				return static_cast<void*>(header + 1);
			}
			else
			{
				// Did not find any free blocks
				return nullptr;
			}
			/* Old implementation
			char * curPos = static_cast<char*>(head);
			size_t curSize = *(reinterpret_cast<size_t*>((curPos - sizeof(size_t))));

			// Find first free fit
			while (curSize != 0)
			{
				// Allocate if fit
				if (curSize >= i_size + sizeof(size_t))
				{
					size_t reqSize = i_size + sizeof(size_t);
					// Don't fragment if free block is small
					if (curSize <= reqSize + sizeof(size_t))
					{
						reqSize += sizeof(size_t);
					}
					curPos -= sizeof(size_t);
					*(reinterpret_cast<size_t*>(curPos)) = reqSize;
					curPos += sizeof(size_t);

					// Split free block
					char * newPos = curPos + reqSize;
					*(reinterpret_cast<size_t*>(newPos)) = curSize - reqSize;

					freeList.Remove(curPos);
					freeList.Add(newPos);

					return curPos;
				}
				else
				{
					curPos += curSize + sizeof(size_t);
					curSize = *(reinterpret_cast<size_t*>((curPos - sizeof(size_t))));
				}
			}
			// If no fit found return null
			return nullptr;
			*/
		}

		struct blockHeader * HeapManager::get_first_free(size_t size)
		{
			struct blockHeader* current = bhead;
			struct blockHeader* prev = NULL;
			size_t i = 0;
			while (current && i < freeCount)
			{
				i++;
				if (current->free && current->size >= size)
				{
					//Remove from free list
					if (prev)
					{
						prev->next = current->next;
					}

					return current;
				}
				prev = current;
				current = current->next;
			}
			return NULL;
		}

		void * HeapManager::_alloc(size_t i_size, unsigned int i_alignment)
		{
			void* ptr = _alloc(i_size + i_alignment + sizeof(size_t));
			if (ptr == nullptr)
			{
				return ptr;
			}

			ptr = static_cast<char*>(ptr) + sizeof(size_t);

			unsigned int res = reinterpret_cast<size_t>(ptr) % i_alignment;
			size_t pad = i_alignment - res;
			if (res != 0)
			{
				ptr = static_cast<char*>(ptr) + pad;
			}
			else
			{
				pad = 0;
			}

			size_t* paddingPtr = static_cast<size_t*>(ptr) - 1;
			*paddingPtr = pad + sizeof(size_t);

			return ptr;
		}

		bool HeapManager::_free(void * i_ptr)
		{
			struct blockHeader* header;

			if (!i_ptr)
			{
				return false;
			}

			size_t* paddingPtr = static_cast<size_t*>(i_ptr) - 1;
			if (*paddingPtr)
			{
				i_ptr = static_cast<char*>(i_ptr) - *paddingPtr;
			}

			header = static_cast<struct blockHeader*>(i_ptr) - 1;
			if (header->free == 1)
			{
				//Already free
				return true;
			}

			if (header->size == 0)
			{
				//Can't free end block
				return false;
			}

			header->free = 1;
			header->next = bhead;
			bhead = header;

			if (bhead == bhead->next)
			{
				bhead->next = NULL;
			}

			//this->collect();

			freeCount++;
			return true;
			/* old implementation
			char * curPos = static_cast<char*>(head);
			size_t curSize = *(reinterpret_cast<size_t*>((curPos - sizeof(size_t))));

			while (curPos != nullptr)
			{
				if (static_cast<void*>(curPos) == i_ptr)
				{
					free(curPos);
					// Check coalescing
					char * nextPos = curPos + curSize + sizeof(size_t);
					size_t nextSize = *(reinterpret_cast<size_t*>((nextPos - sizeof(size_t))));
					if (freeList.Remove(nextPos))
					{
						curSize = *(reinterpret_cast<size_t*>((curPos - sizeof(size_t))));
						*(reinterpret_cast<size_t*>((curPos - sizeof(size_t)))) = curSize + nextSize + sizeof(size_t);
					}
					freeList.Add(curPos);
					return true;
				}
				else
				{
					curPos += curSize + sizeof(size_t);
					curSize = *(reinterpret_cast<size_t*>((curPos - sizeof(size_t))));
				}
			}
			// If block not found return false
			return false;
			*/
		}

		void HeapManager::collect()
		{
			struct blockHeader* current = bhead;
			char* curPos = reinterpret_cast<char*>(bhead);
			struct blockHeader* next;
			char* nextPos;
			size_t curSize;
			while (current)
			{
				curSize = current->size;
				nextPos = curPos + curSize + sizeof(struct blockHeader);
				next = reinterpret_cast<struct blockHeader*>(nextPos);
				if (next->free)
				{
					//if next free
					next->free = 0;
					curSize += next->size + sizeof(struct blockHeader);
					current->size = curSize;

					freeCount--;
					//remove from free list
				}
				else
				{
					// if next not free
					current = current->next;
					if (current)
					{
						curPos = reinterpret_cast<char*>(current);
					}
				}
			}

			while (bhead && !bhead->free)
			{
				bhead = bhead->next;
			}

			current = bhead;
			struct blockHeader* temp;
			while (current)
			{
				temp = current->next;
				while (temp)
				{
					current->next = temp;
					if (temp->free)
					{
						break;
					}
					else
					{
						temp = temp->next;
					}
				}
				current = current->next;
			}

			if (bhead && bhead->next && !bhead->next->free)
			{
				bhead->next = NULL;
			}
			/* old implementation
			for (int i = 0; i < freeList.Count(); i++)
			{
				char* curPos = freeList.GetAt(i);
				size_t curSize = *(reinterpret_cast<size_t*>((curPos - sizeof(size_t))));

				char * nextPos = curPos + curSize + sizeof(size_t);
				size_t nextSize = *(reinterpret_cast<size_t*>((nextPos - sizeof(size_t))));

				if (freeList.Remove(nextPos))
				{
					curSize = *(reinterpret_cast<size_t*>((curPos - sizeof(size_t))));
					*(reinterpret_cast<size_t*>((curPos - sizeof(size_t)))) = curSize + nextSize + sizeof(size_t);
				}
			}*/
		}

		bool HeapManager::Contains(void * i_ptr) const
		{
			return true;
		}

		bool HeapManager::IsAllocated(void * i_ptr) const
		{
			size_t* paddingPtr = static_cast<size_t*>(i_ptr) - 1;
			if (*paddingPtr)
			{
				i_ptr = static_cast<char*>(i_ptr) - *paddingPtr;
			}

			struct blockHeader* header = static_cast<struct blockHeader*>(i_ptr) - 1;

			return !header->free;
		}

		size_t HeapManager::getLargestFreeBlock() const
		{
			struct blockHeader* current = bhead;
			size_t largest = 0;
			while (current)
			{
				if (current->size > largest)
				{
					largest = current->size;
				}
				current = current->next;
			}
			return largest;
		}

		size_t HeapManager::getTotalFreeMemory() const
		{
			struct blockHeader* current = bhead;
			size_t total = 0;
			while (current)
			{
				total += current->size;
				current = current->next;
			}
			return total;
		}

		void HeapManager::ShowAllocs() const
		{
			printf("All blocks\n");
			char* curPos = static_cast<char*>(head);
			size_t curSize = static_cast<blockHeader*>(head)->size;
			size_t free = static_cast<blockHeader*>(head)->free;
			while (curSize != 0)
			{
				printf("Size: %zu   Loc: %p   Free: %zu\n", curSize, curPos, free);
				curPos += curSize + sizeof(struct blockHeader);
				curSize = reinterpret_cast<blockHeader*>(curPos)->size; 
				free = reinterpret_cast<blockHeader*>(curPos)->free;
			}

			/*
			char * curPos = (char*)head;
			size_t curSize = *(reinterpret_cast<size_t*>((curPos - sizeof(size_t))));
			
			while (curSize != 0)
			{
				printf("Size: %zu   Loc: %p\n", curSize, curPos);
				curPos += curSize + sizeof(size_t);
				curSize = *(reinterpret_cast<size_t*>((curPos - sizeof(size_t))));
			}*/

		}

		void HeapManager::ShowFreeBlocks() const
		{
			printf("Free blocks\n");
			struct blockHeader* current = bhead;
			size_t i = 0;
			while (current && i < freeCount)
			{
				i++;
				printf("Size: %zu   Loc: %p   Free: %d\n", current->size, current, current->free);
				current = current->next;
			}
			/*
			for (int i = 0; i < freeList.Count(); i++)
			{
				size_t curSize = *(reinterpret_cast<size_t*>((freeList.GetAt(i) - sizeof(size_t))));
				printf("Size: %zu   Loc: %p\n", curSize, freeList.GetAt(i));
			}
			*/
		}
	}
}