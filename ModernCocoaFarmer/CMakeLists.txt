set(LIBS 
    Celeste
    curlpp)

build_library(NAME ModernCocoaFarmerLibrary FOLDER "Modern Cocoa Farmer/Packages" TYPE SHARED LIBS "${LIBS}")

target_compile_definitions(ModernCocoaFarmerLibrary PRIVATE -DBUILDING_MCF_LIBRARY_DLL)


##------------------------------ Test Modern Cocoa Farmer Library Project ------------------------------##
set(TEST_MCF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Tests)
add_subdirectory(${TEST_MCF_DIR} ${TEST_MCF_DIR}/Build)