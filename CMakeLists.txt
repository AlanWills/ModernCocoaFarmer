cmake_minimum_required(VERSION 3.6)

##---------------------------- Globals ----------------------------##
project(ModernCocoaFarmer)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

IF(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
ENDIF()

IF(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    SET(BUILD_TESTS FALSE)
ELSE()
    SET(BUILD_TESTS TRUE)
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


##------------------------------ Modern Cocoa Farmer ------------------------------##
add_subdirectory(${MCF_DIR} ${MCF_DIR}/Build ${EXCLUDE})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY 
    VS_STARTUP_PROJECT ModernCocoaFarmer)

set_target_properties(ModernCocoaFarmer PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
##------------------------------ end Modern Cocoa Farmer ------------------------------##