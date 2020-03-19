#pragma once

#include "UtilityHeaders/PlatformHeaders.h"

#ifdef BUILDING_MCF_LIBRARY_DLL
#define MCFLibraryDllExport __declspec(dllexport)
#else
#define MCFLibraryDllExport __declspec(dllimport)
#endif