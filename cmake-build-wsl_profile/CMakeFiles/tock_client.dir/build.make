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
CMAKE_SOURCE_DIR = /mnt/c/Users/adzer/CLionProjects/tock-client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile

# Include any dependencies generated for this target.
include CMakeFiles/tock_client.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/tock_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tock_client.dir/flags.make

CMakeFiles/tock_client.dir/src/mainClient.c.o: CMakeFiles/tock_client.dir/flags.make
CMakeFiles/tock_client.dir/src/mainClient.c.o: ../src/mainClient.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tock_client.dir/src/mainClient.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tock_client.dir/src/mainClient.c.o -c /mnt/c/Users/adzer/CLionProjects/tock-client/src/mainClient.c

CMakeFiles/tock_client.dir/src/mainClient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tock_client.dir/src/mainClient.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/adzer/CLionProjects/tock-client/src/mainClient.c > CMakeFiles/tock_client.dir/src/mainClient.c.i

CMakeFiles/tock_client.dir/src/mainClient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tock_client.dir/src/mainClient.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/adzer/CLionProjects/tock-client/src/mainClient.c -o CMakeFiles/tock_client.dir/src/mainClient.c.s

CMakeFiles/tock_client.dir/src/game.c.o: CMakeFiles/tock_client.dir/flags.make
CMakeFiles/tock_client.dir/src/game.c.o: ../src/game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/tock_client.dir/src/game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tock_client.dir/src/game.c.o -c /mnt/c/Users/adzer/CLionProjects/tock-client/src/game.c

CMakeFiles/tock_client.dir/src/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tock_client.dir/src/game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/adzer/CLionProjects/tock-client/src/game.c > CMakeFiles/tock_client.dir/src/game.c.i

CMakeFiles/tock_client.dir/src/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tock_client.dir/src/game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/adzer/CLionProjects/tock-client/src/game.c -o CMakeFiles/tock_client.dir/src/game.c.s

CMakeFiles/tock_client.dir/src/mainSDL.c.o: CMakeFiles/tock_client.dir/flags.make
CMakeFiles/tock_client.dir/src/mainSDL.c.o: ../src/mainSDL.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/tock_client.dir/src/mainSDL.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tock_client.dir/src/mainSDL.c.o -c /mnt/c/Users/adzer/CLionProjects/tock-client/src/mainSDL.c

CMakeFiles/tock_client.dir/src/mainSDL.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tock_client.dir/src/mainSDL.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/adzer/CLionProjects/tock-client/src/mainSDL.c > CMakeFiles/tock_client.dir/src/mainSDL.c.i

CMakeFiles/tock_client.dir/src/mainSDL.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tock_client.dir/src/mainSDL.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/adzer/CLionProjects/tock-client/src/mainSDL.c -o CMakeFiles/tock_client.dir/src/mainSDL.c.s

CMakeFiles/tock_client.dir/src/linkedlist.c.o: CMakeFiles/tock_client.dir/flags.make
CMakeFiles/tock_client.dir/src/linkedlist.c.o: ../src/linkedlist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/tock_client.dir/src/linkedlist.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tock_client.dir/src/linkedlist.c.o -c /mnt/c/Users/adzer/CLionProjects/tock-client/src/linkedlist.c

CMakeFiles/tock_client.dir/src/linkedlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tock_client.dir/src/linkedlist.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/adzer/CLionProjects/tock-client/src/linkedlist.c > CMakeFiles/tock_client.dir/src/linkedlist.c.i

CMakeFiles/tock_client.dir/src/linkedlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tock_client.dir/src/linkedlist.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/adzer/CLionProjects/tock-client/src/linkedlist.c -o CMakeFiles/tock_client.dir/src/linkedlist.c.s

CMakeFiles/tock_client.dir/src/card.c.o: CMakeFiles/tock_client.dir/flags.make
CMakeFiles/tock_client.dir/src/card.c.o: ../src/card.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/tock_client.dir/src/card.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tock_client.dir/src/card.c.o -c /mnt/c/Users/adzer/CLionProjects/tock-client/src/card.c

CMakeFiles/tock_client.dir/src/card.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tock_client.dir/src/card.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/adzer/CLionProjects/tock-client/src/card.c > CMakeFiles/tock_client.dir/src/card.c.i

CMakeFiles/tock_client.dir/src/card.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tock_client.dir/src/card.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/adzer/CLionProjects/tock-client/src/card.c -o CMakeFiles/tock_client.dir/src/card.c.s

CMakeFiles/tock_client.dir/src/gameRule.c.o: CMakeFiles/tock_client.dir/flags.make
CMakeFiles/tock_client.dir/src/gameRule.c.o: ../src/gameRule.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/tock_client.dir/src/gameRule.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tock_client.dir/src/gameRule.c.o -c /mnt/c/Users/adzer/CLionProjects/tock-client/src/gameRule.c

CMakeFiles/tock_client.dir/src/gameRule.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tock_client.dir/src/gameRule.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/adzer/CLionProjects/tock-client/src/gameRule.c > CMakeFiles/tock_client.dir/src/gameRule.c.i

CMakeFiles/tock_client.dir/src/gameRule.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tock_client.dir/src/gameRule.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/adzer/CLionProjects/tock-client/src/gameRule.c -o CMakeFiles/tock_client.dir/src/gameRule.c.s

