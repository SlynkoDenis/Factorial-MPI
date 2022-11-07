#include "Factorial.h"
#include <iostream>
#include "Macros.h"
#include <mpi.h>
#include <sstream>
#include "Utils.h"


namespace mpi_factorial {
MPIFactorial::MPIFactorial(int *argc, char ***argv) {
    ASSERT((argc) && (argv));
    utils::exceptIfMPIError(MPI_Init(argc, argv));
}

MPIFactorial::~MPIFactorial() noexcept {
    int errorCode = MPI_Finalize();
    if (errorCode != MPI_SUCCESS) {
        utils::reportMPIError(errorCode);
    }
}

std::optional<mpz_class> MPIFactorial::ComputeFactorial(int number) {
    if (number < 0) {
        std::stringstream oss;
        oss << "unable to calculate N! where N == " << number;
        throw std::invalid_argument(oss.str());
    }

    int numProcesses = 0;
    utils::exceptIfMPIError(MPI_Comm_size(MPI_COMM_WORLD, &numProcesses));
    if (number <= numProcesses + 1 || numProcesses == 1) {
        return FactorialOneProcess(number);
    }

    int currentProcessId = 0;
    utils::exceptIfMPIError(MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessId));

    if (currentProcessId == ROOT_PROCESS_ID) {
        return rootProcessCalculation(numProcesses, number);
    }
    sideProcessCalculation(numProcesses, currentProcessId, number);
    return {};
}

mpz_class MPIFactorial::rootProcessCalculation(int numProcesses, int number) {
    ASSERT(number > numProcesses);

    size_t numSideProcesses = numProcesses - 1;
    std::vector<MPI_Request> requests(numSideProcesses);
    // received buffers' sizes to further allocate enough memory for results
    std::vector<unsigned int> rawDataSizes(numSideProcesses);
    // initiate non-blocking receive and only then do root's part of calculations
    for (size_t i = 0; i < numSideProcesses; ++i) {
        utils::exceptIfMPIError(
            MPI_Irecv(&rawDataSizes[i], 1, MPI_UNSIGNED, i + 1,
                      MESSAGE_TAG, MPI_COMM_WORLD, &requests[i]));
    }

    auto result = FactorialOneProcess(number / numProcesses);

    // must wait for sizes' reception
    utils::exceptIfMPIError(MPI_Waitall(
        numSideProcesses, requests.data(), MPI_STATUS_IGNORE));
    // receive calculated partial results
    std::vector<std::vector<char>> partialResultsRaw(numSideProcesses);
    for (size_t i = 0; i < numSideProcesses; ++i) {
        partialResultsRaw[i].resize(rawDataSizes[i]);
        utils::exceptIfMPIError(
            MPI_Irecv(partialResultsRaw[i].data(), rawDataSizes[i], MPI_CHAR, i + 1,
                      MESSAGE_TAG, MPI_COMM_WORLD, &requests[i]));
    }
    utils::exceptIfMPIError(MPI_Waitall(
        numSideProcesses, requests.data(), MPI_STATUSES_IGNORE));

    // accumulate results
    for (auto raw : partialResultsRaw) {
        result *= mpz_class(raw.data(), 10);
    }
    return result;
}

void MPIFactorial::sideProcessCalculation(int numProcesses, int processId, int number) {
    ASSERT((number > numProcesses) && (numProcesses > processId) && (processId > 0));

    // determine calculation borders
    int start = number / numProcesses * processId + 1;
    int end = 0;
    if (processId == numProcesses - 1) {
        end = number;
    } else {
        end = number / numProcesses * (processId + 1);
    }

    auto part = FactorialOneProcess(end, start);
    // convert result into string representation to pass via MPI_Isend
    auto raw = utils::mpzRawRepresentation(part);
    auto rawSize = raw.size();

    MPI_Request sizeRequest, dataRequest;
    // must firstly pass size of the buffer
    utils::exceptIfMPIError(
        MPI_Isend(&rawSize, 1, MPI_UNSIGNED, ROOT_PROCESS_ID,
                  MESSAGE_TAG, MPI_COMM_WORLD, &sizeRequest));
    utils::exceptIfMPIError(
        MPI_Isend(raw.data(), rawSize, MPI_CHAR, ROOT_PROCESS_ID,
                  MESSAGE_TAG, MPI_COMM_WORLD, &dataRequest));
    utils::exceptIfMPIError(MPI_Request_free(&sizeRequest));
    utils::exceptIfMPIError(MPI_Request_free(&dataRequest));
}

mpz_class MPIFactorial::FactorialOneProcess(mpz_class endNumber, mpz_class startNumber) {
    if (endNumber < 0) {
        std::stringstream oss;
        oss << "unable to calculate factorial up to negative number " << endNumber;
        throw std::invalid_argument(oss.str());
    }
    if (endNumber < startNumber) {
        std::stringstream oss;
        oss << "unable to calculate partial factorial from " << startNumber << " to " << endNumber;
        throw std::invalid_argument(oss.str());
    }

    mpz_class startIdx = startNumber + 1;
    for (auto i = startIdx; i <= endNumber; ++i) {
        startNumber *= i;
    }
    return startNumber;
}
}   // namespace mpi_factorial
