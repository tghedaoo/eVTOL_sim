# Build Instructions for eVTOL simulator project.

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(eVTOL_sim)

add_executable(sim_run src/sim_run.cpp)
add_executable(state_machine src/state_machine.cpp)

set(OPENCV_INCLUDE_DIR /home/jdhao/local/include/opencv4/)
set(OPENCV_LIB_DIR /home/jdhao/local/lib/)

message(STATUS "OpenCV library path: ${OPENCV_LIB_DIR}")

# set include directory
target_include_directories(write_text PUBLIC "${OPENCV_INCLUDE_DIR}")

# set library directory
target_link_directories(write_text PUBLIC "${OPENCV_LIB_DIR}")

# link specific object files we need
target_link_libraries(write_text opencv_imgcodecs opencv_core opencv_imgproc)