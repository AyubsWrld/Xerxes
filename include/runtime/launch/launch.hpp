#pragma once
#include <concepts>
#include <cstdint>
#include <type_traits>

namespace Runtime::Launch
{
    namespace Detail
    {
        // little trick picked up from Klaus Iglberger: https://www.sandordargo.com/blog/2024/12/04/crtp-vs-concepts#the-crtp-solution
        class EngineLoopTag{};
    }
    struct PreInitContext
    {
        void cleanup();
    };

    template <typename T>
    concept IEngineLoop = requires(T t, std::uint32_t argc, char* argv[]) {
        { t.pre_init(argc, argv) } -> std::convertible_to<std::uint32_t>;
        { t.init() } -> std::convertible_to<std::uint32_t>;
        { t.post_init() } -> std::convertible_to<std::uint32_t>;
        { t.load_core_modules() } -> std::convertible_to<bool>;
        { t.load_preinit_modules() };
        { t.exit() };
    } && std::is_base_of_v<Detail::EngineLoopTag, T>;
}
