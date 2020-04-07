#pragma once

#include "Platform/Platform.h"

#ifdef BUILDING_MCF_LIBRARY_DLL
#define MCFLibraryDllExport __declspec(dllexport)
#else
#define MCFLibraryDllExport __declspec(dllimport)
#endif