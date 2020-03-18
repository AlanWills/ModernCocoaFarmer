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
    SET(USE_PREBUILT_LIBS ON CACHE BOOL "" FORCE)
ENDIF()

IF(USE_PREBUILT_LIBS)
    SET(EXCLUDE EXCLUDE_FROM_ALL CACHE STRING "" FORCE)
ELSE()
    SET(EXCLUDE "" CACHE STRING "" FORCE)
ENDIF()

set(CELESTE_DIR ${PROJECT_SOURCE_DIR}/Celeste)
set(MCF_BUILDS_DIR ${PROJECT_SOURCE_DIR}/Build/${CMAKE_VS_PLATFORM_NAME})
set(THIRD_PARTY_DIR ${CELESTE_DIR}/3rdParty)
set(THIRD_PARTY_LIB_DIR ${THIRD_PARTY_DIR}/lib/${CMAKE_VS_PLATFORM_NAME})
##---------------------------- end Globals ----------------------------##


##---------------------------- assimp ----------------------------##
set(ASSIMP_PROJECT_NAME assimp)
set(ASSIMP_PROJECT_DIR "${THIRD_PARTY_DIR}/assimp")

add_subdirectory(${ASSIMP_PROJECT_DIR} ${ASSIMP_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${ASSIMP_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR}
    OUTPUT_NAME ${ASSIMP_PROJECT_NAME}
    ARCHIVE_OUTPUT_NAME ${ASSIMP_PROJECT_NAME})
#---------------------------- end freealut ----------------------------##


##---------------------------- crossguid ----------------------------##
set(CROSSGUID_PROJECT_NAME crossguid)
set(CROSSGUID_PROJECT_DIR "${THIRD_PARTY_DIR}/crossguid")

# This doesn't seem to work for crossguid
# Follow instructions in the readme

#add_subdirectory(${CROSSGUID_PROJECT_DIR} ${CROSSGUID_PROJECT_DIR}/build ${EXCLUDE})

#set_target_properties(${CROSSGUID_PROJECT_NAME} PROPERTIES 
#    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
#    LIBRARY_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR}
#    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR}
#    OUTPUT_NAME ${CROSSGUID_PROJECT_NAME}
#    ARCHIVE_OUTPUT_NAME ${CROSSGUID_PROJECT_NAME}
#    DEBUG_POSTFIX "")
##---------------------------- end curl ----------------------------##


##---------------------------- curl ----------------------------##
set(LIBCURL_PROJECT_NAME libcurl)
set(CURL_PROJECT_DIR "${THIRD_PARTY_DIR}/curl")

add_subdirectory(${CURL_PROJECT_DIR} ${CURL_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${LIBCURL_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR}
    OUTPUT_NAME ${LIBCURL_PROJECT_NAME}
    ARCHIVE_OUTPUT_NAME ${LIBCURL_PROJECT_NAME})
##---------------------------- end curl ----------------------------##


##---------------------------- curlpp ----------------------------##
set(CURLPP_PROJECT_NAME curlpp)
set(CURLPP_PROJECT_DIR "${THIRD_PARTY_DIR}/curlpp")
set(CURL_INCLUDE_DIR ${CURL_PROJECT_DIR}/include)
set(CURL_LIBRARY ${THIRD_PARTY_LIB_DIR}/${CMAKE_BUILD_TYPE}/${LIBCURL_PROJECT_NAME}.lib)

add_subdirectory(${CURLPP_PROJECT_DIR} ${CURLPP_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${CURLPP_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
##---------------------------- end curlpp ----------------------------##


##---------------------------- dirent ----------------------------##
set(DIRENT_PROJECT_DIR "${THIRD_PARTY_DIR}/dirent")

add_subdirectory(${DIRENT_PROJECT_DIR} ${DIRENT_PROJECT_DIR}/build ${EXCLUDE})
##---------------------------- end dirent ----------------------------##


##---------------------------- ffmpeg ----------------------------##
set(FFMPEG_PROJECT_DIR "${THIRD_PARTY_DIR}/ffmpeg")
set(AVCODEC_PROJECT_NAME avcodec)
set(AVFORMAT_PROJECT_NAME avformat)
set(AVUTIL_PROJECT_NAME avutil)
set(SWSCALE_PROJECT_NAME swscale)
##---------------------------- end ffmpeg ----------------------------##


##---------------------------- openal-soft ----------------------------##
set(OPENAL_SOFT_PROJECT_NAME OpenAL32)
set(OPENAL_SOFT_PROJECT_DIR "${THIRD_PARTY_DIR}/openal-soft")
set(OPENAL_INCLUDE_DIR ${OPENAL_SOFT_PROJECT_DIR}/include/AL)
set(OPENAL_LIBRARY ${THIRD_PARTY_LIB_DIR}/${CMAKE_BUILD_TYPE}/${OPENAL_SOFT_PROJECT_NAME}.lib)

add_subdirectory(${OPENAL_SOFT_PROJECT_DIR} ${OPENAL_SOFT_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(OpenAL PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end openal-soft ----------------------------##


##---------------------------- freealut ----------------------------##
set(FREEALUT_PROJECT_NAME alut)
set(FREEALUT_PROJECT_DIR "${THIRD_PARTY_DIR}/freealut")

add_subdirectory(${FREEALUT_PROJECT_DIR} ${FREEALUT_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${FREEALUT_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end freealut ----------------------------##


##---------------------------- freetype2 ----------------------------##
set(FREETYPE2_PROJECT_NAME freetype)
set(FREETYPE2_PROJECT_DIR "${THIRD_PARTY_DIR}/freetype2")

add_subdirectory(${FREETYPE2_PROJECT_DIR} ${FREETYPE2_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${FREETYPE2_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR}
    DEBUG_POSTFIX "")
#---------------------------- end freetype2 ----------------------------##


##---------------------------- glew ----------------------------##
set(GLEW_PROJECT_NAME glew)
set(GLEW_PROJECT_DIR "${THIRD_PARTY_DIR}/glew")

add_subdirectory(${GLEW_PROJECT_DIR} ${GLEW_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${GLEW_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
##---------------------------- end glew ----------------------------##


##---------------------------- glfw ----------------------------##
set(GLFW_PROJECT_NAME glfw3)
set(GLFW_PROJECT_DIR "${THIRD_PARTY_DIR}/glfw")

add_subdirectory(${GLFW_PROJECT_DIR} ${GLFW_PROJECT_DIR}/build ${EXCLUDE})

#set_target_properties(${GLFW_PROJECT_NAME} PROPERTIES 
#    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
#    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR}
#    OUTPUT_NAME ${GLFW_PROJECT_NAME}
#    ARCHIVE_OUTPUT_NAME ${GLFW_PROJECT_NAME})
##---------------------------- end glfw ----------------------------##


##---------------------------- glm ----------------------------##
set(GLM_PROJECT_NAME glm)
set(GLM_PROJECT_DIR "${THIRD_PARTY_DIR}/glm")

add_subdirectory(${GLM_PROJECT_DIR} ${GLM_PROJECT_DIR}/build ${EXCLUDE})
##---------------------------- end glm ----------------------------##


##---------------------------- lua ----------------------------##
set(LUA_PROJECT_NAME lua)
set(LUA_PROJECT_DIR "${THIRD_PARTY_DIR}/lua")

add_subdirectory(${LUA_PROJECT_DIR} ${LUA_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(liblua PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end lua ----------------------------##


##---------------------------- SOIL2 ----------------------------##
set(SOIL2_PROJECT_NAME SOIL2)
set(SOIL2_PROJECT_DIR "${THIRD_PARTY_DIR}/SOIL2")

add_subdirectory(${SOIL2_PROJECT_DIR} ${SOIL2_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${SOIL2_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end lua ----------------------------##


##---------------------------- sol2 ----------------------------##
set(SOL2_PROJECT_NAME sol2)
set(SOL2_PROJECT_DIR "${THIRD_PARTY_DIR}/sol2")

add_subdirectory(${SOL2_PROJECT_DIR} ${SOL2_PROJECT_DIR}/build ${EXCLUDE})
#---------------------------- end sol2 ----------------------------##


##---------------------------- tinyxml2 ----------------------------##
set(TINYXML2_PROJECT_NAME tinyxml2)
set(TINYXML2_PROJECT_DIR "${THIRD_PARTY_DIR}/tinyxml2")

add_subdirectory(${TINYXML2_PROJECT_DIR} ${TINYXML2_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(tinyxml2 PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR}
    OUTPUT_NAME ${TINYXML2_PROJECT_NAME}
    ARCHIVE_OUTPUT_NAME ${TINYXML2_PROJECT_NAME}
    DEBUG_POSTFIX "")
#---------------------------- end lua ----------------------------##


##---------------------------- 3rd Party ----------------------------##
set(THIRD_PARTY_INCLUDES
    ${ASSIMP_PROJECT_DIR}/include
    ${ASSIMP_PROJECT_DIR}/build/include     #for config.h
    ${CROSSGUID_PROJECT_DIR}/include
    ${CURL_PROJECT_DIR}/include
    ${CURLPP_PROJECT_DIR}/include
    ${DIRENT_PROJECT_DIR}/include
    ${FFMPEG_PROJECT_DIR}
    ${FREEALUT_PROJECT_DIR}/include
    ${FREETYPE2_PROJECT_DIR}/include
    ${GLEW_PROJECT_DIR}/include
    ${GLFW_PROJECT_DIR}/include
    ${GLM_PROJECT_DIR}
    ${LUA_PROJECT_DIR}/src
    ${LUA_PROJECT_DIR}/build    #for luaconf.h
    ${OPENAL_SOFT_PROJECT_DIR}/include
    ${OPENAL_SOFT_PROJECT_DIR}/include/AL
    ${SOL2_PROJECT_DIR}/include
    ${SOIL2_PROJECT_DIR}/src
    ${TINYXML2_PROJECT_DIR})

set(THIRD_PARTY_LIBS
	${AVCODEC_PROJECT_NAME}.lib
    ${AVFORMAT_PROJECT_NAME}.lib
	${AVUTIL_PROJECT_NAME}.lib
    ${SWSCALE_PROJECT_NAME}.lib
	${ASSIMP_PROJECT_NAME}.lib
    ${CROSSGUID_PROJECT_NAME}.lib
    ${CURLPP_PROJECT_NAME}.lib
	${FREEALUT_PROJECT_NAME}.lib
    ${FREETYPE2_PROJECT_NAME}.lib
    ${GLEW_PROJECT_NAME}.lib
    ${GLFW_PROJECT_NAME}dll.lib
    ${LIBCURL_PROJECT_NAME}.lib
	${LUA_PROJECT_NAME}.lib
	${OPENAL_SOFT_PROJECT_NAME}.lib
    opengl32.lib
    ${SOIL2_PROJECT_NAME}.lib
    ${TINYXML2_PROJECT_NAME}.lib)
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

target_link_directories(${CELESTE_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR})
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

target_link_directories(${MCF_LIBRARY_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR})
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

target_link_directories(${TEST_MCF_LIBRARY_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR})
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

target_link_directories(${MCF_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR})
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