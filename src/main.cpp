#include <concepts>
#include <core/scope_exit.h>
#include <iostream>
#include <print>
#include <runtime/launch/launch.hpp>

template <runtime::launch::IEngineLoop T>
void exit(const T& engine_loop)
{
    engine_loop.exit();
}

void bar() {}

template <typename T>
    requires Callable<T>
void foo(T t)
{
    t();
}

int main(int argc, char* argv[])
{

    ON_SCOPE_EXIT
    {
        std::cout << "Exiting\n";
    };

    std::cout << "here\n";
    return 0;
}
