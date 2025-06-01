#pragma once

#ifdef DEBUG
	void MEMORY_REGION_PUSH();
	void MEMORY_REGION_POP();
#else
	#define MEMORY_REGION_PUSH() do {} while(0)
	#define MEMORY_REGION_POP() do {} while(0)
#endif
