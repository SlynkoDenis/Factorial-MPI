#include <fstream>
#include "Macros.h"
#include <mpi.h>
#include <sstream>
#include "Utils.h"


namespace utils {
std::optional<int> GetInputNumber(int argc, char **argv) {
    ASSERT((argc > 1) && (argv));

    // check argument was provided
    if (argc < 2) {
        std::cerr << "Must provide integer number N as the only argument, instead got "\
                  << argc - 1 << " arguments" << std::endl;
        return {};
    }

    // convert argument to integer
    std::istringstream iss(argv[1]);
    int number = 0;
    if (!(iss >> number)) {
        std::cerr << "Must provide integer number N as the only argument, instead got: "\
                  << argv[1] << std::endl;
        return {};
    }
    return number;
}

bool InputOptionExists(int argc, char **argv, std::string option) {
    ASSERT((argc > 0) && (argv));

    auto iter = std::find(argv, argv + argc, option);
    return (iter != argv + argc);
}

void DumpNumberInFile(mpz_class number, std::string filename) {
    DumpNumberInFile(number, filename.c_str());
}

void DumpNumberInFile(mpz_class number, const char *filename) {
    std::fstream fs(filename, std::ostream::out | std::ostream::trunc);
    if (!fs.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
    } else {
        fs << number << std::endl;
    }
}

void reportMPIError(int errorCode) {
    std::string errorString(MPI_MAX_ERROR_STRING, '\0');
    int resultLen = 0;
    MPI_Error_string(errorCode, errorString.data(), &resultLen);
    std::cerr << "MPI error (code " << errorCode << "): " << errorString << std::endl;
}

void exceptIfMPIError(int errorCode) {
    if (errorCode != MPI_SUCCESS) {
        utils::reportMPIError(errorCode);
        throw MPIException(errorCode);
    }
}

std::vector<char> mpzRawRepresentation(mpz_class value) {
    auto asString = value.get_str();
    return std::vector<char>(asString.c_str(), asString.c_str() + asString.size() + 1);
}
}   // namespace utils
