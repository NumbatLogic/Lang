#include "../../../Transpiled/CLI/CLI.hpp"
//#include "../../../Shared/CPP/Memory.hpp"
#include <cstdio>

using namespace NumbatLogic;

int main(int argc, const char* argv[])
{
	//MEMORY_REGION_PUSH();

	Vector<const char*>* sArgVector = new Vector<const char*>();
	for (int i = 1; i < argc; i++)
		sArgVector->PushBack(argv[i]);

	CLI::Run(sArgVector);

	delete sArgVector;

	//MEMORY_REGION_POP();
	return 0;
}