#include "Runtime/Vulkan/VulkanCore.hpp"
#include "Runtime/Vulkan/VulkanCommon.hpp"
#include <vulkan/vulkan_core.h>
#include <vector>


namespace Runtime::Vulkan
{
    VulkanCore::VulkanCore()
    {

    }

    VulkanCore::~VulkanCore()
    {
        vkDestroyInstance(instance, nullptr);
    }

    void VulkanCore::CreateInstance(const char* pAppName) noexcept
    {
        std::vector<const char*> Layers = 
        {
            "VK_LAYER_KHRONOS_validation"
        };

        std::vector<const char*> Extensions = 
        {
            VK_KHR_SURFACE_EXTENSION_NAME, 
            SURFACE_NAME
        };
    }
}
