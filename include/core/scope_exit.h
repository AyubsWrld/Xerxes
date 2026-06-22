#pragma once
#include <concepts>

namespace Core
{
    template <typename T>
    concept Callable = requires(T t) {
        { t() };
    };

    template <typename FuncType>
        requires Callable<FuncType>
    class TScopeGuard
    {
        FuncType _f;

        TScopeGuard(TScopeGuard&&) = delete;
        TScopeGuard(const TScopeGuard&) = delete;
        TScopeGuard& operator=(TScopeGuard&&) = delete;
        TScopeGuard& operator=(const TScopeGuard&) = delete;

    public:

        ~TScopeGuard() { _f(); }
        explicit TScopeGuard(FuncType InFunc) : _f(InFunc) {}
    };

    struct FScopeGuardSyntaxSupport
    {
        template <typename FuncType>
        TScopeGuard<FuncType> operator+(FuncType&& InFunc)
        {
            return TScopeGuard<FuncType>((FuncType&&)InFunc);
        }
    };

#define PRIVATE_SCOPE_EXIT_JOIN(A, B) PRIVATE_SCOPE_EXIT_JOIN_INNER(A, B)
#define PRIVATE_SCOPE_EXIT_JOIN_INNER(A, B) A##B

#define ON_SCOPE_EXIT                                                         \
    const auto PRIVATE_SCOPE_EXIT_JOIN(ScopeGuard_, __LINE__)                 \
        = FScopeGuardSyntaxSupport() + [&]() -> void
}
