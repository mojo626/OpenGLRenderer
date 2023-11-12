# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ben/Desktop/Coding/Cpp/OpenGLRenderer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ben/Desktop/Coding/Cpp/OpenGLRenderer

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/ben/Desktop/Coding/Cpp/OpenGLRenderer/CMakeFiles /Users/ben/Desktop/Coding/Cpp/OpenGLRenderer//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/ben/Desktop/Coding/Cpp/OpenGLRenderer/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named game

# Build rule for target.
game: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 game
.PHONY : game

# fast build rule for target.
game/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/build
.PHONY : game/fast

#=============================================================================
# Target rules for targets named uninstall

# Build rule for target.
uninstall: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 uninstall
.PHONY : uninstall

# fast build rule for target.
uninstall/fast:
	$(MAKE) $(MAKESILENT) -f lib/glfw/CMakeFiles/uninstall.dir/build.make lib/glfw/CMakeFiles/uninstall.dir/build
.PHONY : uninstall/fast

#=============================================================================
# Target rules for targets named glfw

# Build rule for target.
glfw: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 glfw
.PHONY : glfw

# fast build rule for target.
glfw/fast:
	$(MAKE) $(MAKESILENT) -f lib/glfw/src/CMakeFiles/glfw.dir/build.make lib/glfw/src/CMakeFiles/glfw.dir/build
.PHONY : glfw/fast

#=============================================================================
# Target rules for targets named update_mappings

# Build rule for target.
update_mappings: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 update_mappings
.PHONY : update_mappings

# fast build rule for target.
update_mappings/fast:
	$(MAKE) $(MAKESILENT) -f lib/glfw/src/CMakeFiles/update_mappings.dir/build.make lib/glfw/src/CMakeFiles/update_mappings.dir/build
.PHONY : update_mappings/fast

glad.o: glad.c.o
.PHONY : glad.o

# target to build an object file
glad.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/glad.c.o
.PHONY : glad.c.o

glad.i: glad.c.i
.PHONY : glad.i

# target to preprocess a source file
glad.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/glad.c.i
.PHONY : glad.c.i

glad.s: glad.c.s
.PHONY : glad.s

# target to generate assembly for a file
glad.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/glad.c.s
.PHONY : glad.c.s

include/Perlin.o: include/Perlin.cpp.o
.PHONY : include/Perlin.o

# target to build an object file
include/Perlin.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/include/Perlin.cpp.o
.PHONY : include/Perlin.cpp.o

include/Perlin.i: include/Perlin.cpp.i
.PHONY : include/Perlin.i

# target to preprocess a source file
include/Perlin.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/include/Perlin.cpp.i
.PHONY : include/Perlin.cpp.i

include/Perlin.s: include/Perlin.cpp.s
.PHONY : include/Perlin.s

# target to generate assembly for a file
include/Perlin.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/include/Perlin.cpp.s
.PHONY : include/Perlin.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/main.cpp.s
.PHONY : main.cpp.s

util/stb_image.o: util/stb_image.cpp.o
.PHONY : util/stb_image.o

# target to build an object file
util/stb_image.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/util/stb_image.cpp.o
.PHONY : util/stb_image.cpp.o

util/stb_image.i: util/stb_image.cpp.i
.PHONY : util/stb_image.i

# target to preprocess a source file
util/stb_image.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/util/stb_image.cpp.i
.PHONY : util/stb_image.cpp.i

util/stb_image.s: util/stb_image.cpp.s
.PHONY : util/stb_image.s

# target to generate assembly for a file
util/stb_image.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/util/stb_image.cpp.s
.PHONY : util/stb_image.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... uninstall"
	@echo "... update_mappings"
	@echo "... game"
	@echo "... glfw"
	@echo "... glad.o"
	@echo "... glad.i"
	@echo "... glad.s"
	@echo "... include/Perlin.o"
	@echo "... include/Perlin.i"
	@echo "... include/Perlin.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... util/stb_image.o"
	@echo "... util/stb_image.i"
	@echo "... util/stb_image.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

