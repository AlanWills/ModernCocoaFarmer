cmake_minimum_required(VERSION 3.6)

##---------------------------- Globals ----------------------------##
project(ModernCocoaFarmer)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
ENDIF()

set(CELESTE_DIR ${PROJECT_SOURCE_DIR}/Celeste)
set(MCF_BUILDS_DIR ${PROJECT_SOURCE_DIR}/Build/${CMAKE_VS_PLATFORM_NAME}/)
set(THIRD_PARTY_DIR ${CELESTE_DIR}/3rdParty)
set(THIRD_PARTY_FOLDER_NAME "3rd Party")
##---------------------------- end Globals ----------------------------##


##---------------------------- glm ----------------------------##
set(GLM_PROJECT_NAME glm)
set(GLM_PROJECT_DIR "${THIRD_PARTY_DIR}/glm")
#
#file(GLOB_RECURSE SOURCE_FILES ${GLM_PROJECT_DIR}/glm/*.c ${GLM_PROJECT_DIR}/glm/*.cpp)
#file(GLOB_RECURSE HEADER_FILES ${GLM_PROJECT_DIR}/glm/*.h ${GLM_PROJECT_DIR}/glm/*.hpp)
#
#source_group(TREE ${GLM_PROJECT_DIR} PREFIX Source/ FILES ${SOURCE_FILES})						   
#source_group(TREE ${GLM_PROJECT_DIR} PREFIX Include/ FILES ${HEADER_FILES})

#add_library(${GLM_PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
add_subdirectory(${GLM_PROJECT_DIR})

#set_target_properties(${GLM_PROJECT_NAME} PROPERTIES 
#    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
#    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
#    ARCHIVE_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
#    CXX_STANDARD 17
#    EXCLUDE_FROM_ALL true
#    EXCLUDE_FROM_DEFAULT_BUILD true
#    FOLDER ${THIRD_PARTY_FOLDER_NAME})
#
#target_include_directories(${GLM_PROJECT_NAME} PUBLIC ${GLM_PROJECT_DIR})
##---------------------------- end glm ----------------------------##


##---------------------------- ffmpeg ----------------------------##
set(FFMPEG_PROJECT_DIR "${THIRD_PARTY_DIR}/ffmpeg")

##---------------------------- end ffmpeg ----------------------------##


##---------------------------- avcodec ----------------------------##
set(AVCODEC_PROJECT_NAME avcodec)
set(AVCODEC_PROJECT_DIR "${FFMPEG_PROJECT_DIR}/lib${AVCODEC_PROJECT_NAME}")

