cmake_minimum_required(VERSION 3.22)
project(Factorial-MPI)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-DDEBUG)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BINARY mpi_factorial)

add_executable(${BINARY} main.cpp)
add_subdirectory(solver)
add_subdirectory(utils)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_subdirectory(tests)

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_tests.sh
         DESTINATION ${CMAKE_BINARY_DIR})
endif()

# find dependencies
find_package(MPI REQUIRED)
find_library(${GMP_LIB} NAMES gmp libgmp REQUIRED)

target_link_libraries(${BINARY} PUBLIC
    gmp
    gmpxx
    MPI::MPI_CXX
    solver
    utils
    )
