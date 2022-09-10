cmake_minimum_required(VERSION 3.12)

project("templ8-parser")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be at least 17
set(CMAKE_CXX_STANDARD 20)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/tools/antlr-4.10.1-complete.jar)

# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# CMake commands copied by the CMake file for CImg

# To use PKG_CHECK_MODULES to find some optional packages
# find_package(PkgConfig)


# Call macro to add lexer and grammar to your build dependencies.
antlr_target(Templ8GrammarParser templ8.g4 VISITOR OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/parser/)

# add our project source directories
set(TEMPL8_INCLUDE_DIRS
${ANTLR4_INCLUDE_DIRS}
${PROJECT_SOURCE_DIR}
${CMAKE_CURRENT_BINARY_DIR}/antlr4_runtime/src/antlr4_runtime/runtime/Cpp/runtime/src
${PROJECT_SOURCE_DIR}/parser/
PARENT_SCOPE)

include_directories(
  ${TEMPL8_INCLUDE_DIRS}
  )


add_executable(templ8-test main.cpp Visitor.cpp Templ8.cpp
               ${ANTLR_Templ8GrammarParser_CXX_OUTPUTS})

add_library(templ8 Visitor.cpp Templ8.cpp ${ANTLR_Templ8GrammarParser_CXX_OUTPUTS})

# link required libraries
target_link_libraries(templ8-test antlr4_static ${SYSTEM_LIBS} pthread)
target_link_libraries(templ8 antlr4_static ${SYSTEM_LIBS} pthread)

# copy the input file next to the generated executable
add_custom_command(TARGET templ8-test POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${PROJECT_SOURCE_DIR}/test.templ8"
  $<TARGET_FILE_DIR:templ8-test>)

# necessary because the default working directory of Visual Studio
# is not the same as the one in which the binary is created
# so we copy the input file twice:
# one for when you launch the executale in Visual Studio (CTRL+F5)
# one for when you launch it normally
if (WIN32)
add_custom_command(TARGET templ8-test POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${PROJECT_SOURCE_DIR}/tes.templ8"
  $<TARGET_FILE_DIR:templ8-test>/../)
endif()

