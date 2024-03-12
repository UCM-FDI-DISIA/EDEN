#ifndef _ERROR_HANDLER_H
#define _ERROR_HANDLER_H

#include <exception>
#include <iostream>

namespace eden_error {
	#define ERROR_DEFINITION "ERROR in line "+ std::to_string(__LINE__) + ", in file: " + __FILENAME__
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

	#define EDEN_WARNING(msg) std::cerr << ERROR_DEFINITION << ':' << ' ' << msg << '\n';
	#define EDEN_ASSERT(message, condition) assert((message, condition))
	#define EDEN_EXCEPTION(error_description) throw std::exception(error_description);
}


#endif // _ERROR_HANDLER_H