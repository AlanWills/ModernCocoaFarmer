set(LIBS 
    Dolce
    DolceLua
    Celeste
    CelesteLua
    curlpp)
    
set(TEST_LIBS
    CelesteMocks
    CelesteTestResources
    CelesteTestUtils)
    
cbt_build_project(
    NAME ModernCocoaFarmer 
    FOLDER "Modern Cocoa Farmer" 
    TYPE EXECUTABLE 
    LIBS "${LIBS}"
    TEST_LIBS "${TEST_LIBS}")