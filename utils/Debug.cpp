#include "Debug.h"


namespace utils {
void AssertionFail(const char *expr, const char *file, unsigned line, const char *function) {
    std::cerr << "ASSERTION FAILED: " << expr << std::endl;
    std::cerr << "IN " << file << ":" << std::dec << line << ":" << function << std::endl;
    std::terminate();
}

void AssertionFail(std::string expr, const char *file, unsigned line, const char *function) {
    AssertionFail(expr.data(), file, line, function);
}
}   // namespace utils
