#pragma once
#include <vulkan/vulkan.h>
#include <vector>


namespace Runtime::Vulkan
{
    class VulkanCore
    {
        VkInstance instance{nullptr};
        std::vector<VkPhysicalDevice> physicalDevices;

    public:

        VulkanCore();
        ~VulkanCore();

        VulkanCore& operator=(VulkanCore&&) = delete;
        VulkanCore& operator=(const VulkanCore&) = delete;

        VulkanCore(const VulkanCore&&) = delete;
        VulkanCore(VulkanCore&) = delete;

    private:

        [[nodiscard]]
        VkResult InitInstance(const char* pAppName) noexcept;

        [[nodiscard]]
        VkResult EnumerateDevices() noexcept;

        [[nodiscard]]
        bool QueueSupportsGraphics() noexcept;

        void DumpDevices();
    };
}
