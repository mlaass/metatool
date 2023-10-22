cmake_minimum_required(VERSION 3.12)
project(metatool)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-fconcepts)

# set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
# set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
set(USE_LLVM_VERSION 17)

# Find CMake file for Clang
find_package(LLVM ${USE_LLVM_VERSION} REQUIRED)
find_package(Clang ${USE_LLVM_VERSION} REQUIRED)

# Add path to LLVM modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_CMAKE_DIR}")

# import LLVM CMake functions
include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})

set(LLVM_LINK_COMPONENTS support)

add_llvm_executable(metatool src/main.cpp)

add_subdirectory(templ8-parser)
message(STATUS "templ8 include dirs: ${TEMPL8_INCLUDE_DIRS}")

target_include_directories(metatool
  PUBLIC 3rdParty/argparse/include
  PUBLIC 3rdParty/tinyxml2
  PUBLIC templ8-parser
  PUBLIC templ8-parser/
  ${ANTLR4_INCLUDE_DIRS}
  ${TEMPL8_INCLUDE_DIRS}
)

target_compile_options(metatool PRIVATE -fexceptions)

target_link_libraries(metatool
  PRIVATE clangTooling
  PUBLIC templ8
  PUBLIC tinyxml2)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Using ClangConfig.cmake in: ${CLANG_DIR}")

add_subdirectory(3rdParty/tinyxml2)

add_executable(test test/test.cpp)