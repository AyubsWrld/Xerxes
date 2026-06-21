cmake_minimum_required(VERSION 3.16) 

project(
    Xerxes
    LANGUAGES C CXX
    VERSION 0.1
)

#set(GStreamer_DIR ${CMAKE_SOURCE_DIR}/libs/gstreamer-1.28.3/cmake)


set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

add_executable(xerxes src/main.cpp)
target_include_directories(xerxes PRIVATE ${CMAKE_SOURCE_DIR}/include)

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
# for finding the Find<package_name>.cmake files.
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
    find_package(GStreamer REQUIRED)
    find_package(GLIB2 REQUIRED)

    target_link_libraries(
        xerxes 
        PUBLIC 
        ${GStreamer_LIBRARIES}
        ${GLIB2_LIBRARIES}
    )
    target_include_directories(
        xerxes
        PUBLIC 
        ${GStreamer_INCLUDE_DIR}
        ${GLIB2_INCLUDE_DIR}
    )
else()
    message(STATUS "Cross-Compiling for Windows")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
    find_package(GLIB2 REQUIRED)
    if (NOT GLIB2_FOUND)
        message(WARNING "Found glib packages ${GLIB2_INCLUDE_DIR}")
    endif()
    target_link_libraries(
        xerxes 
        PUBLIC
        # /usr/mingw64/bin/libgstreamer-1.0-0.dll
        # /usr/mingw64/bin/libglib-2.0-0.dll
        # ${GStreamer_LIBRARIES}
        #${GLIB2_LIBRARIES}
        GLIB2::GLIB2
        GLIB2::GOBJECT
        GLIB2::GTHREAD2
        GLIB2::GIO
    )
endif()



