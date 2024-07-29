cmake_minimum_required(VERSION 3.20)
project(llvm-assignment)

#===============================================================================
# 1. LLVM CONFIGURATION
#===============================================================================
set(LT_LLVM_INSTALL_DIR "" CACHE PATH "LLVM installation directory")

list(APPEND CMAKE_PREFIX_PATH "${LT_LLVM_INSTALL_DIR}/lib/cmake/llvm/")

find_package(LLVM CONFIG)
if("${LLVM_VERSION_MAJOR}" VERSION_LESS 15)
  message(FATAL_ERROR "Found LLVM ${LLVM_VERSION_MAJOR}, but need LLVM 15 or above")
endif()

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})

#===============================================================================
# 2. LLVM-ASSIGNMENT BUILD CONFIGURATION
#===============================================================================
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

#===============================================================================
# 3. TARGET
#===============================================================================
add_library(Obfuscator SHARED Obfuscator.cpp)

target_link_libraries(Obfuscator
  "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>")
