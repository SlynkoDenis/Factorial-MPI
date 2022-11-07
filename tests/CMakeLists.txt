set(BINARY tests)

set(SOURCES main.cpp)

add_executable(${BINARY} ${SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

find_package(MPI REQUIRED)
find_library(${GMP_LIB} NAMES gmp libgmp REQUIRED)

target_link_libraries(${BINARY}
    PUBLIC
    gmp
    gmpxx
    MPI::MPI_CXX
    solver
    utils
    )
