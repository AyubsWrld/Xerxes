#pragma once
#include <vulkan/vulkan.h>

namespace Runtime::Vulkan
{
    namespace Detail
    {
    }

    class VulkanPhysicalDevice
    {

    public:
        VkPhysicalDevice device;

        explicit VulkanPhysicalDevice(VkPhysicalDevice device);

        ~VulkanPhysicalDevice() = default;

        [[nodiscard]]
        static bool DeviceSupportsCapability(VulkanPhysicalDevice physicalDevice,
                                 VkQueueFlagBits vkDeviceCapability) noexcept;

        [[nodiscard]]
        static bool DeviceSupportsCapability(VkPhysicalDevice physicalDevice,
                                 VkQueueFlagBits vkDeviceCapability) noexcept;
    };
}
