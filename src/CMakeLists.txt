file(GLOB_RECURSE tmp *.cpp *.hpp)
set(${PROJECT_NAME}_lib_src ${${PROJECT_NAME}_lib_src} ${tmp} VideoFile.h VideoInput.h VideoFile.cpp utils.h utils.cpp)

list(APPEND CUDA_NVCC_FLAGS "-std=c++11")

if(NOT CMAKE_CUDA_FLAGS)
    set(CMAKE_CUDA_FLAGS "-cudart shared")
endif()

find_package(CUDA REQUIRED)

set(CUDA_LIBRARIES PUBLIC ${CUDA_LIBRARIES})

include_directories(./include)
include_directories(/usr/local/cuda-8.0/include)

message(STATUS ${${PROJECT_NAME}_examples_src})
cuda_add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_lib_src})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LINKER_LIBS} nvvl nvcuvid cuda)
