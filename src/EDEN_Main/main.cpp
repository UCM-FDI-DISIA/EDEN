#include <iostream>
#include <windows.h>

#include "Export.h"

#ifdef _DEBUG
int main(int argc, char* argv[]) {
#else 
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCadShow) {
#endif
	// Memory Leaks Check
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	eden_export::RunEDEN();
	eden_export::StopEDEN();
}