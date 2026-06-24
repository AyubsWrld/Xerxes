cmake_minimum_required(VERSION 3.16) 

project(
    Xerxes
    LANGUAGES CXX
    VERSION 0.1
)

# set(CMAKE_CXX_COMPILER clang++)
# set(CMAKE_C_COMPILER clang)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)


add_executable(xerxes Source/main.cpp)
target_include_directories(xerxes PRIVATE ${CMAKE_SOURCE_DIR}/Include)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/SDL3-3.4.10")
find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3-shared)

target_sources(
    xerxes 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/Source/Core/Window/Window.cpp
    ${CMAKE_SOURCE_DIR}/Source/Runtime/Vulkan/VulkanCore.cpp
    ${CMAKE_SOURCE_DIR}/Source/Runtime/Vulkan/VulkanPhysicalDevice.cpp
)
target_link_libraries(
    xerxes 
    PRIVATE
    SDL3::SDL3
    glew32
    vulkan-1
)

target_include_directories(
    xerxes 
    PUBLIC
    SDL3::SDL3
    /mingw64/inlcude/vulkan
)


target_compile_options(
    xerxes 
    PRIVATE 
    -Wall 
    -Wextra 
    #-Werror
)
# if(WIN32)
#     add_custom_command(
#         TARGET mygame POST_BUILD
#         COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:mygame>
#         VERBATIM
#     )
# endif()

