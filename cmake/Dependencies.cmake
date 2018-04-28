set(${PROJECT_NAME}_LINKER_LIBS)

find_os_arch(${PROJECT_NAME}_Platform ${PROJECT_NAME}_Arch)

message(STATUS ${${PROJECT_NAME}_Platform})
set(${PROJECT_NAME}_INSTALL_INCLUDE_PREFIX include)
set(${PROJECT_NAME}_INSTALL_LIB_PREFIX lib/${${PROJECT_NAME}_Platform}/${${PROJECT_NAME}_Arch})
set(${PROJECT_NAME}_INSTALL_BIN_PREFIX bin)

if (${USE_OpenCV})
  find_package(OpenCV PATHS ${OpenCV_DIR} NO_DEFAULT_PATH QUIET COMPONENTS core highgui imgproc imgcodecs videoio)
  if (NOT OpenCV_FOUND) # if not OpenCV 3.x, then try to find OpenCV 2.x in default path
    find_package(OpenCV REQUIRED QUIET COMPONENTS core highgui imgproc)
  endif ()
  if (${OpenCV_VERSION} VERSION_GREATER "2.4.13")
    find_package(OpenCV REQUIRED QUIET COMPONENTS core highgui imgproc imgcodecs videoio)
  endif ()
  include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})
  list(APPEND ${PROJECT_NAME}_LINKER_LIBS ${OpenCV_LIBS})
  message(STATUS "Found OpenCV: ${OpenCV_CONFIG_PATH} (found version ${OpenCV_VERSION})")
endif ()
