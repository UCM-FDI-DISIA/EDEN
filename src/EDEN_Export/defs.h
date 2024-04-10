#pragma once
#ifndef EDEN_DEFS
#define EDEN_DEFS
#ifdef EDEN_EXPORTS
#pragma message("EXPORT")
#define EDEN_API __declspec(dllexport)
#else
#pragma message("IMPORT")
#define EDEN_API __declspec(dllimport)
#endif
#endif // EDEN_DEFS
