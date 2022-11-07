set(LIB_NAME solver)
set(SOURCES Factorial.cpp)

add_library(${LIB_NAME} STATIC ${SOURCES})

target_sources(${LIB_NAME} PUBLIC Factorial.h)

include_directories(${CMAKE_SOURCE_DIR}/utils)

# find dependencies
find_package(MPI REQUIRED)
find_library(${GMP_LIB} NAMES gmp libgmp REQUIRED)

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LIB_NAME} PUBLIC
    gmp
    gmpxx
    MPI::MPI_CXX
    )
