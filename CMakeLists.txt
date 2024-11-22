# This is the project CMakeLists.txt file for the test subproject
cmake_minimum_required(VERSION 3.22)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# idf_build_set_property(DEPENDENCIES_LOCK dependencies.lock)

SET(BOARD "BOARD" CACHE STRING "BOARD_MODEL")

if(BOARD=qemu)
# options
message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}" "optio0n board")
elseif(BOARD=tdisplays3)
# options
message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}" "optio0n board")
elseif(BOARD=tdisplays3pro)
# option
message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}" "optio0n board")
else(execute_process("echo"))
# option
message("argument BOARD is required")
endif()


project(cocoa)

