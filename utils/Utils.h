#ifndef FACTORIAL_MPI_UTILS_H_
#define FACTORIAL_MPI_UTILS_H_

#include <gmpxx.h>
#include "Macros.h"
#include <optional>
#include <stdexcept>
#include <vector>


namespace utils {
class MPIException : public std::runtime_error {
public:
    explicit MPIException(const std::string &description)
        : std::runtime_error(description) {}
    explicit MPIException(const char *description)
        : std::runtime_error(description) {}
    explicit MPIException(int errorCode)
        : MPIException(std::to_string(errorCode)) {}
};

std::optional<int> GetInputNumber(int argc, char **argv);

bool InputOptionExists(int argc, char **argv, std::string option);

void DumpNumberInFile(mpz_class number, std::string filename);
void DumpNumberInFile(mpz_class number, const char *filename);

void reportMPIError(int errorCode);

void exceptIfMPIError(int errorCode);

std::vector<char> mpzRawRepresentation(mpz_class value);
}   // namespace utils

#endif // FACTORIAL_MPI_UTILS_H_
