cmake_minimum_required(VERSION 3.12)
project(metastuff-generator)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
# set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
# Find CMake file for Clang
find_package(LLVM 9 REQUIRED)
set(Clang_DIR  /usr/lib/llvm-9/lib/)
find_package(Clang REQUIRED)

# Add path to LLVM modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_CMAKE_DIR}")

# import LLVM CMake functions
include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})


add_llvm_executable(metastuff-gen src/main.cpp)



target_include_directories(metastuff-gen
PUBLIC 3rdParty/argparse/include
PUBLIC 3rdParty/tinyxml2
)

target_compile_options(metastuff-gen PRIVATE -fexceptions)

target_link_libraries(metastuff-gen
PRIVATE clangTooling
PUBLIC tinyxml2)


message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Using ClangConfig.cmake in: ${CLANG_DIR}")

add_subdirectory(3rdParty/tinyxml2)

# add_executable(testapp
#  test/test.cpp)

# target_include_directories(testapp
# PUBLIC test
# )
