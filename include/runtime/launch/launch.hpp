#pragma once
#include <concepts>
#include <cstdint>

namespace runtime::launch
{
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
    };

    template <IEngineLoop Derived>
    class EngineLoop
    {
      public:
        [[nodiscard]]
        std::uint32_t pre_init()
        {
            static_cast<Derived&>(*this).pre_init();
        }

        [[nodiscard]]
        std::uint32_t init()
        {
            static_cast<Derived&>(*this).init();
        }

        [[nodiscard]]
        std::uint32_t post_init()
        {
            static_cast<Derived&>(*this).post_init();
        }

        void load_core_modules()
        {
            static_cast<Derived&>(*this).load_core_modules();
        }

        void load_preinit_modules()
        {
            static_cast<Derived&>(*this).load_core_modules();
        }

        void exit() { static_cast<Derived&>(*this).exit(); }
    };
}
