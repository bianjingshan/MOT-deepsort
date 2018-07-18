PROJECT(matching_app)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)
find_package(OpenCV REQUIRED)

INCLUDE_DIRECTORIES(
./src/errmsg
./src/thirdPart
./src/thirdPart/Eigen
./src/thirdPart/munkres
./src/thirdPart/munkres/adapters
./src/matching
./src/feature
./src/common
./src/image
)
#LINK_DIRECTORIES("./lib")
AUX_SOURCE_DIRECTORY(./src/errmsg DIR_SRCS_errmsg)
AUX_SOURCE_DIRECTORY(./src/thirdPart DIR_SRCS_hungarianoper)
AUX_SOURCE_DIRECTORY(./src/thirdPart/munkres DIR_SRCS_munkres)
AUX_SOURCE_DIRECTORY(./src/thirdPart/munkres/adapters DIR_SRCS_munkres_adapters)
AUX_SOURCE_DIRECTORY(./src/matching DIR_SRCS_matching)
AUX_SOURCE_DIRECTORY(./src/feature DIR_SRCS_feature)
AUX_SOURCE_DIRECTORY(./src/common DIR_SRCS_common)
AUX_SOURCE_DIRECTORY(./src/image DIR_SRCS_image)
AUX_SOURCE_DIRECTORY(./src/matching_app DIR_SRCS_matching_app)


add_executable(sort 
${DIR_SRCS_common} 
${DIR_SRCS_image} 
${DIR_SRCS_hungarianoper} 
${DIR_SRCS_munkres} 
${DIR_SRCS_munkres_adapters} 
${DIR_SRCS_feature} 
${DIR_SRCS_matching} 
${DIR_SRCS_matching_app})
target_link_libraries(sort 
${OpenCV_LIBS} 
"pthread")

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
