# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /root/webServer/MyWebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/webServer/MyWebServer

# Include any dependencies generated for this target.
include CMakeFiles/webserver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/webserver.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/webserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/webserver.dir/flags.make

CMakeFiles/webserver.dir/webserver/log.cc.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/webserver/log.cc.o: webserver/log.cc
CMakeFiles/webserver.dir/webserver/log.cc.o: CMakeFiles/webserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/webServer/MyWebServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/webserver.dir/webserver/log.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"webserver/log.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserver.dir/webserver/log.cc.o -MF CMakeFiles/webserver.dir/webserver/log.cc.o.d -o CMakeFiles/webserver.dir/webserver/log.cc.o -c /root/webServer/MyWebServer/webserver/log.cc

CMakeFiles/webserver.dir/webserver/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/webserver/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"webserver/log.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/webServer/MyWebServer/webserver/log.cc > CMakeFiles/webserver.dir/webserver/log.cc.i

CMakeFiles/webserver.dir/webserver/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/webserver/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"webserver/log.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/webServer/MyWebServer/webserver/log.cc -o CMakeFiles/webserver.dir/webserver/log.cc.s

CMakeFiles/webserver.dir/webserver/util.cc.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/webserver/util.cc.o: webserver/util.cc
CMakeFiles/webserver.dir/webserver/util.cc.o: CMakeFiles/webserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/webServer/MyWebServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/webserver.dir/webserver/util.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"webserver/util.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserver.dir/webserver/util.cc.o -MF CMakeFiles/webserver.dir/webserver/util.cc.o.d -o CMakeFiles/webserver.dir/webserver/util.cc.o -c /root/webServer/MyWebServer/webserver/util.cc

CMakeFiles/webserver.dir/webserver/util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/webserver/util.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"webserver/util.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/webServer/MyWebServer/webserver/util.cc > CMakeFiles/webserver.dir/webserver/util.cc.i

CMakeFiles/webserver.dir/webserver/util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/webserver/util.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"webserver/util.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/webServer/MyWebServer/webserver/util.cc -o CMakeFiles/webserver.dir/webserver/util.cc.s

CMakeFiles/webserver.dir/webserver/config.cc.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/webserver/config.cc.o: webserver/config.cc
CMakeFiles/webserver.dir/webserver/config.cc.o: CMakeFiles/webserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/webServer/MyWebServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/webserver.dir/webserver/config.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"webserver/config.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserver.dir/webserver/config.cc.o -MF CMakeFiles/webserver.dir/webserver/config.cc.o.d -o CMakeFiles/webserver.dir/webserver/config.cc.o -c /root/webServer/MyWebServer/webserver/config.cc

CMakeFiles/webserver.dir/webserver/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/webserver/config.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"webserver/config.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/webServer/MyWebServer/webserver/config.cc > CMakeFiles/webserver.dir/webserver/config.cc.i

CMakeFiles/webserver.dir/webserver/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/webserver/config.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"webserver/config.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/webServer/MyWebServer/webserver/config.cc -o CMakeFiles/webserver.dir/webserver/config.cc.s

# Object files for target webserver
webserver_OBJECTS = \
"CMakeFiles/webserver.dir/webserver/log.cc.o" \
"CMakeFiles/webserver.dir/webserver/util.cc.o" \
"CMakeFiles/webserver.dir/webserver/config.cc.o"

# External object files for target webserver
webserver_EXTERNAL_OBJECTS =

lib/libwebserver.so: CMakeFiles/webserver.dir/webserver/log.cc.o
lib/libwebserver.so: CMakeFiles/webserver.dir/webserver/util.cc.o
lib/libwebserver.so: CMakeFiles/webserver.dir/webserver/config.cc.o
lib/libwebserver.so: CMakeFiles/webserver.dir/build.make
lib/libwebserver.so: CMakeFiles/webserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/webServer/MyWebServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library lib/libwebserver.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/webserver.dir/build: lib/libwebserver.so
.PHONY : CMakeFiles/webserver.dir/build

CMakeFiles/webserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/webserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/webserver.dir/clean

CMakeFiles/webserver.dir/depend:
	cd /root/webServer/MyWebServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/webServer/MyWebServer /root/webServer/MyWebServer /root/webServer/MyWebServer /root/webServer/MyWebServer /root/webServer/MyWebServer/CMakeFiles/webserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/webserver.dir/depend

