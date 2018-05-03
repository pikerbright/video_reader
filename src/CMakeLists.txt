file(GLOB_RECURSE tmp *.cpp *.hpp)
set(${PROJECT_NAME}_lib_src ${${PROJECT_NAME}_lib_src} ${tmp} VideoFile.h VideoInput.h VideoFile.cpp utils.h utils.cpp)

list(APPEND CUDA_NVCC_FLAGS "-std=c++11")

if(NOT CMAKE_CUDA_FLAGS)
    set(CMAKE_CUDA_FLAGS "-cudart shared")
endif()

find_package(CUDA REQUIRED)

include_directories(./include)
include_directories(${CUDA_INCLUDE_DIRS})

message(STATUS ${${PROJECT_NAME}_examples_src})
cuda_add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_lib_src} main.cpp cuda/utils.cu)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")
target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LINKER_LIBS} nvvl nvcuvid cuda)

set(WITH_OPENCV 1)

if (WITH_OPENCV)
    # If we are in here, they explicitly asked for it, so make it required
    find_package(OpenCV CONFIG REQUIRED COMPONENTS core cudaarithm cudaimgproc imgcodecs)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_OPENCV=1)
    target_link_libraries(${PROJECT_NAME} opencv_core ${OpenCV_LIBS})
endif()
