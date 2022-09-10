cmake_minimum_required(VERSION 3.12)
project(metatool)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-fconcepts)

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


add_llvm_executable(metatool-gen src/main.cpp)

add_subdirectory(templ8-parser)
message(STATUS "templ8 include dirs: ${TEMPL8_INCLUDE_DIRS}")


target_include_directories(metatool-gen
PUBLIC 3rdParty/argparse/include
PUBLIC 3rdParty/tinyxml2
PUBLIC templ8-parser
PUBLIC templ8-parser/
${ANTLR4_INCLUDE_DIRS}
${TEMPL8_INCLUDE_DIRS}
)

target_compile_options(metatool-gen PRIVATE -fexceptions)

target_link_libraries(metatool-gen
PRIVATE clangTooling
PUBLIC templ8
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
