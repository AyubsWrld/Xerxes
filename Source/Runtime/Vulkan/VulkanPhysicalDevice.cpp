#include "Runtime/Vulkan/VulkanPhysicalDevice.hpp"
#include <vector>

namespace Runtime::Vulkan
{
    namespace Detail
    {
    }

    VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice vkDevice)
        : device{vkDevice}
    {
    }

    bool VulkanPhysicalDevice::DeviceSupportsCapability(
        VulkanPhysicalDevice physicalDevice,
        VkQueueFlagBits vkDeviceCapability) noexcept
    {
        uint32_t queuePropertiesCount;
        vkGetPhysicalDeviceQueueFamilyProperties2(
            physicalDevice.device, &queuePropertiesCount, nullptr);
        std::vector<VkQueueFamilyProperties2> queueFamilyProperties(
            queuePropertiesCount);
        vkGetPhysicalDeviceQueueFamilyProperties2(
            physicalDevice.device, &queuePropertiesCount,
            queueFamilyProperties.data());

        for(const auto& property : queueFamilyProperties)
            {
                if(property.queueFamilyProperties.queueFlags
                   & vkDeviceCapability)
                    return true;
            }
        return false;
    }

    bool VulkanPhysicalDevice::DeviceSupportsCapability(
        VkPhysicalDevice physicalDevice,
        VkQueueFlagBits vkDeviceCapability) noexcept
    {
        return VulkanPhysicalDevice::DeviceSupportsCapability(
            VulkanPhysicalDevice(physicalDevice), vkDeviceCapability);
    }
}
