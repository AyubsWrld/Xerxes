#include <runtime/launch/launch.hpp>

namespace Runtime::Launch
{
    class WindowsLoop : public Detail::EngineLoopTag
    {

    public:
        [[nodiscard]]
        std::uint32_t pre_init(std::uint32_t argc, char* argv[]) 
        {
           return 0; 
        }

        [[nodiscard]]
        std::uint32_t init()
        {
            return 0;
        }

        [[nodiscard]]
        std::uint32_t post_init()
        {
            return 0;
        }

        void load_core_modules()
        {
            return;
        }

        void load_preinit_modules()
        {
            return;
        }

        void exit() { return; }
    };
}
