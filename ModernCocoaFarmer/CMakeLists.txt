set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)

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
    TEST_LIBS "${TEST_LIBS}"
    APP_FILE "${PROJECT_SOURCE_DIR}/ModernCocoaFarmer/Installer/ModernCocoaFarmer.rc")

install(TARGETS ModernCocoaFarmer RUNTIME DESTINATION . COMPONENT applications)
install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION . COMPONENT applications)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/ModernCocoaFarmer/Resources"
        DESTINATION "ModernCocoaFarmer"
        COMPONENT applications)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/Celeste/Celeste/Lua/Resources"
        DESTINATION "Celeste/Celeste/Lua"
        COMPONENT applications)

set(CPACK_PACKAGE_NAME "Modern Cocoa Farmer")
set(CPACK_PACKAGE_VENDOR "CMake.org")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Modern Cocoa Farmer")
set(CPACK_PACKAGE_EXECUTABLES "ModernCocoaFarmer.exe" "Modern Cocoa Farmer")
set(CPACK_NSIS_DISPLAY_NAME "Modern Cocoa Farmer")
set(CPACK_NSIS_EXECUTABLES_DIRECTORY .)

# Define NSIS installation types
set(CPACK_ALL_INSTALL_TYPES Full)
set(CPACK_PACKAGE_FILE_NAME "ModernCocoaFarmerSetup")
set(CPACK_PACKAGE_DIRECTORY "${PROJECT_SOURCE_DIR}/Install/${CMAKE_BUILD_TYPE}")

# Installer Icons
set(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/ModernCocoaFarmer/Resources/Installer\\\\InstallerIcon.bmp")
set(CPACK_NSIS_MUI_ICON "${PROJECT_SOURCE_DIR}/ModernCocoaFarmer/Resources/Installer/InstallerIcon.ico")
set(CPACK_NSIS_MUI_UNIICON "${PROJECT_SOURCE_DIR}/ModernCocoaFarmer/Resources/Installer/InstallerIcon.ico")

set(CPACK_NSIS_MENU_LINKS "ModernCocoaFarmer.exe" "Modern Cocoa Farmer")
set(CPACK_NSIS_MUI_FINISHPAGE_RUN "ModernCocoaFarmer.exe")
 
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_ALL applications)
set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Modern Cocoa Farmer")
set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)

# Must be after the last CPACK macros
include(CPack)