﻿# CMakeList.txt : CMake project for CMakeProject12, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OpenCVExample")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (OpenCVExample "CMakeProject12.cpp" "CMakeProject12.h" "Advanced.cpp")
target_link_libraries(OpenCVExample ${OpenCV_LIBS})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenCVExample PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