file(GLOB_RECURSE SOURCE_FILES ${AVCODEC_PROJECT_DIR}/*.c ${AVCODEC_PROJECT_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${AVCODEC_PROJECT_DIR}/*.h ${AVCODEC_PROJECT_DIR}/*.hpp)

source_group(TREE ${AVCODEC_PROJECT_DIR} PREFIX Source/ FILES ${SOURCE_FILES})						   
source_group(TREE ${AVCODEC_PROJECT_DIR} PREFIX Include/ FILES ${HEADER_FILES})

add_library(${AVCODEC_PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${AVCODEC_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17
    EXCLUDE_FROM_ALL true
    EXCLUDE_FROM_DEFAULT_BUILD true
    FOLDER ${THIRD_PARTY_FOLDER_NAME})

target_include_directories(${AVCODEC_PROJECT_NAME} PUBLIC ${FFMPEG_PROJECT_DIR})
#---------------------------- end avcodec ----------------------------##


#---------------------------- avformat ----------------------------##
set(AVFORMAT_PROJECT_NAME avformat)
set(AVFORMAT_PROJECT_DIR "${FFMPEG_PROJECT_DIR}/lib${AVFORMAT_PROJECT_NAME}")

file(GLOB_RECURSE SOURCE_FILES ${AVFORMAT_PROJECT_DIR}/*.c ${AVFORMAT_PROJECT_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${AVFORMAT_PROJECT_DIR}/*.h ${AVFORMAT_PROJECT_DIR}/*.hpp)

source_group(TREE ${AVFORMAT_PROJECT_DIR} PREFIX Source/ FILES ${SOURCE_FILES})						   
source_group(TREE ${AVFORMAT_PROJECT_DIR} PREFIX Include/ FILES ${HEADER_FILES})

add_library(${AVFORMAT_PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${AVFORMAT_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17
    EXCLUDE_FROM_ALL true
    EXCLUDE_FROM_DEFAULT_BUILD true
    FOLDER ${THIRD_PARTY_FOLDER_NAME})

target_include_directories(${AVFORMAT_PROJECT_NAME} PUBLIC ${FFMPEG_PROJECT_DIR})
##---------------------------- end avformat ----------------------------##


#---------------------------- avutil ----------------------------##
set(AVUTIL_PROJECT_NAME avutil)
set(AVUTIL_PROJECT_DIR "${FFMPEG_PROJECT_DIR}/lib${AVUTIL_PROJECT_NAME}")

file(GLOB_RECURSE SOURCE_FILES ${AVUTIL_PROJECT_DIR}/*.c ${AVUTIL_PROJECT_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${AVUTIL_PROJECT_DIR}/*.h ${AVUTIL_PROJECT_DIR}/*.hpp)

source_group(TREE ${AVUTIL_PROJECT_DIR} PREFIX Source/ FILES ${SOURCE_FILES})						   
source_group(TREE ${AVUTIL_PROJECT_DIR} PREFIX Include/ FILES ${HEADER_FILES})

add_library(${AVUTIL_PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${AVUTIL_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17
    EXCLUDE_FROM_ALL true
    EXCLUDE_FROM_DEFAULT_BUILD true
    FOLDER ${THIRD_PARTY_FOLDER_NAME})

target_include_directories(${AVUTIL_PROJECT_NAME} PUBLIC ${FFMPEG_PROJECT_DIR})
##---------------------------- end avutil ----------------------------##


#---------------------------- swscale ----------------------------##
set(SWSCALE_PROJECT_NAME swscale)
set(SWSCALE_PROJECT_DIR "${FFMPEG_PROJECT_DIR}/lib${SWSCALE_PROJECT_NAME}")

file(GLOB_RECURSE SOURCE_FILES ${SWSCALE_PROJECT_DIR}/*.c ${SWSCALE_PROJECT_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${SWSCALE_PROJECT_DIR}/*.h ${SWSCALE_PROJECT_DIR}/*.hpp)

source_group(TREE ${SWSCALE_PROJECT_DIR} PREFIX Source/ FILES ${SOURCE_FILES})						   
source_group(TREE ${SWSCALE_PROJECT_DIR} PREFIX Include/ FILES ${HEADER_FILES})

add_library(${SWSCALE_PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${SWSCALE_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17
    EXCLUDE_FROM_ALL true
    EXCLUDE_FROM_DEFAULT_BUILD true
    FOLDER ${THIRD_PARTY_FOLDER_NAME})

target_include_directories(${SWSCALE_PROJECT_NAME} PUBLIC ${FFMPEG_PROJECT_DIR})
##---------------------------- end swscale ----------------------------##


##---------------------------- openal-soft ----------------------------##
set(OPENAL_SOFT_PROJECT_DIR "${THIRD_PARTY_DIR}/openal-soft")
set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(${OPENAL_SOFT_PROJECT_DIR})

set_target_properties(OpenAL PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    EXCLUDE_FROM_ALL true
    EXCLUDE_FROM_DEFAULT_BUILD true
    FOLDER ${THIRD_PARTY_FOLDER_NAME})

set_target_properties(build_version PROPERTIES
    #RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    #LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    #EXCLUDE_FROM_ALL true
    #EXCLUDE_FROM_DEFAULT_BUILD true
    FOLDER ${THIRD_PARTY_FOLDER_NAME})

set_target_properties(common PROPERTIES
    #RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    #LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    #EXCLUDE_FROM_ALL true
    #EXCLUDE_FROM_DEFAULT_BUILD true
    FOLDER ${THIRD_PARTY_FOLDER_NAME})

set_target_properties(ex-common PROPERTIES
    #RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    #LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    #EXCLUDE_FROM_ALL true
    #EXCLUDE_FROM_DEFAULT_BUILD true
    FOLDER ${THIRD_PARTY_FOLDER_NAME})

set_target_properties(native-tools PROPERTIES
    #RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    #LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    #EXCLUDE_FROM_ALL true
    #EXCLUDE_FROM_DEFAULT_BUILD true
    FOLDER ${THIRD_PARTY_FOLDER_NAME})
#---------------------------- end openal-soft ----------------------------##


##---------------------------- 3rd Party ----------------------------##
set(THIRD_PARTY_INCLUDES
    ${GLM_PROJECT_DIR}
    ${FFMPEG_PROJECT_DIR}
    ${THIRD_PARTY_DIR}/Include
	${THIRD_PARTY_DIR}/Include/Assimp
	${THIRD_PARTY_DIR}/Include/freetype2)

set(THIRD_PARTY_LIBS
	${AVCODEC_PROJECT_NAME}.lib
    ${AVFORMAT_PROJECT_NAME}.lib
	${AVUTIL_PROJECT_NAME}.lib
    ${SWSCALE_PROJECT_NAME}.lib
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


##------------------------------ Celeste ------------------------------##
set(CELESTE_PROJECT_NAME Celeste)
set(CELESTE_PROJECT_DIR ${CELESTE_DIR}/${CELESTE_PROJECT_NAME})

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
set_target_properties(${CELESTE_PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
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
set(MCF_LIBRARY_PROJECT_DIR ${PROJECT_SOURCE_DIR}/${MCF_LIBRARY_PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES ${MCF_LIBRARY_PROJECT_DIR}/Source/*.c ${MCF_LIBRARY_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${MCF_LIBRARY_PROJECT_DIR}/Include/*.h ${MCF_LIBRARY_PROJECT_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${MCF_LIBRARY_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${MCF_LIBRARY_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${MCF_LIBRARY_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${MCF_LIBRARY_PROJECT_DIR} FILES ${RES_FILES})

add_library(${MCF_LIBRARY_PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${MCF_LIBRARY_PROJECT_NAME} PUBLIC ${THIRD_PARTY_INCLUDES})
target_include_directories(${MCF_LIBRARY_PROJECT_NAME} PUBLIC ${CELESTE_PROJECT_DIR}/Include)
target_include_directories(${MCF_LIBRARY_PROJECT_NAME} PUBLIC ${MCF_LIBRARY_PROJECT_DIR}/Include)

target_link_libraries(${MCF_LIBRARY_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIBS})

target_compile_options(${MCF_LIBRARY_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)

add_dependencies(${MCF_LIBRARY_PROJECT_NAME} ${CELESTE_PROJECT_NAME})


##------------------------------ Test Modern Cocoa Farmer Library Project ------------------------------##
set(TEST_MCF_LIBRARY_PROJECT_NAME TestModernCocoaFarmerLibrary)
set(TEST_MCF_LIBRARY_PROJECT_DIR ${PROJECT_SOURCE_DIR}/${MCF_LIBRARY_PROJECT_NAME}/Tests)

file(GLOB_RECURSE SOURCE_FILES ${TEST_MCF_LIBRARY_PROJECT_DIR}/Source/*.c ${TEST_MCF_LIBRARY_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${TEST_MCF_LIBRARY_PROJECT_DIR}/Include/*.h ${TEST_MCF_LIBRARY_PROJECT_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${TEST_MCF_LIBRARY_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${TEST_MCF_LIBRARY_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${TEST_MCF_LIBRARY_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${TEST_MCF_LIBRARY_PROJECT_DIR} FILES ${RES_FILES})

add_library(${TEST_MCF_LIBRARY_PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${TEST_MCF_LIBRARY_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
set_target_properties(${TEST_MCF_LIBRARY_PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
set_target_properties(${TEST_MCF_LIBRARY_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${TEST_MCF_LIBRARY_PROJECT_NAME} PUBLIC ${THIRD_PARTY_INCLUDES})
target_include_directories(${TEST_MCF_LIBRARY_PROJECT_NAME} PUBLIC ${CELESTE_PROJECT_DIR}/Include)
target_include_directories(${TEST_MCF_LIBRARY_PROJECT_NAME} PUBLIC ${MCF_LIBRARY_PROJECT_DIR}/Include)
target_include_directories(${TEST_MCF_LIBRARY_PROJECT_NAME} PUBLIC ${TEST_MCF_LIBRARY_PROJECT_DIR}/Include)

target_link_libraries(${TEST_MCF_LIBRARY_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIBS})

target_compile_options(${TEST_MCF_LIBRARY_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)

add_dependencies(${TEST_MCF_LIBRARY_PROJECT_NAME} ${CELESTE_PROJECT_NAME} ${MCF_LIBRARY_PROJECT_NAME})


##------------------------------ Modern Cocoa Farmer Project ------------------------------##
set(MCF_PROJECT_NAME ModernCocoaFarmer)
set(MCF_PROJECT_DIR ${PROJECT_SOURCE_DIR}/${MCF_LIBRARY_PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES ${MCF_PROJECT_DIR}/Source/*.c ${MCF_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${MCF_PROJECT_DIR}/Include/*.h ${MCF_PROJECT_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${MCF_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${MCF_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${MCF_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${MCF_PROJECT_DIR} FILES ${RES_FILES})

add_executable(${MCF_PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${MCF_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
set_target_properties(${MCF_PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR})
set_target_properties(${MCF_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${MCF_PROJECT_NAME} PUBLIC ${THIRD_PARTY_INCLUDES})
target_include_directories(${MCF_PROJECT_NAME} PUBLIC ${CELESTE_PROJECT_DIR}/Include)
target_include_directories(${MCF_PROJECT_NAME} PUBLIC ${MCF_LIBRARY_PROJECT_DIR}/Include)
target_include_directories(${MCF_PROJECT_NAME} PUBLIC ${MCF_PROJECT_DIR}/Include)

target_link_libraries(${MCF_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIBS})
target_link_libraries(${MCF_PROJECT_NAME} PUBLIC ${MCF_LIBRARY_PROJECT_NAME})

target_compile_options(${CELESTE_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)

add_dependencies(${MCF_PROJECT_NAME} ${MCF_LIBRARY_PROJECT_NAME} ${CELESTE_PROJECT_NAME})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${MCF_PROJECT_NAME})
set_target_properties(${MCF_PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${MCF_PROJECT_DIR})


set(MCF_FOLDER_NAME "Modern Cocoa Farmer")
set_target_properties(${MCF_PROJECT_NAME} PROPERTIES FOLDER ${MCF_FOLDER_NAME})
set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES FOLDER ${MCF_FOLDER_NAME})
set_target_properties(${TEST_MCF_LIBRARY_PROJECT_NAME} PROPERTIES FOLDER ${MCF_FOLDER_NAME})

#add_custom_command(
#	TARGET ${PROJECT_NAME}
#	PRE_BUILD
#	COMMAND call "$(ProjectDir)Build Events/CopyDependencyFiles.bat" "$(TargetDir)" $(Configuration) $(Platform)
#	VERBATIM)