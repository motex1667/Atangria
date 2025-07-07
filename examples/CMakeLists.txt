# Setup like GLFW examples.
link_libraries(atangria)
if(WIN32)
    set(ICON atangria.rc)
elseif (APPLE)
    set(ICON atangria.icns)
endif()

add_executable(helloworld WIN32 MACOSX_BUNDLE hello_world.cpp ${ICON})
set(ATA_GUI_BINARIES helloworld)

set_target_properties(${ATA_GUI_BINARIES} ${ATA_CONSOLE_BINARIES} PROPERTIES
                      C_STANDARD 99
                      CXX_STANDARD 11
                      FOLDER "ATA/examples")

if (APPLE)
	set_target_properties(helloworld PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Hello World")
	set_source_files_properties(atangria.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
	set_target_properties(${ATA_GUI_ONLY_BINARIES} PROPERTIES
                                  MACOSX_BUNDLE_SHORT_VERSION_STRING ${ATA_VERSION}
                                  MACOSX_BUNDLE_LONG_VERSION_STRING ${ATA_VERSION}
                                  MACOSX_BUNDLE_ICON_FILE atangria.icns
                                  MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/cmake/info.plist.in")
endif()