CMakeFiles/tock_client.dir/src/Player/player.c.o: CMakeFiles/tock_client.dir/flags.make
CMakeFiles/tock_client.dir/src/Player/player.c.o: ../src/Player/player.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/tock_client.dir/src/Player/player.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tock_client.dir/src/Player/player.c.o -c /mnt/c/Users/adzer/CLionProjects/tock-client/src/Player/player.c

CMakeFiles/tock_client.dir/src/Player/player.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tock_client.dir/src/Player/player.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/adzer/CLionProjects/tock-client/src/Player/player.c > CMakeFiles/tock_client.dir/src/Player/player.c.i

CMakeFiles/tock_client.dir/src/Player/player.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tock_client.dir/src/Player/player.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/adzer/CLionProjects/tock-client/src/Player/player.c -o CMakeFiles/tock_client.dir/src/Player/player.c.s

CMakeFiles/tock_client.dir/src/board.c.o: CMakeFiles/tock_client.dir/flags.make
CMakeFiles/tock_client.dir/src/board.c.o: ../src/board.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/tock_client.dir/src/board.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tock_client.dir/src/board.c.o -c /mnt/c/Users/adzer/CLionProjects/tock-client/src/board.c

CMakeFiles/tock_client.dir/src/board.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tock_client.dir/src/board.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/adzer/CLionProjects/tock-client/src/board.c > CMakeFiles/tock_client.dir/src/board.c.i

CMakeFiles/tock_client.dir/src/board.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tock_client.dir/src/board.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/adzer/CLionProjects/tock-client/src/board.c -o CMakeFiles/tock_client.dir/src/board.c.s

CMakeFiles/tock_client.dir/src/parser.c.o: CMakeFiles/tock_client.dir/flags.make
CMakeFiles/tock_client.dir/src/parser.c.o: ../src/parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/tock_client.dir/src/parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tock_client.dir/src/parser.c.o -c /mnt/c/Users/adzer/CLionProjects/tock-client/src/parser.c

CMakeFiles/tock_client.dir/src/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tock_client.dir/src/parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/adzer/CLionProjects/tock-client/src/parser.c > CMakeFiles/tock_client.dir/src/parser.c.i

CMakeFiles/tock_client.dir/src/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tock_client.dir/src/parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/adzer/CLionProjects/tock-client/src/parser.c -o CMakeFiles/tock_client.dir/src/parser.c.s

CMakeFiles/tock_client.dir/src/Color.c.o: CMakeFiles/tock_client.dir/flags.make
CMakeFiles/tock_client.dir/src/Color.c.o: ../src/Color.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/tock_client.dir/src/Color.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tock_client.dir/src/Color.c.o -c /mnt/c/Users/adzer/CLionProjects/tock-client/src/Color.c

CMakeFiles/tock_client.dir/src/Color.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tock_client.dir/src/Color.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/adzer/CLionProjects/tock-client/src/Color.c > CMakeFiles/tock_client.dir/src/Color.c.i

CMakeFiles/tock_client.dir/src/Color.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tock_client.dir/src/Color.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/adzer/CLionProjects/tock-client/src/Color.c -o CMakeFiles/tock_client.dir/src/Color.c.s

# Object files for target tock_client
tock_client_OBJECTS = \
"CMakeFiles/tock_client.dir/src/mainClient.c.o" \
"CMakeFiles/tock_client.dir/src/game.c.o" \
"CMakeFiles/tock_client.dir/src/mainSDL.c.o" \
"CMakeFiles/tock_client.dir/src/linkedlist.c.o" \
"CMakeFiles/tock_client.dir/src/card.c.o" \
"CMakeFiles/tock_client.dir/src/gameRule.c.o" \
"CMakeFiles/tock_client.dir/src/Player/player.c.o" \
"CMakeFiles/tock_client.dir/src/board.c.o" \
"CMakeFiles/tock_client.dir/src/parser.c.o" \
"CMakeFiles/tock_client.dir/src/Color.c.o"

# External object files for target tock_client
tock_client_EXTERNAL_OBJECTS =

tock_client: CMakeFiles/tock_client.dir/src/mainClient.c.o
tock_client: CMakeFiles/tock_client.dir/src/game.c.o
tock_client: CMakeFiles/tock_client.dir/src/mainSDL.c.o
tock_client: CMakeFiles/tock_client.dir/src/linkedlist.c.o
tock_client: CMakeFiles/tock_client.dir/src/card.c.o
tock_client: CMakeFiles/tock_client.dir/src/gameRule.c.o
tock_client: CMakeFiles/tock_client.dir/src/Player/player.c.o
tock_client: CMakeFiles/tock_client.dir/src/board.c.o
tock_client: CMakeFiles/tock_client.dir/src/parser.c.o
tock_client: CMakeFiles/tock_client.dir/src/Color.c.o
tock_client: CMakeFiles/tock_client.dir/build.make
tock_client: CMakeFiles/tock_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable tock_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tock_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tock_client.dir/build: tock_client
.PHONY : CMakeFiles/tock_client.dir/build

CMakeFiles/tock_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tock_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tock_client.dir/clean

CMakeFiles/tock_client.dir/depend:
	cd /mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/adzer/CLionProjects/tock-client /mnt/c/Users/adzer/CLionProjects/tock-client /mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile /mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile /mnt/c/Users/adzer/CLionProjects/tock-client/cmake-build-wsl_profile/CMakeFiles/tock_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tock_client.dir/depend

