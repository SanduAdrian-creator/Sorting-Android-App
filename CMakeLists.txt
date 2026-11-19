cmake_minimum_required(VERSION 3.21)
project(CuvinteApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickControls2)
qt_standard_project_setup(REQUIRES 6.5)

# Executabilul ajunge în bin/
if(NOT ANDROID)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif()

qt_add_executable(CuvinteApp
    src/main.cpp
    src/WordStorage.cpp
    src/WordListModel.cpp
    include/cuvinte/WordStorage.h
    include/cuvinte/WordListModel.h
)

qt_add_qml_module(CuvinteApp
    URI CuvinteApp
    VERSION 1.0
    QML_FILES qml/Main.qml
)

target_include_directories(CuvinteApp PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(CuvinteApp PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
)

# Pe Windows copiază automat DLL-urile Qt lângă executabil, în bin/
if(WIN32)
    find_program(WINDEPLOYQT windeployqt HINTS "${Qt6_DIR}/../../../bin")
    if(WINDEPLOYQT)
        add_custom_command(TARGET CuvinteApp POST_BUILD
            COMMAND ${WINDEPLOYQT} --qmldir ${CMAKE_SOURCE_DIR}/qml $<TARGET_FILE:CuvinteApp>
        )
    endif()
endif()