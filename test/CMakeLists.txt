# This is the project CMakeLists.txt file for the test subproject
cmake_minimum_required(VERSION 3.22)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
# idf_build_set_property(DEPENDENCIES_LOCK "../dependencies.lock")

# Include the components directory of the main application:
#
set(EXTRA_COMPONENT_DIRS "../components")

# Set the components to include the tests for.
# This can be overriden from CMake cache:
# - when invoking CMake directly: cmake -D TEST_COMPONENTS="xxxxx" ..
# - when using idf.py: idf.py -T xxxxx build
#
set(TEST_COMPONENTS 
    "blocks"
    "crypto"
    "helpers"
    "power"
    #"screen"
    "storage"
)



project(cocoa_tests)
