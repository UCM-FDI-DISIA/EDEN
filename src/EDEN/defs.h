#ifndef EDEN_API
#define EDEN_API
// #ifdef EDEN_EXPORTS
#define EDEN_API __declspec(dllexport)
//#else
//#define EDEN_API __declspec(dllimport)
//#endif

#ifdef _DEBUG
#include <iostream>
#endif;
#endif // EDEN_API
