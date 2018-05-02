file(GLOB_RECURSE tmp *.cpp *.hpp)
set(${PROJECT_NAME}_lib_src ${${PROJECT_NAME}_lib_src} ${tmp} VideoFile.h VideoInput.h VideoFile.cpp utils.h utils.cpp)

include_directories(./include)

message(STATUS ${${PROJECT_NAME}_examples_src})
cuda_add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_lib_src})
target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LINKER_LIBS} nvvl nvcuvid cuda)
