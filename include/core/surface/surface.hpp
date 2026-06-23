#pragma once 

// A collection of pixels used in software blitting.

class Surface 
{
    Surface() = default;
    ~Surface() = default;

    Surface(Surface&&) = delete;
    Surface(const Surface&) = delete;

    Surface& operator=(const Surface&) = delete;
    Surface& operator=(Surface&&) = delete;
};
