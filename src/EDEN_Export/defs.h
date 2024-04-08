#pragma once
#ifndef EDEN_DEFS
#define EDEN_DEFS
#ifdef EDEN_EXPORTS
#define EDEN_API __declspec(dllexport)
#else
#define EDEN_API __declspec(dllimport)
#endif

#endif // EDEN_DEFS
