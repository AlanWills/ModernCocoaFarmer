cmake_minimum_required(VERSION 3.6)

include(${CMAKE_CURRENT_SOURCE_DIR}/Celeste/BuildTools/CMakeLists.txt)

##---------------------------- Globals ----------------------------##
project(ModernCocoaFarmer)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
IF(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
ENDIF()

IF(NOT DEFINED USE_PREBUILT_LIBS)
    SET(USE_PREBUILT_LIBS OFF CACHE BOOL "" FORCE)
ENDIF()

IF(USE_PREBUILT_LIBS)
    SET(EXCLUDE EXCLUDE_FROM_ALL CACHE STRING "" FORCE)
ELSE()
    SET(EXCLUDE "" CACHE STRING "" FORCE)
ENDIF()

set(MCF_BUILDS_DIR ${PROJECT_SOURCE_DIR}/Build/${CMAKE_VS_PLATFORM_NAME})
set(MCF_DIR ${PROJECT_SOURCE_DIR}/${CMAKE_PROJECT_NAME})
set(CELESTE_DIR ${PROJECT_SOURCE_DIR}/Celeste)
set(THIRD_PARTY_FOLDER "3rd Party")
set(THIRD_PARTY_DIR ${CELESTE_DIR}/3rdParty)
set(THIRD_PARTY_LIB_DIR ${THIRD_PARTY_DIR}/lib/${CMAKE_VS_PLATFORM_NAME})
set(THIRD_PARTY_DLL_DIR ${THIRD_PARTY_DIR}/dll/${CMAKE_VS_PLATFORM_NAME})
##---------------------------- end Globals ----------------------------##


##---------------------------- assimp ----------------------------##
set(ASSIMP_PROJECT_DIR "${THIRD_PARTY_DIR}/assimp")
SET(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
SET(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(${ASSIMP_PROJECT_DIR} ${ASSIMP_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(assimp PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

set_target_properties(IrrXML PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})

set_target_properties(zlibstatic PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})

set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})
#---------------------------- end freealut ----------------------------##


##---------------------------- crossguid ----------------------------##
set(CROSSGUID_PROJECT_DIR "${THIRD_PARTY_DIR}/crossguid")
SET(CROSSGUID_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(${CROSSGUID_PROJECT_DIR} ${CROSSGUID_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(crossguid PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
##---------------------------- end curl ----------------------------##


##---------------------------- curl ----------------------------##
set(CURL_PROJECT_DIR "${THIRD_PARTY_DIR}/curl")
add_subdirectory(${CURL_PROJECT_DIR} ${CURL_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(libcurl PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
##---------------------------- end curl ----------------------------##


##---------------------------- curlpp ----------------------------##
set(CURLPP_PROJECT_DIR "${THIRD_PARTY_DIR}/curlpp")
set(CURL_INCLUDE_DIR ${CURL_PROJECT_DIR}/include)
set(CURL_LIBRARY ${THIRD_PARTY_LIB_DIR}/${CMAKE_BUILD_TYPE}/libcurl.lib)

add_subdirectory(${CURLPP_PROJECT_DIR} ${CURLPP_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(curlpp PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
##---------------------------- end curlpp ----------------------------##


##---------------------------- dirent ----------------------------##
set(DIRENT_PROJECT_DIR "${THIRD_PARTY_DIR}/dirent")
add_subdirectory(${DIRENT_PROJECT_DIR} ${DIRENT_PROJECT_DIR}/build EXCLUDE_FROM_ALL)
##---------------------------- end dirent ----------------------------##


##---------------------------- ffmpeg ----------------------------##
set(FFMPEG_PROJECT_DIR "${THIRD_PARTY_DIR}/ffmpeg")
set(AVCODEC_PROJECT_NAME avcodec)
set(AVFORMAT_PROJECT_NAME avformat)
set(AVUTIL_PROJECT_NAME avutil)
set(SWSCALE_PROJECT_NAME swscale)
##---------------------------- end ffmpeg ----------------------------##


##---------------------------- openal-soft ----------------------------##
set(OPENAL_SOFT_PROJECT_DIR "${THIRD_PARTY_DIR}/openal-soft")
set(OPENAL_INCLUDE_DIR ${OPENAL_SOFT_PROJECT_DIR}/include/AL)
set(OPENAL_LIBRARY ${THIRD_PARTY_LIB_DIR}/${CMAKE_BUILD_TYPE}/OpenAL32.lib)
set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${OPENAL_SOFT_PROJECT_DIR} ${OPENAL_SOFT_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(OpenAL PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

set_target_properties(build_version PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})

set_target_properties(common PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})

set_target_properties(native-tools PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})
#---------------------------- end openal-soft ----------------------------##


##---------------------------- freealut ----------------------------##
set(FREEALUT_PROJECT_DIR "${THIRD_PARTY_DIR}/freealut")
SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
SET(BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(${FREEALUT_PROJECT_DIR} ${FREEALUT_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(alut PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end freealut ----------------------------##


##---------------------------- freetype2 ----------------------------##
set(FREETYPE2_PROJECT_DIR "${THIRD_PARTY_DIR}/freetype2")
add_subdirectory(${FREETYPE2_PROJECT_DIR} ${FREETYPE2_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(freetype PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end freetype2 ----------------------------##


##---------------------------- glew ----------------------------##
set(GLEW_PROJECT_DIR "${THIRD_PARTY_DIR}/glew")
add_subdirectory(${GLEW_PROJECT_DIR} ${GLEW_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(glew PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

set_target_properties(glewinfo PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})
##---------------------------- end glew ----------------------------##


##---------------------------- glfw ----------------------------##
set(GLFW_PROJECT_DIR "${THIRD_PARTY_DIR}/glfw")
add_subdirectory(${GLFW_PROJECT_DIR} ${GLFW_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(glfw PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
##---------------------------- end glfw ----------------------------##


##---------------------------- glm ----------------------------##
set(GLM_PROJECT_DIR "${THIRD_PARTY_DIR}/glm")
set(BUILD_STATIC_LIBS true)
set(BUILD_SHARED_LIBS false)
add_subdirectory(${GLM_PROJECT_DIR} ${GLM_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(glm_static PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

##---------------------------- end glm ----------------------------##


##---------------------------- lua ----------------------------##
set(LUA_PROJECT_DIR "${THIRD_PARTY_DIR}/lua")
add_subdirectory(${LUA_PROJECT_DIR} ${LUA_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(liblua PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end lua ----------------------------##


##---------------------------- SOIL2 ----------------------------##
set(SOIL2_PROJECT_DIR "${THIRD_PARTY_DIR}/SOIL2")
add_subdirectory(${SOIL2_PROJECT_DIR} ${SOIL2_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(SOIL2 PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end lua ----------------------------##


##---------------------------- sol2 ----------------------------##
set(SOL2_PROJECT_DIR "${THIRD_PARTY_DIR}/sol2")
add_subdirectory(${SOL2_PROJECT_DIR} ${SOL2_PROJECT_DIR}/build ${EXCLUDE})
#---------------------------- end sol2 ----------------------------##


##---------------------------- tinyxml2 ----------------------------##
set(TINYXML2_PROJECT_DIR "${THIRD_PARTY_DIR}/tinyxml2")
add_subdirectory(${TINYXML2_PROJECT_DIR} ${TINYXML2_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(tinyxml2 PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end tinyxml2 ----------------------------##


##---------------------------- 3rd Party ----------------------------##
#set(THIRD_PARTY_INCLUDES
#     ${ASSIMP_PROJECT_DIR}/include
#     ${ASSIMP_PROJECT_DIR}/build/include     #for config.h
#     ${FFMPEG_PROJECT_DIR}
#     ${OPENAL_SOFT_PROJECT_DIR}/include
#     ${OPENAL_SOFT_PROJECT_DIR}/include/AL
#     )

#set(THIRD_PARTY_LIBS
#	${AVCODEC_PROJECT_NAME}.lib
#    ${AVFORMAT_PROJECT_NAME}.lib
#	${AVUTIL_PROJECT_NAME}.lib
#    ${SWSCALE_PROJECT_NAME}.lib)
##---------------------------- end 3rd Party ----------------------------##


##------------------------------ Testing ------------------------------##
#INCLUDE_EXTERNAL_MSPROJECT(TestUtils ${CELESTE_DIR}/TestUtils/TestUtils.vcxproj)
#set_target_properties(TestUtils PROPERTIES FOLDER Testing)

#CMake doesn't seem to support this projects type, but that's ok cos we don't really use it anyway
#INCLUDE_EXTERNAL_MSPROJECT(CelTestSharp ${CELESTE_DIR}/CelTestSharp/CelTestSharp.csproj)
#set_target_properties(CelTestSharp PROPERTIES FOLDER Testing)

#INCLUDE_EXTERNAL_MSPROJECT(CelesteTestUtils ${CELESTE_DIR}/CelesteTestUtils/CelesteTestUtils.vcxproj)
#set_target_properties(CelesteTestUtils PROPERTIES FOLDER Celeste)
#add_dependencies(CelesteTestUtils 
#	Celeste 
#	TestUtils)

#INCLUDE_EXTERNAL_MSPROJECT(TestCeleste ${CELESTE_DIR}/TestCeleste/TestCeleste.vcxproj)
#set_target_properties(TestCeleste PROPERTIES FOLDER Celeste)
#add_dependencies(CelesteTestUtils 
#	Celeste 
#	CelesteTestUtils 
#	TestUtils)

#INCLUDE_EXTERNAL_MSPROJECT(TestCelesteRuntime ${CELESTE_DIR}/TestCelesteRuntime/TestCelesteRuntime.vcxproj)
#set_target_properties(TestCelesteRuntime PROPERTIES FOLDER Celeste)
#add_dependencies(TestCelesteRuntime 
#	Celeste 
#	CelesteTestUtils 
#	TestUtils)


##------------------------------ Platform ------------------------------##
set(PLATFORM_DIR ${CELESTE_DIR}/Platform)
add_subdirectory(${PLATFORM_DIR} ${PLATFORM_DIR}/Build)
##------------------------------ end Platform ------------------------------##


##------------------------------ CelesteStl ------------------------------##
set(CELESTE_STL_DIR ${CELESTE_DIR}/CelesteStl)
add_subdirectory(${CELESTE_STL_DIR} ${CELESTE_STL_DIR}/Build)
##------------------------------ end Assert ------------------------------##


##------------------------------ Assert ------------------------------##
set(ASSERT_DIR ${CELESTE_DIR}/Assert)
add_subdirectory(${ASSERT_DIR} ${ASSERT_DIR}/Build)

set_target_properties(Assert PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
##------------------------------ end Assert ------------------------------##


##------------------------------ Log ------------------------------##
set(LOG_DIR ${CELESTE_DIR}/Log)
add_subdirectory(${LOG_DIR} ${LOG_DIR}/Build)

set_target_properties(Log PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
##------------------------------ end Assert ------------------------------##


##---------------------------- FileSystem ----------------------------##
set(FILE_SYSTEM_PROJECT_DIR "${CELESTE_DIR}/FileSystem")
add_subdirectory(${FILE_SYSTEM_PROJECT_DIR} ${FILE_SYSTEM_PROJECT_DIR}/Build ${EXCLUDE})
#---------------------------- end FileSystem ----------------------------##


##---------------------------- Lua ----------------------------##
add_subdirectory("${CELESTE_DIR}/Lua" "${CELESTE_DIR}/Lua/Build" ${EXCLUDE})

set_target_properties(Lua PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
#---------------------------- end Lua ----------------------------##


##------------------------------ Dolce ------------------------------##
set(DOLCE_PROJECT_DIR "${CELESTE_DIR}/Dolce")
add_subdirectory(${DOLCE_PROJECT_DIR} ${DOLCE_PROJECT_DIR}/Build ${EXCLUDE})

set_target_properties(Dolce PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ DolceLua ------------------------------##
set(DOLCE_LUA_PROJECT_DIR "${CELESTE_DIR}/DolceLua")
add_subdirectory(${DOLCE_LUA_PROJECT_DIR} ${DOLCE_LUA_PROJECT_DIR}/Build ${EXCLUDE})

set_target_properties(DolceLua PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ Celeste ------------------------------##
set(CELESTE_PROJECT_DIR ${CELESTE_DIR}/Celeste)
add_subdirectory(${CELESTE_PROJECT_DIR} ${CELESTE_PROJECT_DIR}/Build ${EXCLUDE})

set_target_properties(Celeste PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ CelesteLua ------------------------------##
set(CELESTE_LUA_PROJECT_DIR "${CELESTE_DIR}/CelesteLua")
add_subdirectory(${CELESTE_LUA_PROJECT_DIR} ${CELESTE_LUA_PROJECT_DIR}/Build ${EXCLUDE})

set_target_properties(CelesteLua PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ Celeste Test Globals ------------------------------##
set(CELESTE_TESTS_SOLUTION_FOLDER Celeste/Tests)


##------------------------------ Celeste Mocks Project ------------------------------##
set(CELESTE_LUA_PROJECT_DIR "${CELESTE_DIR}/CelesteMocks")
add_subdirectory(${CELESTE_LUA_PROJECT_DIR} ${CELESTE_LUA_PROJECT_DIR}/Build)

set_target_properties(CelesteMocks PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ Celeste Test Resources Project ------------------------------##
set(CELESTE_TEST_RESOURCES_PROJECT_DIR "${CELESTE_DIR}/CelesteTestResources")
add_subdirectory(${CELESTE_TEST_RESOURCES_PROJECT_DIR} ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Build)

set_target_properties(CelesteTestResources PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ Test Utils Project ------------------------------##
set(TEST_UTILS_PROJECT_DIR "${CELESTE_DIR}/TestUtils")
add_subdirectory(${TEST_UTILS_PROJECT_DIR} ${TEST_UTILS_PROJECT_DIR}/Build)

set_target_properties(TestUtils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ Celeste Test Utils Project ------------------------------##
set(CELESTE_TEST_UTILS_PROJECT_DIR "${CELESTE_DIR}/CelesteTestUtils")
add_subdirectory(${CELESTE_TEST_UTILS_PROJECT_DIR} ${CELESTE_TEST_UTILS_PROJECT_DIR}/Build)

set_target_properties(CelesteTestUtils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ Test Celeste Project ------------------------------##
set(TEST_CELESTE_PROJECT_DIR ${CELESTE_PROJECT_DIR}/Tests)
add_subdirectory(${TEST_CELESTE_PROJECT_DIR} ${TEST_CELESTE_PROJECT_DIR}/Build)

set_target_properties(TestCeleste PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ Dev Tools ------------------------------##
#INCLUDE_EXTERNAL_MSPROJECT(GuidGenerator ${CELESTE_DIR}/GuidGenerator/GuidGenerator.vcxproj)
#set_target_properties(GuidGenerator PROPERTIES FOLDER DevTools)


##------------------------------ Bindings ------------------------------##
#INCLUDE_EXTERNAL_MSPROJECT(BindingsGenerator ${CELESTE_DIR}/BindingsGenerator/BindingsGenerator.vcxproj)
#set_target_properties(BindingsGenerator PROPERTIES FOLDER Bindings)

#INCLUDE_EXTERNAL_MSPROJECT(CelesteBindingsGenerator ${CELESTE_DIR}/CelesteBindingsGenerator/CelesteBindingsGenerator.vcxproj)
#set_target_properties(CelesteBindingsGenerator PROPERTIES FOLDER Bindings)
#add_dependencies(CelesteBindingsGenerator 
#	BindingsGenerator)
	
#INCLUDE_EXTERNAL_MSPROJECT(BindingsKernel ${CELESTE_DIR}/BindingsKernel/BindingsKernel.csproj)
#set_target_properties(BindingsKernel PROPERTIES FOLDER Bindings)

#INCLUDE_EXTERNAL_MSPROJECT(CelesteBindingsLib ${CELESTE_DIR}/CelesteBindingsLib/CelesteBindingsLib.csproj)
#set_target_properties(CelesteBindingsLib PROPERTIES FOLDER Bindings)

#INCLUDE_EXTERNAL_MSPROJECT(CelesteBindings ${CELESTE_DIR}/CelesteBindings/CelesteBindings.csproj)
#set_target_properties(CelesteBindings PROPERTIES FOLDER Bindings)
#add_dependencies(CelesteBindings 
#	BindingsKernel
#	CelesteBindingsLib)
	

##------------------------------ Editor ------------------------------##
#INCLUDE_EXTERNAL_MSPROJECT(CelesteEditorLibrary ${CELESTE_DIR}/CelesteEditorLibrary/CelesteEditorLibrary.csproj)
#set_target_properties(CelesteEditorLibrary PROPERTIES FOLDER Editor)
#add_dependencies(CelesteEditorLibrary
#	BindingsKernel
#	CelesteBindingsLib
#	CelesteBindings)

#INCLUDE_EXTERNAL_MSPROJECT(CelesteEditor ${CELESTE_DIR}/CelesteEditor/CelesteEditor.csproj)
#set_target_properties(CelesteEditor PROPERTIES FOLDER Editor)
#add_dependencies(CelesteEditor
#	BindingsKernel
#	CelesteBindingsLib
#	CelesteBindings
#	CelesteEditorLibrary)


##------------------------------ Modern Cocoa Farmer Library Project ------------------------------##
add_subdirectory(${MCF_DIR} ${MCF_DIR}/Build)

set_target_properties(ModernCocoaFarmerLibrary PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ ModernCocoaFarmerLua ------------------------------##
set(MCF_LUA_PROJECT_DIR "${PROJECT_SOURCE_DIR}/ModernCocoaFarmerLua")
add_subdirectory(${MCF_LUA_PROJECT_DIR} ${MCF_LUA_PROJECT_DIR}/Build ${EXCLUDE})

set_target_properties(ModernCocoaFarmerLua PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})


##------------------------------ Modern Cocoa Farmer Project ------------------------------##
set(MCF_PROJECT_NAME ModernCocoaFarmer)

file(GLOB_RECURSE RES_FILES ${MCF_DIR}/Resources/*.*)
file(GLOB_RECURSE CELESTE_RES_FILES ${CELESTE_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${MCF_DIR} FILES ${RES_FILES})
source_group(TREE ${CELESTE_PROJECT_DIR} FILES ${CELESTE_RES_FILES})

add_executable(${MCF_PROJECT_NAME} ${MCF_DIR}/Main.cpp ${MCF_DIR}/MCFGame.cpp ${MCF_DIR}/MCFGame.h ${RES_FILES} ${CELESTE_RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${MCF_PROJECT_NAME} PROPERTIES
    FOLDER "Modern Cocoa Farmer"
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR} 
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17
    VS_DEBUGGER_WORKING_DIRECTORY ${MCF_DIR})

target_include_directories(${MCF_PROJECT_NAME} PUBLIC 
    ${MCF_DIR}/Include)
target_link_libraries(${MCF_PROJECT_NAME} PUBLIC 
    Dolce
    DolceLua
    Celeste
    CelesteLua
    ModernCocoaFarmerLibrary
    ModernCocoaFarmerLua)

target_compile_options(${MCF_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)