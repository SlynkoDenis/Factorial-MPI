#ifndef FACTORIAL_MPI_FACTORIAL_H_
#define FACTORIAL_MPI_FACTORIAL_H_

#include <gmpxx.h>
#include "Macros.h"
#include <optional>


namespace mpi_factorial {
class MPIFactorial final {
public:
    MPIFactorial(int *argc, char ***argv);
    NO_COPY_SEMANTIC(MPIFactorial);
    NO_MOVE_SEMANTIC(MPIFactorial);
    ~MPIFactorial() noexcept;

    std::optional<mpz_class> ComputeFactorial(int number);

public:
    static mpz_class FactorialOneProcess(int endNumber, int startNumber = 1);

    static constexpr int MESSAGE_TAG = 0;
    static constexpr int ROOT_PROCESS_ID = 0;

private:
    mpz_class rootProcessCalculation(int numProcesses, int number);
    void sideProcessCalculation(int numProcesses, int processId, int number);
};
}   // namespace mpi_factorial

#endif // FACTORIAL_MPI_FACTORIAL_H_
