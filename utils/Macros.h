#ifndef FACTORIAL_MPI_MACROS_H_
#define FACTORIAL_MPI_MACROS_H_

#include "Debug.h"

#ifdef DEBUG

#define UNLIKELY(expr) (__builtin_expect((expr) != 0, false))

#define ASSERT_FAIL(expr) utils::AssertionFail((expr), __FILE__, __LINE__, __FUNCTION__)
#define ASSERT(expr)            \
    if (UNLIKELY(!(expr))) {    \
        ASSERT_FAIL(#expr);     \
    }

#else

#define ASSERT(expr) static_cast<void>(0)

#endif


#define NO_COPY_CTOR(TypeName) \
    TypeName(const TypeName &) = delete;

#define NO_COPY_OPERATOR(TypeName) \
    TypeName &operator=(const TypeName &) = delete

#define NO_COPY_SEMANTIC(TypeName) \
    NO_COPY_CTOR(TypeName)         \
    NO_COPY_OPERATOR(TypeName)

#define NO_MOVE_CTOR(TypeName) \
    TypeName(TypeName &&) = delete;

#define NO_MOVE_OPERATOR(TypeName) \
    TypeName &operator=(TypeName &&) = delete

#define NO_MOVE_SEMANTIC(TypeName) \
    NO_MOVE_CTOR(TypeName)         \
    NO_MOVE_OPERATOR(TypeName)

#endif // FACTORIAL_MPI_MACROS_H_
