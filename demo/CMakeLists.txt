PROJECT(demo)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

find_package(OpenCV REQUIRED)
find_package(gflags REQUIRED)

AUX_SOURCE_DIRECTORY(./common DIR_SRCS_common)
AUX_SOURCE_DIRECTORY(./image DIR_SRCS_image)
AUX_SOURCE_DIRECTORY(./demo DIR_SRCS_demo)

include_directories(
../include 
./image
./common
)

link_directories("../lib/")
add_executable(demo 
${DIR_SRCS_common} 
${DIR_SRCS_image} 
${DIR_SRCS_demo} 
)
target_link_libraries(demo libdeepsort.so ${OpenCV_LIBS} gflags "pthread")

include(CheckCXXCompilerFlag)  
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)  
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)  
if(COMPILER_SUPPORTS_CXX11)  
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  
elseif(COMPILER_SUPPORTS_CXX0X)  
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")  
else()  
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")  
endif()  
