/*
#include "NewDel.h"
#include "Memory/HeapManager.h"

Engine::Memory::HeapManager defaultHeapManager;

void * operator new(size_t size)
{
	return defaultHeapManager._alloc(size, 4);
}

void * operator new(size_t size, Alignment i_align)
{
	switch (i_align)
	{
		case ALIGN_16:
		case ALIGN_32:
			return defaultHeapManager._alloc(size, i_align);
		default:
			return defaultHeapManager._alloc(size, 4);
	}
}

void * operator new[](size_t size)
{
	return defaultHeapManager._alloc(size, 4);
}

void operator delete(void * ptr)
{
	if (ptr)
	{
		defaultHeapManager._free(ptr);
	}
}

void operator delete(void * ptr, Alignment i_align)
{
	// Shouldn't be called
	if (ptr)
	{
		defaultHeapManager._free(ptr);
	}
}

void operator delete[](void * ptr)
{
	if (ptr)
	{
		defaultHeapManager._free(ptr);
	}
}
*/