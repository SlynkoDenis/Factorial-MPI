#include "Factorial.h"
#include <iostream>
#include "Utils.h"


int main(int argc, char **argv) {
    auto number = utils::GetInputNumber(argc, argv);
    if (!number) {
        return 1;
    }

    try {
        mpi_factorial::MPIFactorial calculator(&argc, &argv);
        auto fact = calculator.ComputeFactorial(number.value());
        if (fact) {
            auto expected = calculator.FactorialOneProcess(number.value());
            if (fact.value() != expected) {
                std::cerr << "Incorrect result for " << number.value() << "! : expected "\
                          << expected << ", got " << fact.value() << std::endl;
                return 1;
            }
        }
    } catch (utils::MPIException &exc) {
        return 1;
    }
    return 0;
}
