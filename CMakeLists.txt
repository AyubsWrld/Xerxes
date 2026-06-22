cmake_minimum_required(VERSION 3.16) 

project(
    Xerxes
    LANGUAGES CXX
    VERSION 0.1
)



# set(CMAKE_CXX_COMPILER /clang64/bin/clang++)
# set(CMAKE_C_COMPILER /clang64/bin/clang)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)


add_executable(xerxes src/main.cpp)
target_include_directories(xerxes PRIVATE ${CMAKE_SOURCE_DIR}/include)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/SDL3-3.4.10")
find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3-shared)
target_link_libraries(
    xerxes 
    PRIVATE
    SDL3::SDL3
)
target_include_directories(
    xerxes 
    PUBLIC
    SDL3::SDL3
)

# if(WIN32)
#     add_custom_command(
#         TARGET mygame POST_BUILD
#         COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:mygame>
#         VERBATIM
#     )
# endif()

