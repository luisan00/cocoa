cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS "../components")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# components/helpers
add_compile_options(
    -Wno-sequence-point
    -Wno-unused-value
    )

project(NerdMiner_tests)