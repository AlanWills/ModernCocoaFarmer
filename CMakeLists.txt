cmake_minimum_required(VERSION 3.6)

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

set(BUILDS_DIR ${PROJECT_SOURCE_DIR}/Build/${CMAKE_VS_PLATFORM_NAME})
set(MCF_DIR ${PROJECT_SOURCE_DIR}/${CMAKE_PROJECT_NAME})
set(CELESTE_DIR ${PROJECT_SOURCE_DIR}/Celeste)
##---------------------------- end Globals ----------------------------##


##------------------------------ Celeste ------------------------------##
add_subdirectory(${CELESTE_DIR} ${CELESTE_DIR}/Build ${EXCLUDE})
##------------------------------ end Celeste ------------------------------##


##------------------------------ Modern Cocoa Farmer Library Project ------------------------------##
add_subdirectory(${MCF_DIR} ${MCF_DIR}/Build)

set_target_properties(ModernCocoaFarmerLibrary PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ ModernCocoaFarmerLua ------------------------------##
set(MCF_LUA_PROJECT_DIR "${PROJECT_SOURCE_DIR}/ModernCocoaFarmerLua")
add_subdirectory(${MCF_LUA_PROJECT_DIR} ${MCF_LUA_PROJECT_DIR}/Build ${EXCLUDE})

set_target_properties(ModernCocoaFarmerLua PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ Modern Cocoa Farmer Project ------------------------------##
set(MCF_PROJECT_NAME ModernCocoaFarmer)

file(GLOB_RECURSE RES_FILES ${MCF_DIR}/Resources/*.*)
file(GLOB_RECURSE CELESTE_RES_FILES ${CELESTE_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${MCF_DIR} FILES ${RES_FILES})
source_group(TREE ${CELESTE_DIR}/Celeste FILES ${CELESTE_RES_FILES})

add_executable(${MCF_PROJECT_NAME} ${MCF_DIR}/Main.cpp ${MCF_DIR}/MCFGame.cpp ${MCF_DIR}/MCFGame.h ${RES_FILES} ${CELESTE_RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${MCF_PROJECT_NAME} PROPERTIES
    FOLDER "Modern Cocoa Farmer"
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR} 
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR}
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