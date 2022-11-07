#include <chrono>
#include "Factorial.h"
#include <iostream>
#include "Utils.h"


namespace {
std::string GetDumpFileName(std::optional<int> number) {
    return std::to_string(number.value()) + "_fact.dat";
}

const char *TO_FILE_OPTION = "--to-file";
}   // anonymous namespace


int main(int argc, char **argv) {
    auto number = utils::GetInputNumber(argc, argv);
    if (!number) {
        return 1;
    }

    try {
        auto begin = std::chrono::steady_clock::now();

        mpi_factorial::MPIFactorial calculator(&argc, &argv);
        auto fact = calculator.ComputeFactorial(number.value());
        // print only from the root process, as only it has the accumulated result
        if (fact) {
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - begin).count();

            if (utils::InputOptionExists(argc, argv, TO_FILE_OPTION)) {
                utils::DumpNumberInFile(fact.value(), GetDumpFileName(number));
            } else {
                std::cout << number.value() << "! = " << fact.value() << std::endl;
            }
            std::cout << "Elapsed " << elapsed << " ms" << std::endl;
        }
    } catch (utils::MPIException &exc) {
        return 1;
    }
    return 0;
}
