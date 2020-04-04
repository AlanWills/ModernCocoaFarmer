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

set(MCF_BUILDS_DIR ${PROJECT_SOURCE_DIR}/Build/${CMAKE_VS_PLATFORM_NAME})
set(MCF_DIR ${PROJECT_SOURCE_DIR}/${CMAKE_PROJECT_NAME})
set(CELESTE_DIR ${PROJECT_SOURCE_DIR}/Celeste)
set(THIRD_PARTY_FOLDER "3rd Party")
set(THIRD_PARTY_DIR ${CELESTE_DIR}/3rdParty)
set(THIRD_PARTY_LIB_DIR ${THIRD_PARTY_DIR}/lib/${CMAKE_VS_PLATFORM_NAME})
set(THIRD_PARTY_DLL_DIR ${THIRD_PARTY_DIR}/dll/${CMAKE_VS_PLATFORM_NAME})
##---------------------------- end Globals ----------------------------##


##---------------------------- assimp ----------------------------##
set(ASSIMP_PROJECT_NAME assimp)
set(ASSIMP_PROJECT_DIR "${THIRD_PARTY_DIR}/assimp")

add_subdirectory(${ASSIMP_PROJECT_DIR} ${ASSIMP_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${ASSIMP_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
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
#    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
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
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
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
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
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
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end openal-soft ----------------------------##


##---------------------------- freealut ----------------------------##
set(FREEALUT_PROJECT_NAME alut)
set(FREEALUT_PROJECT_DIR "${THIRD_PARTY_DIR}/freealut")

add_subdirectory(${FREEALUT_PROJECT_DIR} ${FREEALUT_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${FREEALUT_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end freealut ----------------------------##


##---------------------------- freetype2 ----------------------------##
set(FREETYPE2_PROJECT_NAME freetype)
set(FREETYPE2_PROJECT_DIR "${THIRD_PARTY_DIR}/freetype2")

add_subdirectory(${FREETYPE2_PROJECT_DIR} ${FREETYPE2_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${FREETYPE2_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR}
    DEBUG_POSTFIX "")
#---------------------------- end freetype2 ----------------------------##


##---------------------------- glew ----------------------------##
set(GLEW_PROJECT_NAME glew)
set(GLEW_PROJECT_DIR "${THIRD_PARTY_DIR}/glew")

add_subdirectory(${GLEW_PROJECT_DIR} ${GLEW_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${GLEW_PROJECT_NAME} PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
##---------------------------- end glew ----------------------------##


##---------------------------- glfw ----------------------------##
set(GLFW_PROJECT_NAME glfw3)
set(GLFW_PROJECT_DIR "${THIRD_PARTY_DIR}/glfw")

add_subdirectory(${GLFW_PROJECT_DIR} ${GLFW_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(glfw PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR}
    OUTPUT_NAME ${GLFW_PROJECT_NAME}
    ARCHIVE_OUTPUT_NAME ${GLFW_PROJECT_NAME})
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
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end lua ----------------------------##


##---------------------------- SOIL2 ----------------------------##
set(SOIL2_PROJECT_NAME SOIL2)
set(SOIL2_PROJECT_DIR "${THIRD_PARTY_DIR}/SOIL2")

add_subdirectory(${SOIL2_PROJECT_DIR} ${SOIL2_PROJECT_DIR}/build ${EXCLUDE})

set_target_properties(${SOIL2_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
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
    RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_DLL_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR}
    OUTPUT_NAME ${TINYXML2_PROJECT_NAME}
    ARCHIVE_OUTPUT_NAME ${TINYXML2_PROJECT_NAME}
    DEBUG_POSTFIX "")
#---------------------------- end tinyxml2 ----------------------------##


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
    glew
    glfw
    ${LIBCURL_PROJECT_NAME}.lib
	${LUA_PROJECT_NAME}.lib
	${OPENAL_SOFT_PROJECT_NAME}.lib
    opengl32
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


##------------------------------ Test Utils Project ------------------------------##
set(TEST_UTILS_PROJECT_NAME TestUtils)
set(TEST_UTILS_PROJECT_DIR ${CELESTE_DIR}/${TEST_UTILS_PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES ${TEST_UTILS_PROJECT_DIR}/Source/*.c ${TEST_UTILS_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${TEST_UTILS_PROJECT_DIR}/Include/*.h ${TEST_UTILS_PROJECT_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${TEST_UTILS_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${TEST_UTILS_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${TEST_UTILS_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${TEST_UTILS_PROJECT_DIR} FILES ${RES_FILES})

add_library(${TEST_UTILS_PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${TEST_UTILS_PROJECT_NAME} PROPERTIES 
    FOLDER Testing
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17)

target_include_directories(${TEST_UTILS_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_INCLUDES} 
    ${TEST_UTILS_PROJECT_DIR}/Include)
target_link_directories(${TEST_UTILS_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR} ${PROJECT_BINARY_DIR})
target_link_libraries(${TEST_UTILS_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIBS})

target_compile_options(${TEST_UTILS_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)


##------------------------------ Dolce ------------------------------##
set(DOLCE_PROJECT_DIR "${CELESTE_DIR}/Dolce")
add_subdirectory(${DOLCE_PROJECT_DIR} ${DOLCE_PROJECT_DIR}/Build ${EXCLUDE})


##------------------------------ DolceLua ------------------------------##
set(DOLCE_LUA_PROJECT_DIR "${CELESTE_DIR}/DolceLua")
add_subdirectory(${DOLCE_LUA_PROJECT_DIR} ${DOLCE_LUA_PROJECT_DIR}/Build ${EXCLUDE})


##------------------------------ Celeste ------------------------------##
set(CELESTE_PROJECT_NAME Celeste)
set(CELESTE_PROJECT_DIR ${CELESTE_DIR}/Celeste)

file(GLOB_RECURSE SOURCE_FILES ${CELESTE_PROJECT_DIR}/Source/*.c ${CELESTE_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CELESTE_PROJECT_DIR}/Include/*.h ${CELESTE_PROJECT_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${CELESTE_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${CELESTE_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${CELESTE_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CELESTE_PROJECT_DIR} FILES ${RES_FILES})

add_library(Celeste SHARED ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(Celeste PROPERTIES 
    FOLDER Celeste
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17)

target_include_directories(Celeste PUBLIC 
	${THIRD_PARTY_INCLUDES}
	${CELESTE_PROJECT_DIR}/Include)

target_link_directories(Celeste PUBLIC ${THIRD_PARTY_LIB_DIR})

target_link_libraries(Celeste PUBLIC 
	${THIRD_PARTY_LIBS}
    Dolce)

target_compile_options(Celeste PRIVATE /MP4 /W4 /WX)
target_compile_definitions(Celeste PUBLIC -DGLM_FORCE_SILENT_WARNINGS PRIVATE -DBUILDING_CELESTE_ENGINE_DLL)


##------------------------------ CelesteLua ------------------------------##
set(CELESTE_LUA_PROJECT_DIR "${CELESTE_DIR}/CelesteLua")
add_subdirectory(${CELESTE_LUA_PROJECT_DIR} ${CELESTE_LUA_PROJECT_DIR}/Build ${EXCLUDE})


##------------------------------ Celeste Test Globals ------------------------------##
set(CELESTE_TESTS_SOLUTION_FOLDER ${CELESTE_PROJECT_NAME}/Tests)


##------------------------------ Celeste Mocks Project ------------------------------##
set(CELESTE_MOCKS_PROJECT_NAME CelesteMocks)
set(CELESTE_MOCKS_PROJECT_DIR ${CELESTE_DIR}/${CELESTE_MOCKS_PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES ${CELESTE_MOCKS_PROJECT_DIR}/Source/*.c ${CELESTE_MOCKS_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CELESTE_MOCKS_PROJECT_DIR}/Include/*.h ${CELESTE_MOCKS_PROJECT_DIR}/Include/*.hpp)

source_group(TREE ${CELESTE_MOCKS_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${CELESTE_MOCKS_PROJECT_DIR} FILES ${HEADER_FILES})

add_library(${CELESTE_MOCKS_PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${CELESTE_MOCKS_PROJECT_NAME} PROPERTIES
    FOLDER ${CELESTE_TESTS_SOLUTION_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17)

target_include_directories(${CELESTE_MOCKS_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_INCLUDES} 
    ${CELESTE_PROJECT_DIR}/Include 
    ${CELESTE_MOCKS_PROJECT_DIR}/Include)
target_link_directories(${CELESTE_MOCKS_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR} ${PROJECT_BINARY_DIR})
target_link_libraries(${CELESTE_MOCKS_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIBS} ${CELESTE_PROJECT_NAME}.lib)

target_compile_options(${CELESTE_MOCKS_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)
target_compile_definitions(${CELESTE_MOCKS_PROJECT_NAME} PRIVATE -DCELESTE_MOCKS_STATIC_LIB -DGLM_FORCE_SILENT_WARNINGS)

add_dependencies(${CELESTE_MOCKS_PROJECT_NAME} ${CELESTE_PROJECT_NAME})


##------------------------------ Celeste Test Resources Project ------------------------------##
set(CELESTE_TEST_RESOURCES_PROJECT_NAME CelesteTestResources)
set(CELESTE_TEST_RESOURCES_PROJECT_DIR ${CELESTE_DIR}/${CELESTE_TEST_RESOURCES_PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Source/*.c ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Include/*.h ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${CELESTE_TEST_RESOURCES_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${CELESTE_TEST_RESOURCES_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CELESTE_TEST_RESOURCES_PROJECT_DIR} FILES ${RES_FILES})

add_library(${CELESTE_TEST_RESOURCES_PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${CELESTE_TEST_RESOURCES_PROJECT_NAME} PROPERTIES
    FOLDER ${CELESTE_TESTS_SOLUTION_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17)

target_include_directories(${CELESTE_TEST_RESOURCES_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_INCLUDES}
    ${CELESTE_PROJECT_DIR}/Include 
    ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Include)
target_link_directories(${CELESTE_TEST_RESOURCES_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR} ${PROJECT_BINARY_DIR})
target_link_libraries(${CELESTE_TEST_RESOURCES_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_LIBS} 
    ${CELESTE_PROJECT_NAME}.lib)

target_compile_options(${CELESTE_TEST_RESOURCES_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)
target_compile_definitions(${CELESTE_TEST_RESOURCES_PROJECT_NAME} PRIVATE -DCELESTE_TEST_RESOURCES_STATIC_LIB -DGLM_FORCE_SILENT_WARNINGS)

add_dependencies(
    ${CELESTE_TEST_RESOURCES_PROJECT_NAME} 
    ${CELESTE_PROJECT_NAME})


##------------------------------ Celeste Test Utils Project ------------------------------##
set(CELESTE_TEST_UTILS_PROJECT_NAME CelesteTestUtils)
set(CELESTE_TEST_UTILS_PROJECT_DIR ${CELESTE_DIR}/${CELESTE_TEST_UTILS_PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES ${CELESTE_TEST_UTILS_PROJECT_DIR}/Source/*.c ${CELESTE_TEST_UTILS_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CELESTE_TEST_UTILS_PROJECT_DIR}/Include/*.h ${CELESTE_TEST_UTILS_PROJECT_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${CELESTE_TEST_UTILS_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${CELESTE_TEST_UTILS_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${CELESTE_TEST_UTILS_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CELESTE_TEST_UTILS_PROJECT_DIR} FILES ${RES_FILES})

add_library(${CELESTE_TEST_UTILS_PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${CELESTE_TEST_UTILS_PROJECT_NAME} PROPERTIES 
    FOLDER ${CELESTE_TESTS_SOLUTION_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17)

target_include_directories(${CELESTE_TEST_UTILS_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_INCLUDES} 
    ${CELESTE_PROJECT_DIR}/Include 
    ${TEST_UTILS_PROJECT_DIR}/Include
    ${CELESTE_MOCKS_PROJECT_DIR}/Include
    ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Include
    ${CELESTE_TEST_UTILS_PROJECT_DIR}/Include)
target_link_directories(${CELESTE_TEST_UTILS_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR} ${PROJECT_BINARY_DIR})
target_link_libraries(${CELESTE_TEST_UTILS_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_LIBS} 
    ${CELESTE_PROJECT_NAME}.lib
    ${TEST_UTILS_PROJECT_NAME}.lib
    ${CELESTE_MOCKS_PROJECT_NAME}.lib
    ${CELESTE_TEST_RESOURCES_PROJECT_NAME}.lib)

target_compile_options(${CELESTE_TEST_UTILS_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)
target_compile_definitions(${CELESTE_TEST_UTILS_PROJECT_NAME} PRIVATE -DCELESTE_TEST_UTILS_STATIC_LIB -DGLM_FORCE_SILENT_WARNINGS)

add_dependencies(${CELESTE_TEST_UTILS_PROJECT_NAME} 
    ${CELESTE_PROJECT_NAME} 
    ${TEST_UTILS_PROJECT_NAME}
    ${CELESTE_TEST_RESOURCES_PROJECT_NAME}
    ${CELESTE_MOCKS_PROJECT_NAME})


##------------------------------ Test Celeste Project ------------------------------##
set(TEST_CELESTE_PROJECT_NAME TestCeleste)
set(TEST_CELESTE_PROJECT_DIR ${CELESTE_PROJECT_DIR}/Tests)

file(GLOB_RECURSE SOURCE_FILES ${TEST_CELESTE_PROJECT_DIR}/Source/*.c ${TEST_CELESTE_PROJECT_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${TEST_CELESTE_PROJECT_DIR}/Include/*.h ${TEST_CELESTE_PROJECT_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${TEST_CELESTE_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${TEST_CELESTE_PROJECT_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${TEST_CELESTE_PROJECT_DIR} FILES ${HEADER_FILES})
source_group(TREE ${TEST_CELESTE_PROJECT_DIR} FILES ${RES_FILES})

add_library(${TEST_CELESTE_PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${TEST_CELESTE_PROJECT_NAME} PROPERTIES
    FOLDER ${CELESTE_TESTS_SOLUTION_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17
    VS_DEBUGGER_WORKING_DIRECTORY ${TEST_CELESTE_PROJECT_DIR})

target_include_directories(${TEST_CELESTE_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_INCLUDES}
    ${CELESTE_PROJECT_DIR}/Include 
    ${TEST_UTILS_PROJECT_DIR}/Include 
    ${CELESTE_MOCKS_PROJECT_DIR}/Include 
    ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Include 
    ${CELESTE_TEST_UTILS_PROJECT_DIR}/Include 
    ${TEST_CELESTE_PROJECT_DIR}/Include)
target_link_directories(${TEST_CELESTE_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR} ${PROJECT_BINARY_DIR})
target_link_libraries(${TEST_CELESTE_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_LIBS} 
    ${CELESTE_PROJECT_NAME}.lib
    ${TEST_UTILS_PROJECT_NAME}.lib
    ${CELESTE_MOCKS_PROJECT_NAME}.lib
    ${CELESTE_TEST_RESOURCES_PROJECT_NAME}.lib
    ${CELESTE_TEST_UTILS_PROJECT_NAME}.lib)

target_compile_options(${TEST_CELESTE_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)
target_compile_definitions(${TEST_CELESTE_PROJECT_NAME} PRIVATE 
    -DGLM_FORCE_SILENT_WARNINGS)

add_dependencies(
    ${TEST_CELESTE_PROJECT_NAME} 
    ${CELESTE_PROJECT_NAME} 
    ${TEST_UTILS_PROJECT_NAME} 
    ${CELESTE_MOCKS_PROJECT_NAME}
    ${CELESTE_TEST_RESOURCES_PROJECT_NAME}
    ${CELESTE_TEST_UTILS_PROJECT_NAME})


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

file(GLOB_RECURSE SOURCE_FILES ${MCF_DIR}/Source/*.c ${MCF_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${MCF_DIR}/Include/*.h ${MCF_DIR}/Include/*.hpp)

source_group(TREE ${MCF_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${MCF_DIR} FILES ${HEADER_FILES})

add_library(${MCF_LIBRARY_PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17)

target_include_directories(${MCF_LIBRARY_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_INCLUDES} 
    ${CELESTE_PROJECT_DIR}/Include 
    ${MCF_DIR}/Include)
target_link_directories(${MCF_LIBRARY_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_LIB_DIR} 
    ${PROJECT_BINARY_DIR})
target_link_libraries(${MCF_LIBRARY_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_LIBS} 
    Celeste)

target_compile_options(${MCF_LIBRARY_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)
target_compile_definitions(${MCF_LIBRARY_PROJECT_NAME} PRIVATE -DBUILDING_MCF_LIBRARY_DLL)

add_dependencies(${MCF_LIBRARY_PROJECT_NAME} ${CELESTE_PROJECT_NAME})


##------------------------------ Test Modern Cocoa Farmer Library Project ------------------------------##
set(TEST_MCF_LIBRARY_PROJECT_NAME TestModernCocoaFarmerLibrary)
set(TEST_MCF_DIR ${MCF_DIR}/Tests)

file(GLOB_RECURSE SOURCE_FILES ${TEST_MCF_DIR}/Source/*.c ${TEST_MCF_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${TEST_MCF_DIR}/Include/*.h ${TEST_MCF_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${TEST_MCF_DIR}/Resources/*.*)

source_group(TREE ${TEST_MCF_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${TEST_MCF_DIR} FILES ${HEADER_FILES})
source_group(TREE ${TEST_MCF_DIR} FILES ${RES_FILES})

add_library(${TEST_MCF_LIBRARY_PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${TEST_MCF_LIBRARY_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17
    VS_DEBUGGER_WORKING_DIRECTORY ${MCF_DIR})

target_include_directories(${TEST_MCF_LIBRARY_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_INCLUDES} 
    ${CELESTE_PROJECT_DIR}/Include
    ${TEST_UTILS_PROJECT_DIR}/Include 
    ${CELESTE_TEST_UTILS_PROJECT_DIR}/Include
    ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Include
    ${CELESTE_MOCKS_PROJECT_DIR}/Include
    ${MCF_DIR}/Include
    ${TEST_MCF_DIR}/Include)
target_link_directories(${TEST_MCF_LIBRARY_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR} ${PROJECT_BINARY_DIR})
target_link_libraries(${TEST_MCF_LIBRARY_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_LIBS} 
    ${CELESTE_PROJECT_NAME}.lib
    ${TEST_UTILS_PROJECT_NAME}.lib
    ${CELESTE_TEST_UTILS_PROJECT_NAME}.lib
    ${CELESTE_MOCKS_PROJECT_NAME}.lib
    ${CELESTE_TEST_RESOURCES_PROJECT_NAME}.lib
    ${MCF_LIBRARY_PROJECT_NAME}.lib
    CelesteLua)

target_compile_options(${TEST_MCF_LIBRARY_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)
target_compile_definitions(${TEST_MCF_LIBRARY_PROJECT_NAME} PRIVATE -DGLM_FORCE_SILENT_WARNINGS)

add_dependencies(
    ${TEST_MCF_LIBRARY_PROJECT_NAME} 
    ${CELESTE_PROJECT_NAME}
    ${TEST_UTILS_PROJECT_NAME} 
    ${CELESTE_TEST_UTILS_PROJECT_NAME} 
    ${CELESTE_MOCKS_PROJECT_NAME}
    ${CELESTE_TEST_RESOURCES_PROJECT_NAME}
    ${MCF_LIBRARY_PROJECT_NAME})


##------------------------------ ModernCocoaFarmerLua ------------------------------##
set(MCF_LUA_PROJECT_DIR "${PROJECT_SOURCE_DIR}/ModernCocoaFarmerLua")
add_subdirectory(${MCF_LUA_PROJECT_DIR} ${MCF_LUA_PROJECT_DIR}/Build ${EXCLUDE})


##------------------------------ Modern Cocoa Farmer Project ------------------------------##
set(MCF_PROJECT_NAME ModernCocoaFarmer)

file(GLOB_RECURSE RES_FILES ${MCF_DIR}/Resources/*.*)
file(GLOB_RECURSE CELESTE_RES_FILES ${CELESTE_PROJECT_DIR}/Resources/*.*)

source_group(TREE ${MCF_DIR} FILES ${RES_FILES})
source_group(TREE ${CELESTE_PROJECT_DIR} FILES ${CELESTE_RES_FILES})

add_executable(${MCF_PROJECT_NAME} ${MCF_DIR}/Main.cpp ${MCF_DIR}/MCFGame.cpp ${MCF_DIR}/MCFGame.h ${RES_FILES} ${CELESTE_RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${MCF_PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR} 
    LIBRARY_OUTPUT_DIRECTORY ${MCF_BUILDS_DIR}
    CXX_STANDARD 17
    VS_DEBUGGER_WORKING_DIRECTORY ${MCF_DIR})

target_include_directories(${MCF_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_INCLUDES} 
    ${CELESTE_PROJECT_DIR}/Include 
    ${MCF_DIR}/Include)
target_link_directories(${MCF_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_LIB_DIR} 
    ${PROJECT_BINARY_DIR})
target_link_libraries(${MCF_PROJECT_NAME} PUBLIC 
    ${THIRD_PARTY_LIBS} 
    ${CELESTE_PROJECT_NAME}.lib
    Dolce
    DolceLua
    Celeste
    CelesteLua
    ModernCocoaFarmerLibrary
    ModernCocoaFarmerLua)

target_compile_options(${CELESTE_PROJECT_NAME} PRIVATE /MP4 /W4 /WX)

add_dependencies(${MCF_PROJECT_NAME} ${CELESTE_PROJECT_NAME} ${MCF_LIBRARY_PROJECT_NAME})


set(MCF_FOLDER_NAME "Modern Cocoa Farmer")
set_target_properties(${MCF_PROJECT_NAME} PROPERTIES FOLDER ${MCF_FOLDER_NAME})
set_target_properties(${MCF_LIBRARY_PROJECT_NAME} PROPERTIES FOLDER ${MCF_FOLDER_NAME})
set_target_properties(${TEST_MCF_LIBRARY_PROJECT_NAME} PROPERTIES FOLDER ${MCF_FOLDER_NAME}/Tests)