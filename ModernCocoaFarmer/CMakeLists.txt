set(LIBS 
    Celeste
    curlpp)
    
set(TEST_LIBS
    CelesteMocks
    CelesteTestResources
    CelesteTestUtils)

build_library(
    NAME ModernCocoaFarmerLibrary 
    FOLDER "Modern Cocoa Farmer" 
    TYPE SHARED 
    LIBS "${LIBS}"
    TEST_LIBS "${TEST_LIBS}")

target_compile_definitions(ModernCocoaFarmerLibrary PRIVATE -DBUILDING_MCF_LIBRARY_DLL)