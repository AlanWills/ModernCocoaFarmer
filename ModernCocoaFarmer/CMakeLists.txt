cmake_minimum_required(VERSION 3.6)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#limit cmake to only make these configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

#set platforms we will generate the project on
set(CMAKE_GENERATOR_PLATFORM "x64")

project(ModernCocoaFarmer)

# Configure variables for MCF that will be used by other projects
set(MCF_BUILDS_DIR ${PROJECT_SOURCE_DIR}/Builds/${CMAKE_GENERATOR_PLATFORM}/${CMAKE_BUILD_TYPE})

#make sure call to project(ModernCocoaFarmer) before this otherwise ${PROJECT_SOURCE_DIR} won't be expanded properly
set(CELESTE_DIR ${PROJECT_SOURCE_DIR}/../Celeste)

##------------------------------ Testing ------------------------------##

INCLUDE_EXTERNAL_MSPROJECT(TestUtils ${CELESTE_DIR}/TestUtils/TestUtils.vcxproj)
set_target_properties(TestUtils PROPERTIES FOLDER Testing)

#CMake doesn't seem to support this projects type, but that's ok cos we don't really use it anyway
#INCLUDE_EXTERNAL_MSPROJECT(CelTestSharp ${CELESTE_DIR}/CelTestSharp/CelTestSharp.csproj)
#set_target_properties(CelTestSharp PROPERTIES FOLDER Testing)

##------------------------------ Celeste ------------------------------##

#add include directory for Celeste
INCLUDE_DIRECTORIES(${CELESTE_DIR}/Celeste/Headers)

#add library directories for Celeste
LINK_DIRECTORIES(${CELESTE_DIR}/Celeste/bin/${CMAKE_GENERATOR_PLATFORM}/${CMAKE_BUILD_TYPE})

#add link libraries for Celeste
LINK_LIBRARIES(Celeste.lib)

#include Celeste Engine projects
INCLUDE_EXTERNAL_MSPROJECT(Celeste ${CELESTE_DIR}/Celeste/Celeste.vcxproj)
set_target_properties(Celeste PROPERTIES FOLDER Celeste)

INCLUDE_EXTERNAL_MSPROJECT(CelesteTestUtils ${CELESTE_DIR}/CelesteTestUtils/CelesteTestUtils.vcxproj)
set_target_properties(CelesteTestUtils PROPERTIES FOLDER Celeste)
add_dependencies(CelesteTestUtils 
	Celeste 
	TestUtils)

INCLUDE_EXTERNAL_MSPROJECT(TestCeleste ${CELESTE_DIR}/TestCeleste/TestCeleste.vcxproj)
set_target_properties(TestCeleste PROPERTIES FOLDER Celeste)
add_dependencies(CelesteTestUtils 
	Celeste 
	CelesteTestUtils 
	TestUtils)

INCLUDE_EXTERNAL_MSPROJECT(TestCelesteRuntime ${CELESTE_DIR}/TestCelesteRuntime/TestCelesteRuntime.vcxproj)
set_target_properties(TestCelesteRuntime PROPERTIES FOLDER Celeste)
add_dependencies(TestCelesteRuntime 
	Celeste 
	CelesteTestUtils 
	TestUtils)

##------------------------------ Dev Tools ------------------------------##

INCLUDE_EXTERNAL_MSPROJECT(GuidGenerator ${CELESTE_DIR}/GuidGenerator/GuidGenerator.vcxproj)
set_target_properties(GuidGenerator PROPERTIES FOLDER DevTools)

##------------------------------ Bindings ------------------------------##

INCLUDE_EXTERNAL_MSPROJECT(BindingsGenerator ${CELESTE_DIR}/BindingsGenerator/BindingsGenerator.vcxproj)
set_target_properties(BindingsGenerator PROPERTIES FOLDER Bindings)

INCLUDE_EXTERNAL_MSPROJECT(CelesteBindingsGenerator ${CELESTE_DIR}/CelesteBindingsGenerator/CelesteBindingsGenerator.vcxproj)
set_target_properties(CelesteBindingsGenerator PROPERTIES FOLDER Bindings)
add_dependencies(CelesteBindingsGenerator 
	BindingsGenerator)
	
INCLUDE_EXTERNAL_MSPROJECT(BindingsKernel ${CELESTE_DIR}/BindingsKernel/BindingsKernel.csproj)
set_target_properties(BindingsKernel PROPERTIES FOLDER Bindings)

INCLUDE_EXTERNAL_MSPROJECT(CelesteBindingsLib ${CELESTE_DIR}/CelesteBindingsLib/CelesteBindingsLib.csproj)
set_target_properties(CelesteBindingsLib PROPERTIES FOLDER Bindings)

INCLUDE_EXTERNAL_MSPROJECT(CelesteBindings ${CELESTE_DIR}/CelesteBindings/CelesteBindings.csproj)
set_target_properties(CelesteBindings PROPERTIES FOLDER Bindings)
add_dependencies(CelesteBindings 
	BindingsKernel
	CelesteBindingsLib)
	
