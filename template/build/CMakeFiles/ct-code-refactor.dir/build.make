# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wangzc/Documents/static-analysis/template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wangzc/Documents/static-analysis/template/build

# Include any dependencies generated for this target.
include CMakeFiles/ct-code-refactor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ct-code-refactor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ct-code-refactor.dir/flags.make

CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.o: CMakeFiles/ct-code-refactor.dir/flags.make
CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.o: ../CodeRefactor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangzc/Documents/static-analysis/template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.o -c /home/wangzc/Documents/static-analysis/template/CodeRefactor.cpp

CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangzc/Documents/static-analysis/template/CodeRefactor.cpp > CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.i

CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangzc/Documents/static-analysis/template/CodeRefactor.cpp -o CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.s

# Object files for target ct-code-refactor
ct__code__refactor_OBJECTS = \
"CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.o"

# External object files for target ct-code-refactor
ct__code__refactor_EXTERNAL_OBJECTS =

bin/ct-code-refactor: CMakeFiles/ct-code-refactor.dir/CodeRefactor.cpp.o
bin/ct-code-refactor: CMakeFiles/ct-code-refactor.dir/build.make
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangTooling.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangFormat.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangToolingInclusions.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangFrontend.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangDriver.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangParse.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangSerialization.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangSema.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangEdit.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangAnalysis.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangASTMatchers.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangAST.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangToolingCore.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangRewrite.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangLex.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libclangBasic.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMOption.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMFrontendOpenMP.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMTransformUtils.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMAnalysis.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMProfileData.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMObject.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMBitReader.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMCore.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMRemarks.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMBitstreamReader.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMMCParser.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMMC.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMDebugInfoCodeView.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMTextAPI.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMBinaryFormat.a
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMSupport.a
bin/ct-code-refactor: /usr/lib/x86_64-linux-gnu/libz.so
bin/ct-code-refactor: /usr/lib/x86_64-linux-gnu/libtinfo.so
bin/ct-code-refactor: /home/wangzc/Documents/llvm-project/install/lib/libLLVMDemangle.a
bin/ct-code-refactor: CMakeFiles/ct-code-refactor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wangzc/Documents/static-analysis/template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/ct-code-refactor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ct-code-refactor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ct-code-refactor.dir/build: bin/ct-code-refactor

.PHONY : CMakeFiles/ct-code-refactor.dir/build

CMakeFiles/ct-code-refactor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ct-code-refactor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ct-code-refactor.dir/clean

CMakeFiles/ct-code-refactor.dir/depend:
	cd /home/wangzc/Documents/static-analysis/template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wangzc/Documents/static-analysis/template /home/wangzc/Documents/static-analysis/template /home/wangzc/Documents/static-analysis/template/build /home/wangzc/Documents/static-analysis/template/build /home/wangzc/Documents/static-analysis/template/build/CMakeFiles/ct-code-refactor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ct-code-refactor.dir/depend
