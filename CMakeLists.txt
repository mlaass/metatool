cmake_minimum_required(VERSION 3.12)
project(metastuff-generator)

set(CMAKE_CXX_STANDARD 17)

# Find CMake file for Clang
find_package(Clang REQUIRED)

# Add path to LLVM modules
set(CMAKE_MODULE_PATH
${CMAKE_MODULE_PATH}
"${LLVM_CMAKE_DIR}"
)

# import LLVM CMake functions
include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})


add_llvm_executable(metastuff-gen src/main.cpp)



target_include_directories(metastuff-gen
PUBLIC 3rdParty/argparse/include
)
target_compile_options(metastuff-gen PRIVATE -fexceptions)

target_link_libraries(metastuff-gen
PRIVATE clangTooling
PUBLIC fmt)


message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_subdirectory(3rdParty/argparse)
add_subdirectory(3rdParty/fmt)
