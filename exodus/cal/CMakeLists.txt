#
# Copyright 2023 The titan-search Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Configuration
# =============

include(GNUInstallDirs)

file(STRINGS "${PROJECT_SOURCE_DIR}/exodus/cal/calc_config.h" calc_version_defines
        REGEX "#define CALC_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${calc_version_defines})
    if(ver MATCHES "#define CALC_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(HS_CALC_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(HS_VERSION "0.1.0")
message(STATUS "Building hs-calc v${HS_VERSION}")

# We generate the kernel.json file, given the installation prefix and the executable name
configure_file (
    "${PROJECT_SOURCE_DIR}/share/jupyter/kernels/calc/kernel.json.in"
    "${PROJECT_SOURCE_DIR}/share/jupyter/kernels/calc/kernel.json"
)

# Flags
# =====

include(CheckCXXCompilerFlag)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
add_library(hs_calc SHARED calc_interpreter.cc calc_interpreter.h calc_config.h)


# hcalc is the target for the kernel executable
add_executable(hcalc calc_main.cc)
set_target_properties(hcalc PROPERTIES ENABLE_EXPORTS 1)
target_link_libraries(hcalc PRIVATE hs_calc)
target_compile_definitions(hcalc PRIVATE HS_CALC_HOME="${HS_CALC_PREFIX}")

#set(CMAKE_INSTALL_RPATH "$origin/../lib")

set_target_properties(hcalc PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

#Option for GTest
if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    set(BUILD_TESTS ON)
endif()

target_link_libraries(hs_calc PUBLIC dwarf::dwarf_STATIC)

set_target_properties(hs_calc PROPERTIES
                      COMPILE_DEFINITIONS "HS_CALC_EXPORTS"
                      PREFIX ""
                      VERSION ${HS_VERSION}
                      SOVERSION ${HS_VERSION}
OUTPUT_NAME "libhs_calc")


## Test ##
# take into account the CMakeList in test

OPTION(BUILD_TESTS "hs_calc test suite" OFF)
OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    set(BUILD_TESTS ON)
endif()


if(BUILD_TESTS)
    add_subdirectory(test)
endif()

# Installation
# ============

# Install hs_calc and hcalc
install(TARGETS hs_calc
        EXPORT ${PROJECT_NAME}-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hs_calc)

install(TARGETS hcalc
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# Configuration and data directories for jupyter
set(HS_JUPYTER_DATA_DIR "share/jupyter/kernels" CACHE STRING "Jupyter data directory")

# Install Jupyter kernelspecs
set(HS_CALCSPEC_DIR ${PROJECT_SOURCE_DIR}/share/jupyter/kernels/calc)
install(DIRECTORY ${HS_CALCSPEC_DIR}
        DESTINATION ${HS_JUPYTER_DATA_DIR}
        PATTERN "*.in" EXCLUDE)


# Extra path for installing Jupyter kernelspec
if (HS_EXTRA_JUPYTER_DATA_DIR)
    install(DIRECTORY ${HS_CALCSPEC_DIR}
            DESTINATION ${HS_EXTRA_JUPYTER_DATA_DIR}/kernels
            PATTERN "*.in" EXCLUDE)
endif(HS_EXTRA_JUPYTER_DATA_DIR)
