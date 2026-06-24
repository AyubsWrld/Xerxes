#include "Runtime/Vulkan/VulkanCore.hpp"
#include "Runtime/Vulkan/VulkanCommon.hpp"
#include "Runtime/Vulkan/VulkanPhysicalDevice.hpp"
#include "SDL3/SDL_vulkan.h"
#include <cstdint>
#include <iostream>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace Runtime::Vulkan
{
    VulkanCore::VulkanCore()
    {
        CHECK_VK_RESULT(InitInstance("Vulkan Tutorial"),
                        "Failed to create Vulkan Instance");
        CHECK_VK_RESULT(EnumerateDevices(), "Failed to enumerate devices");
        DumpDevices();

        
        if (QueueSupportsGraphics())
        {
            std::cout << "Queue Supports Graphics!!\n";
        }
    }

    VulkanCore::~VulkanCore() { vkDestroyInstance(instance, nullptr); }

    VkResult VulkanCore::InitInstance(const char* pAppName) noexcept
    {

        uint32_t instanceExtensionsCount{0};
        char const* const* instanceExtensions{
            SDL_Vulkan_GetInstanceExtensions(&instanceExtensionsCount)};

        const VkApplicationInfo appInfo
            = {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
               .pNext = NULL,
               .pApplicationName = pAppName,
               .apiVersion = VK_API_VERSION_1_3};

        const VkInstanceCreateInfo createInfo
            = {.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
               .pNext = NULL,
               .flags = 0,
               .pApplicationInfo = &appInfo,
               .enabledExtensionCount = instanceExtensionsCount,
               .ppEnabledExtensionNames = instanceExtensions};

        return vkCreateInstance(&createInfo, nullptr, &instance);
    }

    VkResult VulkanCore::EnumerateDevices() noexcept
    {
        std::uint32_t physicalDeviceCount{};
        CHECK_VK_RESULT(
            vkEnumeratePhysicalDevices(instance, &physicalDeviceCount,
                                       nullptr),
            "Failed while attemping to enumerate physical devices");

        std::vector<VkPhysicalDevice> devices(physicalDeviceCount);
        CHECK_VK_RESULT(
            vkEnumeratePhysicalDevices(instance, &physicalDeviceCount,
                                       devices.data()),
            "Failed while attemping to enumerate physical devices");

        physicalDevices = std::move(devices);
        return {};
    }

    void VulkanCore::DumpDevices()
    {
        if(std::ssize(physicalDevices) == 0)
            {
                printf("Could not do it rip\n");
            }
        VkPhysicalDeviceProperties2 deviceProperties{
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = NULL};
        vkGetPhysicalDeviceProperties2(physicalDevices[0], &deviceProperties);
        std::cout << "Selected device: "
                  << deviceProperties.properties.deviceName << "\n";
    }

    bool VulkanCore::QueueSupportsGraphics() noexcept
    {
        if(std::size(physicalDevices) == 0)
            return false;

        VulkanPhysicalDevice device { physicalDevices[0] } ;
        return VulkanPhysicalDevice::DeviceSupportsCapability(device, VK_QUEUE_GRAPHICS_BIT);
    };
}
