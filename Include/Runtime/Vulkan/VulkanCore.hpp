#pragma once
#include <vulkan/vulkan.h>

namespace Runtime::Vulkan
{
    class VulkanCore
    {
        VkInstance instance { nullptr };

    public:

        VulkanCore();
        ~VulkanCore();

        VulkanCore& operator=(VulkanCore&&) = delete;
        VulkanCore& operator=(const VulkanCore&) = delete;

        VulkanCore(const VulkanCore&&) = delete;
        VulkanCore(VulkanCore&) = delete;

    private:
        void CreateInstance(const char* pAppName) noexcept; 
    };
}
