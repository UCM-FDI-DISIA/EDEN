#ifndef EDEN_EXPORT_H_
#define EDEN_EXPORT_H_

#include "defs.h"

#include <windows.h>

typedef void (*SceneFunc)();

namespace eden {
	class Master;
	class SceneManager;

	Master* master;
	SceneManager* scnManager;
}

namespace eden_error {
	class ErrorHandler;
	ErrorHandler* errorHandler;
}

namespace eden_export {
	EDEN_API void RunEDEN();
	EDEN_API void StopEDEN();
	SceneFunc GetLoadScene();
}

HMODULE game;
eden::Master* master;
eden::SceneManager* scnManager;
eden_error::ErrorHandler* errorHandler;
SceneFunc LoadScene;

#endif /*EDEN_EXPORT_H_*/