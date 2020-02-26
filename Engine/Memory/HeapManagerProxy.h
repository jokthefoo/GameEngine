#ifndef __HEAP_MANAGER_PROXY_H
#define __HEAP_MANAGER_PROXY_H

#include <stdint.h>
#include "HeapManager.h"

namespace HeapManagerProxy
{

Engine::Memory::HeapManager *	CreateHeapManager( void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors );
void			Destroy(Engine::Memory::HeapManager * i_pManager );

void *			alloc(Engine::Memory::HeapManager * i_pManager, size_t i_size );
void *			alloc(Engine::Memory::HeapManager * i_pManager, size_t i_size, unsigned int i_alignment );
bool			free(Engine::Memory::HeapManager * i_pManager, void * i_ptr );

void			Collect(Engine::Memory::HeapManager * i_pManager );

bool			Contains( const Engine::Memory::HeapManager * i_pManager, void * i_ptr );
bool			IsAllocated( const Engine::Memory::HeapManager * i_pManager, void * i_ptr );

size_t			GetLargestFreeBlock( const Engine::Memory::HeapManager * i_pManager );
size_t			GetTotalFreeMemory( const Engine::Memory::HeapManager * i_pManager );

void			ShowFreeBlocks( const Engine::Memory::HeapManager * i_pManager );
void			ShowOutstandingAllocations( const Engine::Memory::HeapManager * i_pManager );

} // namespace HeapManagerProxy

#endif // __HEAP_MANAGER_PROXY_H