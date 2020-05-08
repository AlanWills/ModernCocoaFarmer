#pragma once

#include "Platform/Platform.h"

#ifdef BUILDING_MODERNCOCOAFARMERLIBRARY_DLL
#define MCFLibraryDllExport __declspec(dllexport)
#else
#define MCFLibraryDllExport __declspec(dllimport)
#endif