#include "Export.h"
#include <iostream>

int main(int argc, char* argv[]) {
	// Memory Leaks Check
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	eden_export::RunEDEN();
	eden_export::StopEDEN();
}