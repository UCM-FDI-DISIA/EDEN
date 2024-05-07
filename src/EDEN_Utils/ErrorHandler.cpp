#define _CRTDBG_MAP_ALLOC
#include "ErrorHandler.h"
#include "EdenMaster.h"

#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include "MacOSMessageBoxHelper.h"
#endif

namespace eden_error {
	void ErrorHandler::CloseApplication() {
		if (eden::Master::isInitialized())
		{
			eden::Master::Instance()->Close();
		}
	}

	void ErrorHandler::HandleExceptionNWin(std::runtime_error e) {
		std::string errorTitle, errorDescription;

		std::string what = e.what();

		bool charFound = false;

		for (int i = 0; i < what.size(); ++i) {
			if (!charFound && what[i] == TITLE_ERROR_SEPARATOR) {
				charFound = true;
			}
			else {
				if (charFound) {
					errorDescription.push_back(what[i]);
				}
				else {
					errorTitle.push_back(what[i]);
				}
			}
		}

		if (!charFound) {
			errorDescription = errorTitle;
		}

#ifdef __APPLE__
		ShowErrorMessageBox(errorTitle, errorDescription);
#endif

		CloseApplication();
	}

	void ErrorHandler::HandleException(std::exception e) {
		CloseApplication();

		std::string errorTitle, errorDescription;

		std::string what = e.what();

		bool charFound = false;

		for (int i = 0; i < what.size(); ++i) {	
			if (!charFound && what[i] == TITLE_ERROR_SEPARATOR) {
				charFound = true;
			}
			else {
				if (charFound) {
					errorDescription.push_back(what[i]);
				}
				else {
					errorTitle.push_back(what[i]);
				}
			}
		}

		if (!charFound) {
			errorDescription = errorTitle;
		}

#ifdef _WIN32
		MessageBoxA(nullptr, (LPCSTR)errorDescription.c_str(), (LPCSTR)errorTitle.c_str(), MB_ICONERROR);
#endif

	}

	void ErrorHandler::Warning(std::string warningMsg) {
		std::string msg("WARNING in line " + __LINE__);
		msg += +", in file: ";
		msg += __FILENAME__ + ':' + ' ' + warningMsg + '\n';
		AddToLog(msg);
	}

	void ErrorHandler::Assert(bool condition, std::string errorMessage) {
		if (!condition) {
			std::string message = __FILENAME__;
			message += " in line " + __LINE__;
			message += ": " + errorMessage + '\n';
			AddToLog(message);
			CloseApplication();
		}
	}

	void ErrorHandler::Exception(std::string title, std::string definition) {
		AddToLog(title + ": " + definition + '\n');
		std::string msg = title + TITLE_ERROR_SEPARATOR + definition;
		EDEN_EXCEPTION(msg.c_str());
	}

	void ErrorHandler::AddToLog(std::string message) {
#ifdef _DEBUG
		std::cerr << message;
		std::cerr << ERROR_SEPARETOR;
#endif // _DEBUG

		std::ofstream errorLog;

		// choosing opening mode
		int mode = std::ios_base::app;
		if (_generateLog) {
			mode = std::ios_base::trunc;
			_generateLog = false;
		}

		errorLog.open(LOG_NAME, mode);
		
		message += ERROR_SEPARETOR;

		errorLog.write(message.c_str(), message.size());

		errorLog.close();
	}
}