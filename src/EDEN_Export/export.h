#ifndef EDEN_EXPORT_H_
#define EDEN_EXPORT_H_

#include "defs.h"

namespace eden {
	class Master;
}

namespace eden_error {
	class ErrorHandler;
}

namespace eden_export {
	EDEN_API void InitEDEN();
	EDEN_API void RunEDEN();
	EDEN_API void StopEDEN();
}

eden::Master* master = nullptr;
eden_error::ErrorHandler* errorHandler = nullptr;

void RegisterComponents();

#endif /*EDEN_EXPORT_H_*/