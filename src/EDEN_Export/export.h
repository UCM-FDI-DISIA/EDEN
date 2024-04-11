#ifndef EDEN_EXPORT_H_
#define EDEN_EXPORT_H_

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
	__declspec(dllexport) void RunEDEN();
	__declspec(dllexport) void StopEDEN();
}

eden::Master* master = nullptr;
eden::SceneManager* scnManager = nullptr;
eden_error::ErrorHandler* errorHandler = nullptr;

#endif /*EDEN_EXPORT_H_*/