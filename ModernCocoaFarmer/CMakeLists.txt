set(LIBS 
    Celeste
    curlpp)

build_library(
    NAME ModernCocoaFarmerLibrary 
    FOLDER "Modern Cocoa Farmer" 
    TYPE SHARED 
    LIBS "${LIBS}")

target_compile_definitions(ModernCocoaFarmerLibrary PRIVATE -DBUILDING_MCF_LIBRARY_DLL)