cmake_minimum_required(VERSION 3.16)

project(CalculatorApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appCalculator
    main.cpp
    calculator.h
    calculator.cpp
)

qt_add_qml_module(appCalculator
    URI CalculatorApp
    VERSION 1.0
    QML_FILES
        Main.qml
)

target_link_libraries(appCalculator
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
)

set_target_properties(appCalculator PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
