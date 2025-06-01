#include "Memory.hpp"

#ifdef DEBUG
	#include "Assert.hpp"

	#include <stdio.h>
	#include <stdlib.h>

	//using namespace NumberDuck;

	struct MemoryRegion;

	struct MemoryAllocation
	{
		unsigned long nAllocationId;

		MemoryAllocation* pNext;
		MemoryAllocation* pPrevious;
		MemoryRegion* pMemoryRegion;
	};

	struct MemoryRegion
	{
		MemoryAllocation* pLastMemoryAllocation;
		MemoryRegion* pPrevious;
	};

	unsigned long g_nLastAllocationId = 0;
	MemoryRegion* g_pLastMemoryRegion = NULL;

	void* operator new(size_t n)
	{
		MemoryAllocation* pMemoryAllocation = (MemoryAllocation*)malloc(sizeof(MemoryAllocation) + n);
		void* p = (void*)(pMemoryAllocation + 1);

		++g_nLastAllocationId;

		if (g_nLastAllocationId == 389332)
		{
			//nbAssert::Assert(false);
		}

		pMemoryAllocation->nAllocationId = g_nLastAllocationId;
		pMemoryAllocation->pPrevious = NULL;
		pMemoryAllocation->pNext = NULL;
		pMemoryAllocation->pMemoryRegion = g_pLastMemoryRegion;
		if (g_pLastMemoryRegion)
		{
			pMemoryAllocation->pPrevious = g_pLastMemoryRegion->pLastMemoryAllocation;
			if (pMemoryAllocation->pPrevious)
				pMemoryAllocation->pPrevious->pNext = pMemoryAllocation;
			g_pLastMemoryRegion->pLastMemoryAllocation = pMemoryAllocation;
		}
		return p;
	}

	void operator delete(void* p) throw()
	{
		if (!p)
			return;

		MemoryAllocation* pMemoryAllocation = ((MemoryAllocation*)p) - 1;

		if (pMemoryAllocation->pMemoryRegion)
		{
			if (pMemoryAllocation->pMemoryRegion->pLastMemoryAllocation == pMemoryAllocation)
			{
				pMemoryAllocation->pMemoryRegion->pLastMemoryAllocation = pMemoryAllocation->pPrevious;
			}

			if (pMemoryAllocation->pPrevious)
				pMemoryAllocation->pPrevious->pNext = pMemoryAllocation->pNext;

			if (pMemoryAllocation->pNext)
				pMemoryAllocation->pNext->pPrevious = pMemoryAllocation->pPrevious;
		}

		free(pMemoryAllocation);
	}

	void MEMORY_REGION_PUSH()
	{
		MemoryRegion* pMemoryRegion = new MemoryRegion();
		pMemoryRegion->pLastMemoryAllocation = NULL;
		pMemoryRegion->pPrevious = g_pLastMemoryRegion;
		g_pLastMemoryRegion = pMemoryRegion;
	}

	void MEMORY_REGION_POP()
	{
		CLIFFY_ASSERT(g_pLastMemoryRegion);

		MemoryRegion* pMemoryRegion = g_pLastMemoryRegion;
		MemoryAllocation* pMemoryAllocation = pMemoryRegion->pLastMemoryAllocation;

		if (pMemoryAllocation)
		{
			printf("****** Leaks Detected!! ******\n");
			int nCount = 0;
			while (pMemoryAllocation)
			{
				if (!pMemoryAllocation->pPrevious)
					printf("\t%lu\n", pMemoryAllocation->nAllocationId);
				pMemoryAllocation = pMemoryAllocation->pPrevious;
				nCount++;
			}
			printf("%d leaks\n", nCount);
			CLIFFY_ASSERT(false);
		}

		g_pLastMemoryRegion = pMemoryRegion->pPrevious;
		delete pMemoryRegion;
	}

#endif
