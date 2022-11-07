#ifndef FACTORIAL_MPI_DEBUG_H_
#define FACTORIAL_MPI_DEBUG_H_

#include <iostream>


namespace utils {
void AssertionFail(const char *expr, const char *file, unsigned line, const char *function);
void AssertionFail(std::string expr, const char *file, unsigned line, const char *function);
}   // namespace utils

#endif // FACTORIAL_MPI_DEBUG_H_
