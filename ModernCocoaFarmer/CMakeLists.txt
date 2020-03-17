cmake_minimum_required(VERSION 3.6)

##---------------------------- Globals ----------------------------##
project(ModernCocoaFarmer)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CELESTE_DIR ${PROJECT_SOURCE_DIR}/../Celeste)
set(MCF_BUILDS_DIR ${PROJECT_SOURCE_DIR}/Builds/${CMAKE_VS_PLATFORM_NAME}/${CMAKE_BUILD_TYPE})
set(THIRD_PARTY_DIR ${CELESTE_DIR}/3rdParty)


##---------------------------- glm ----------------------------##
set(GLM_PROJECT_DIR "${THIRD_PARTY_DIR}/glm")

execute_process(COMMAND git submodule update --init ${GLM_PROJECT_DIR}
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})


##---------------------------- Third Party ----------------------------##
set(THIRD_PARTY_INCLUDES
    ${GLM_PROJECT_DIR}
    ${THIRD_PARTY_DIR}/Include
	${THIRD_PARTY_DIR}/Include/Assimp
	${THIRD_PARTY_DIR}/Include/freetype2
	${THIRD_PARTY_DIR}/Include/ffmpeg)

set(THIRD_PARTY_LIBS
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


##------------------------------ Celeste ------------------------------##
set(CELESTE_PROJECT_NAME Celeste)
set(CELESTE_PROJECT_DIR ${PROJECT_SOURCE_DIR}/../Celeste/${CELESTE_PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES ${CELESTE_PROJECT_DIR}/Source/*.c ${CELESTE_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CELESTE_PROJECT_DIR}/Include/*.h ${CELESTE_PROJECT_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${CELESTE_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${CELESTE_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${CELESTE_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CELESTE_PROJECT_DIR} FILES ${RES_FILES})

add_library(${CELESTE_PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${CELESTE_PROJECT_NAME} PROPERTIES FOLDER ${CELESTE_PROJECT_NAME})
set_target_properties(${CELESTE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
set_target_properties(${CELESTE_PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_PATH ${MCF_BUILDS_DIR})
set_target_properties(${CELESTE_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${CELESTE_PROJECT_NAME} PUBLIC ${THIRD_PARTY_INCLUDES})
target_include_directories(${CELESTE_PROJECT_NAME} PUBLIC ${CELESTE_PROJECT_DIR}/Include)

target_link_libraries(${CELESTE_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIBS})

target_compile_options(${CELESTE_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)
add_definitions(-DBUILDING_CELESTE_ENGINE_DLL -DGLM_FORCE_SILENT_WARNINGS)


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
set(MCF_LIBRARY_PROJECT_NAME ModernCocoaFarmerLibrary)
set(MCF_LIBRARY_PROJECT_DIR ${PROJECT_SOURCE_DIR}/../${MCF_LIBRARY_PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES ${MCF_LIBRARY_PROJECT_DIR}/Source/*.c ${MCF_LIBRARY_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${MCF_LIBRARY_PROJECT_DIR}/Include/*.h ${MCF_LIBRARY_PROJECT_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${MCF_LIBRARY_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${MCF_LIBRARY_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${MCF_LIBRARY_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${MCF_LIBRARY_PROJECT_DIR} FILES ${RES_FILES})

add_library(${MCF_LIBRARY_PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_PATH ${MCF_BUILDS_DIR})
set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${MCF_LIBRARY_PROJECT_NAME} PUBLIC ${THIRD_PARTY_INCLUDES})
target_include_directories(${MCF_LIBRARY_PROJECT_NAME} PUBLIC ${CELESTE_PROJECT_DIR}/Include)
target_include_directories(${MCF_LIBRARY_PROJECT_NAME} PUBLIC ${MCF_LIBRARY_PROJECT_DIR}/Include)

target_link_libraries(${MCF_LIBRARY_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIBS})

target_compile_options(${CELESTE_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)

add_dependencies(${MCF_LIBRARY_PROJECT_NAME} ${CELESTE_PROJECT_NAME})


##------------------------------ Modern Cocoa Farmer Project ------------------------------##
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/Source/*.c ${PROJECT_SOURCE_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/Include/*.h ${PROJECT_SOURCE_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${PROJECT_SOURCE_DIR}/Resources/*.*)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${RES_FILES})

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_PATH ${MCF_BUILDS_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC ${THIRD_PARTY_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CELESTE_PROJECT_DIR}/Include)
target_include_directories(${PROJECT_NAME} PUBLIC ${MCF_LIBRARY_PROJECT_DIR}/Include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIBS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${MCF_LIBRARY_PROJECT_NAME})

target_compile_options(${CELESTE_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)

add_dependencies(${PROJECT_NAME} ${MCF_LIBRARY_PROJECT_NAME} ${CELESTE_PROJECT_NAME})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})

#add_custom_command(
#	TARGET ${PROJECT_NAME}
#	PRE_BUILD
#	COMMAND call "$(ProjectDir)Build Events/CopyDependencyFiles.bat" "$(TargetDir)" $(Configuration) $(Platform)
#	VERBATIM)