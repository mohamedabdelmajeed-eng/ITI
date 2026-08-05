cmake_minimum_required(VERSION 3.16)

project(Task_2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(
        "${CMAKE_CURRENT_LIST_DIR}/importedcontent"
    )
endif()

qt_add_executable(appTask_2
    main.cpp
)

qt_add_qml_module(appTask_2
    URI Task_2
    VERSION 1.0

    QML_FILES
        Main.qml
        CarCard.qml

    RESOURCES
        images/car1.jpg
        images/car2.jpg
        images/car3.jpg
        images/logo.png
)

set_target_properties(appTask_2 PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION
        ${PROJECT_VERSION}

    MACOSX_BUNDLE_SHORT_VERSION_STRING
        ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}

    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTask_2
    PRIVATE Qt6::Quick
)

install(
    TARGETS appTask_2

    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)