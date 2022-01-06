cmake_minimum_required(VERSION 3.13.4)
project(template)


list(APPEND CMAKE_PREFIX_PATH "${CT_Clang_INSTALL_DIR}/lib/cmake/clang/")

find_package(Clang REQUIRED CONFIG)

include_directories(SYSTEM "${LLVM_INCLUDE_DIRS};${CLANG_INCLUDE_DIRS}")

# Use the same C++ standard as LLVM does
# set(CMAKE_CXX_STANDARD 14 CACHE STRING "")

# Compiler flags
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall\
#     -fdiagnostics-color=always")

# LLVM/Clang is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

# -fvisibility-inlines-hidden is set when building LLVM and on Darwin warnings
# are triggered if llvm-tutor is built without this flag (though otherwise it
# builds fine). For consistency, add it here too.
# include(CheckCXXCompilerFlag)
# check_cxx_compiler_flag("-fvisibility-inlines-hidden"
#   SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG)
# if(${SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG} EQUAL "1")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
# endif()

# Set the build directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

#===============================================================================
# 4. ADD SUB-TARGETS
# Doing this at the end so that all definitions and link/include paths are
# available for the sub-projects.
#===============================================================================\

add_executable(find-class-decls FindClassDecls.cpp)

target_link_libraries(find-class-decls clangTooling)
# add_library(HelloWorld SHARED HelloWorld.cpp)

# add_library(find-class-decls SHARED FindClassDecls.cpp)
# target_include_directories(CodeRefactor PRIVATE CodeRefactor.cpp)
# target_include_directories(ct-code-refactor PRIVATE )