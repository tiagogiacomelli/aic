cmake_minimum_required (VERSION 2.6)
project (aic)

set(EXECUTABLE_OUTPUT_PATH "bin")
set (aic_lib_VERSION_MAJOR 0)
set (aic_lib_VERSION_MINOR 01)

# Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")

# Project folders
SET(AIC_LIB_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/aic_lib)
SET(AIC_TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/aic_test)

# Find source files
file(GLOB LIB_SOURCES ${AIC_LIB_ROOT_DIR}/src/*.cpp)

# Specify additional locations of header files
include_directories(
  ${AIC_LIB_ROOT_DIR}/include
)

# Create shared library
add_library(aic_lib STATIC ${LIB_SOURCES})

add_executable(${PROJECT_NAME}_serial_test ${AIC_TEST_ROOT_DIR}/src/serial_test.cpp)
target_link_libraries (${PROJECT_NAME}_serial_test aic_lib)

add_executable(${PROJECT_NAME}_can_test ${AIC_TEST_ROOT_DIR}/src/can_test.cpp)
target_link_libraries (${PROJECT_NAME}_can_test aic_lib)

# add the install targets
install (TARGETS aic_lib ${PROJECT_NAME}_serial_test ${PROJECT_NAME}_can_test
         ARCHIVE DESTINATION /usr/local/lib
         LIBRARY DESTINATION /usr/local/lib
         RUNTIME DESTINATION /usr/local/bin)

INSTALL (DIRECTORY ${AIC_LIB_ROOT_DIR}/
  DESTINATION /usr/local
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
  PATTERN ".git" EXCLUDE
  )
