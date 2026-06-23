#pragma once
#include <print>

#ifndef VULKAN_SUPPORTS_GEOMETRY_SHADERS
#define VULKAN_SUPPORTS_GEOMETRY_SHADERS PLATFORM_SUPPORTS_GEOMETRY_SHADERS
#endif

// This defines controls shader generation (so will cause a format rebuild)
// be careful wrt cooker/target platform not matching define-wise!!!
// ONLY used for debugging binding table/descriptor set bugs/mismatches.
#define VULKAN_ENABLE_BINDING_DEBUG_NAMES 0

#define CHECK_VK_RESULT(X, MSG)                                               \
    static_assert(std::is_same_v<decltype(X), VkResult>,                      \
                  "Expression requires Vk");                                  \
    do                                                                        \
        {                                                                     \
            if(X != VK_SUCCESS)                                               \
                std::print("{:s}: Result of routine failed: {:s}",            \
                           __FUNCTION__, MSG);                                \
        }                                                                     \
    while(0)

#if defined(_WIN32)
#define SURFACE_NAME "VH_KHR_win32_surface"
#elif defined(__APPLE__)
#define SURFACE_NAME "VH_KHR_macos_surface"
#elif defined(__linux__)
#define SURFACE_NAME "VH_KHR_xcb_surface"
#endif

namespace ShaderStage
{
    // There should be one value for each value in EShaderFrequency.
    // These values are meant to be used as indices in contexts where values
    // for different bind points can overlap (Graphics/Compute/RayTracing) like
    // shader arrays in pipeline states or UB binding indices for Graphics
    // (Vertex==0, Pixel==1) that can overlap with Compute (Compute==0).
    // IMPORTANT: Adjusting these requires a full shader rebuild (ie modify the
    // GUID in VulkanCommon.usf)
    enum EStage
    {
        Vertex = 0,
        Pixel = 1,
        Geometry = 2,
        Mesh = 3,
        Task = 4,

        NumGraphicsStages = 5,

        RayGen = 0,
        RayMiss = 1,
        RayHitGroup = 2,
        RayCallable = 3,

        NumRayTracingStages = 4,

        Compute = 0,

        NumComputeStages = 1,

        MaxNumStages = 6, // work with even count to simplify bindless
                          // alignment requirements

        Invalid = -1,
    };
}