##------------------------------ Editor ------------------------------##

INCLUDE_EXTERNAL_MSPROJECT(CelesteEditorLibrary ${CELESTE_DIR}/CelesteEditorLibrary/CelesteEditorLibrary.csproj)
set_target_properties(CelesteEditorLibrary PROPERTIES FOLDER Editor)
add_dependencies(CelesteEditorLibrary
	BindingsKernel
	CelesteBindingsLib
	CelesteBindings)

INCLUDE_EXTERNAL_MSPROJECT(CelesteEditor ${CELESTE_DIR}/CelesteEditor/CelesteEditor.csproj)
set_target_properties(CelesteEditor PROPERTIES FOLDER Editor)
add_dependencies(CelesteEditor
	BindingsKernel
	CelesteBindingsLib
	CelesteBindings
	CelesteEditorLibrary)

##---------------------------- Third Party ----------------------------##

#add include directory for Third Party
INCLUDE_DIRECTORIES(
	${CELESTE_DIR}/3rdParty/Include
	${CELESTE_DIR}/3rdParty/Include/Assimp
	${CELESTE_DIR}/3rdParty/Include/freetype2
	${CELESTE_DIR}/3rdParty/Include/ffmpeg)

#add library directories for Third Party
LINK_DIRECTORIES(${CELESTE_DIR}/3rdParty/Lib/${CMAKE_GENERATOR_PLATFORM}/${CMAKE_BUILD_TYPE})

#add link libraries for Third Party
LINK_LIBRARIES(
	swscale.lib
	avutil.lib
	avcodec.lib
	avformat.lib
	assimp-vc140-mt.lib
	liblua53.lib
	tinyxml2.lib
	alut.lib
	OpenAL32.lib
	SOIL.lib
	glew32.lib
	opengl32.lib
	glfw3dll.lib
	freetype.lib)

MACRO(SOURCE_GROUP_BY_FOLDER root target)
  SET(SOURCE_GROUP_DELIMITER "/")
  SET(last_dir "")
  SET(files "")
  
  FOREACH(file ${target})
    file(RELATIVE_PATH relative_file ${root} "${file}")
    message(${relative_file})
    GET_FILENAME_COMPONENT(dir "${relative_file}" PATH)
    message(${dir})
    IF (NOT "${dir}" STREQUAL "${last_dir}")
      IF (files)
        message(${files})
        SOURCE_GROUP("${last_dir}" FILES ${files})
      ENDIF (files)
      SET(files "")
    ENDIF (NOT "${dir}" STREQUAL "${last_dir}")
    SET(files ${files} ${file})
    message(${files})
    SET(last_dir "${dir}")
  ENDFOREACH(file)

  IF (files)
    SOURCE_GROUP("${last_dir}" FILES ${files})
  ENDIF (files)
ENDMACRO(SOURCE_GROUP_BY_FOLDER)

##------------------------------ Modern Cocoa Farmer Library Project ------------------------------##
set(MCF_LIBRARY_PROJECT_NAME ModernCocoaFarmerLibrary)
set(MCF_LIBRARY_PROJECT_DIR ${PROJECT_SOURCE_DIR}/../${MCF_LIBRARY_PROJECT_NAME})

#set the default path for built executables to the "bin" directory
set(RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})

#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${MCF_BUILDS_DIR})

#add include directory for this project
INCLUDE_DIRECTORIES(${MCF_LIBRARY_PROJECT_DIR}/Include)

file(GLOB_RECURSE SOURCES ${MCF_LIBRARY_PROJECT_DIR}/Source/*.cpp)

SOURCE_GROUP_BY_FOLDER(${MCF_LIBRARY_PROJECT_DIR} ${SOURCES})

add_library(${MCF_LIBRARY_PROJECT_NAME} ${SOURCES})
add_dependencies(${MCF_LIBRARY_PROJECT_NAME} Celeste)
#add_custom_command(
#	TARGET ${PROJECT_NAME}
#	PRE_BUILD
#	COMMAND call "$(ProjectDir)Build Events/CopyDependencyFiles.bat" "$(TargetDir)" $(Configuration) $(Platform)
#	VERBATIM)

set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})

##------------------------------ Modern Cocoa Farmer Project ------------------------------##

#set the default path for built executables to the "bin" directory
set(RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})

#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${MCF_BUILDS_DIR})

#add include directory for this project
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Include)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/Source/*.cpp)

SOURCE_GROUP_BY_FOLDER(${PROJECT_SOURCE_DIR} ${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} Celeste ${MCF_LIBRARY_PROJECT_NAME})
#add_custom_command(
#	TARGET ${PROJECT_NAME}
#	PRE_BUILD
#	COMMAND call "$(ProjectDir)Build Events/CopyDependencyFiles.bat" "$(TargetDir)" $(Configuration) $(Platform)
#	VERBATIM)

set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ModernCocoaFarmer)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})