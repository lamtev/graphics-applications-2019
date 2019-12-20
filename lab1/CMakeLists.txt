cmake_minimum_required(VERSION 3.10.2)
project(lab1)

set(CMAKE_CXX_STANDARD 17)
add_executable(lab1 src/lab1.cpp src/stretching.cpp src/stretching.h src/hist.cpp src/hist.h src/FigReader.cpp src/FigReader.h src/Fig.h src/equalization.cpp src/equalization.h src/Plotter.cpp src/Plotter.h)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(lab1 ${OpenCV_LIBS})

find_package(PythonLibs 2.7)
target_include_directories(lab1 PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(lab1 ${PYTHON_LIBRARIES})
target_include_directories(lab1 PRIVATE ../matplotlib)
