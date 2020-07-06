set(LIBS 
    Dolce
    DolceScriptCommands
    Celeste
    CelesteScriptCommands
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

# Installer
set(CPACK_MONOLITHIC_INSTALL 1)

install(TARGETS ModernCocoaFarmer RUNTIME DESTINATION "bin")

set (CPACK_PACKAGE_NAME "Modern Cocoa Farmer")
set (CPACK_PACKAGE_VENDOR "CMake.org")
set (CPACK_PACKAGE_VERSION "1.0.0")
set (CPACK_PACKAGE_VERSION_MAJOR "1")
set (CPACK_PACKAGE_VERSION_MINOR "0")
set (CPACK_PACKAGE_VERSION_PATCH "0")
set (CPACK_PACKAGE_INSTALL_DIRECTORY "Modern Cocoa Farmer")
set(CPACK_INSTALLED_DIRECTORIES 
    "${PROJECT_SOURCE_DIR}/ModernCocoaFarmer/Resources" "bin/ModernCocoaFarmer/Resources"
    "${PROJECT_SOURCE_DIR}/Celeste/Celeste/Lua/Resources" "bin/Celeste/Celeste/Lua/Resources")

# Define NSIS installation types
set(CPACK_ALL_INSTALL_TYPES Full)
set(CPACK_PACKAGE_FILE_NAME "ModernCocoaFarmerSetup")
set(CPACK_PACKAGE_DIRECTORY "${PROJECT_SOURCE_DIR}/Install")
 
# Must be after the last CPACK macros
include(CPack)