# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

src/client/moc_ChatClient.cpp: /Users/mihyar/Desktop/OS2\ Project/Chat-Application-with-Client-Server/src/client/ChatClient.h
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating src/client/moc_ChatClient.cpp"
	cd "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/src/client" && /opt/homebrew/opt/qt/share/qt/libexec/moc "@/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/src/client/moc_ChatClient.cpp_parameters"

CMakeFiles/client.dir/src/client/client.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/client/client.cpp.o: /Users/mihyar/Desktop/OS2\ Project/Chat-Application-with-Client-Server/src/client/client.cpp
CMakeFiles/client.dir/src/client/client.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client.dir/src/client/client.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/src/client/client.cpp.o -MF CMakeFiles/client.dir/src/client/client.cpp.o.d -o CMakeFiles/client.dir/src/client/client.cpp.o -c "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/src/client/client.cpp"

CMakeFiles/client.dir/src/client/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/client.dir/src/client/client.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/src/client/client.cpp" > CMakeFiles/client.dir/src/client/client.cpp.i

CMakeFiles/client.dir/src/client/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/client/client.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/src/client/client.cpp" -o CMakeFiles/client.dir/src/client/client.cpp.s

CMakeFiles/client.dir/src/client/ChatClient.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/client/ChatClient.cpp.o: /Users/mihyar/Desktop/OS2\ Project/Chat-Application-with-Client-Server/src/client/ChatClient.cpp
CMakeFiles/client.dir/src/client/ChatClient.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/client.dir/src/client/ChatClient.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/src/client/ChatClient.cpp.o -MF CMakeFiles/client.dir/src/client/ChatClient.cpp.o.d -o CMakeFiles/client.dir/src/client/ChatClient.cpp.o -c "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/src/client/ChatClient.cpp"

CMakeFiles/client.dir/src/client/ChatClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/client.dir/src/client/ChatClient.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/src/client/ChatClient.cpp" > CMakeFiles/client.dir/src/client/ChatClient.cpp.i

CMakeFiles/client.dir/src/client/ChatClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/client/ChatClient.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/src/client/ChatClient.cpp" -o CMakeFiles/client.dir/src/client/ChatClient.cpp.s

CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.o: src/client/moc_ChatClient.cpp
CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.o -MF CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.o.d -o CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.o -c "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/src/client/moc_ChatClient.cpp"

CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/src/client/moc_ChatClient.cpp" > CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.i

CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/src/client/moc_ChatClient.cpp" -o CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/src/client/client.cpp.o" \
"CMakeFiles/client.dir/src/client/ChatClient.cpp.o" \
"CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client: CMakeFiles/client.dir/src/client/client.cpp.o
client: CMakeFiles/client.dir/src/client/ChatClient.cpp.o
client: CMakeFiles/client.dir/src/client/moc_ChatClient.cpp.o
client: CMakeFiles/client.dir/build.make
client: /opt/homebrew/opt/qt/lib/QtWidgets.framework/Versions/A/QtWidgets
client: /opt/homebrew/opt/qt/lib/QtGui.framework/Versions/A/QtGui
client: /opt/homebrew/opt/qt/lib/QtCore.framework/Versions/A/QtCore
client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client
.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend: src/client/moc_ChatClient.cpp
	cd "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server" "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server" "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug" "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug" "/Users/mihyar/Desktop/OS2 Project/Chat-Application-with-Client-Server/cmake-build-debug/CMakeFiles/client.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/client.dir/depend

