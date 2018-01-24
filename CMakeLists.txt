cmake_minimum_required(VERSION 3.1)

project(math-py-test)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
FIND_PACKAGE(PythonInterp REQUIRED)
FIND_PACKAGE(PythonLibs REQUIRED)
if(${PYTHON_VERSION_MAJOR} EQUAL 3)
    FIND_PACKAGE(Boost COMPONENTS python3)
elseif()
    FIND_PACKAGE(Boost COMPONENTS python)
endif()

INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(3rdparty)
INCLUDE_DIRECTORIES(gui)

PYTHON_ADD_MODULE(function_wrapper function.cpp
    pythonembedded.hpp )

add_library(gui gui/mainwindow.cpp 3rdparty/qcustomplot.cpp gui/dialog.cpp)
target_link_libraries(gui Qt5::Widgets Qt5::PrintSupport)

add_executable(${PROJECT_NAME} "main.cpp" function.cpp)

target_link_libraries(${PROJECT_NAME} -lboost_python ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} gui)

FILE(COPY function.py derivative.py DESTINATION .)
