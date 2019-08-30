#pragma once

#ifdef BUILDING_MCF_LIBRARY_DLL
#define MCFLibraryDllExport __declspec(dllexport)
#else
#define MCFLibraryDllExport __declspec(dllimport)
#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers