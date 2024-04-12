

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif ()

if (NOT HERCULES_PATH)
    set(HERCULES_PATH "$ENV{HOME}/.hercules")
endif ()
message(STATUS "Found Hercules in ${HERCULES_PATH}")
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${HERCULES_PATH}/lib/hercules/" CACHE PATH "Use the existing Hercules installation" FORCE)
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} -pedantic -fvisibility-inlines-hidden -Wno-return-type-c-linkage -Wno-gnu-zero-variadic-macro-arguments -Wno-deprecated-declarations"
    )
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-type")
endif ()
set(CMAKE_CXX_FLAGS_DEBUG "-g")
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-limit-debug-info")
endif ()
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
include_directories(.)

find_package(LLVM REQUIRED CONFIG)
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
# Hercules Jupyter library
set(HERCULES_JUPYTER_FILES jupyter.h jupyter.cc)
add_library(hercules_jupyter SHARED ${HERCULES_JUPYTER_FILES})
target_include_directories(hercules_jupyter PRIVATE "${HERCULES_PATH}/include" ${LLVM_INCLUDE_DIRS})
add_dependencies(hercules_jupyter dwarf::dwarf_STATIC)
target_link_directories(hercules_jupyter PRIVATE "${HERCULES_PATH}/lib/hercules")
target_link_libraries(hercules_jupyter PRIVATE dwarf::dwarf_STATIC herculesc)

install(TARGETS hercules_jupyter DESTINATION .)

# Configuration and data directories for jupyter
set(HS_JUPYTER_DATA_DIR "share/jupyter/kernels" CACHE STRING "Jupyter data directory")

# Install Jupyter kernelspecs
set(HS_CALCSPEC_DIR ${PROJECT_SOURCE_DIR}/share/jupyter/kernels/hercules)
install(DIRECTORY ${HS_CALCSPEC_DIR}
        DESTINATION ${HS_JUPYTER_DATA_DIR}
        PATTERN "*.in" EXCLUDE)


# Extra path for installing Jupyter kernelspec
if (HS_EXTRA_JUPYTER_DATA_DIR)
    install(DIRECTORY ${HS_CALCSPEC_DIR}
            DESTINATION ${HS_EXTRA_JUPYTER_DATA_DIR}/kernels
            PATTERN "*.in" EXCLUDE)
endif(HS_EXTRA_JUPYTER_DATA_DIR)
