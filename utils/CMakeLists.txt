set(LIB_NAME utils)
set(SOURCES
    Debug.cpp
    Utils.cpp
    )

add_library(${LIB_NAME} STATIC ${SOURCES})

target_sources(${LIB_NAME} PUBLIC
    Debug.h
    Macros.h
    Utils.h
    )

# find dependencies
find_package(MPI REQUIRED)
find_library(${GMP_LIB} NAMES gmp libgmp REQUIRED)

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LIB_NAME} PUBLIC
    gmp
    gmpxx
    MPI::MPI_CXX
    )
