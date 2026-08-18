cmake_minimum_required(VERSION 3.16)

project(IVIAudioPlayer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS
    Quick
    QuickControls2
    QuickDialogs2
    Multimedia
)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appIVIAudioPlayer
    main.cpp
    resources.qrc
)

qt_add_qml_module(appIVIAudioPlayer
    URI IVIAudioPlayer
    VERSION 1.0
    QML_FILES
        Main.qml
        SplashScreen.qml
        HomePage.qml
        SourceCard.qml
        SourcePage.qml
        IVILogo.qml
    SOURCES
        soniqueplaybackengine.h
        soniqueplaybackengine.cpp
)

set_target_properties(appIVIAudioPlayer PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING
        ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appIVIAudioPlayer
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::QuickDialogs2
        Qt6::Multimedia
)

include(GNUInstallDirs)

install(TARGETS appIVIAudioPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
