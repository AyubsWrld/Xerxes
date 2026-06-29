#pragma once 

#include <version>
#include <cstdint>

using U8 = std::uint8_t;
using U16 = std::uint16_t;
using U32 = std::uint32_t;
using U64 = std::uint64_t;

using I8 = std::int8_t;
using I16 = std::int16_t;
using I32 = std::int32_t;
using I64 = std::int64_t;

using F32 = float;
using F64 = double;


#if defined(__GNUC__) || defined(__clang__)
#define XERXES_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define XERXES_DEPRECATED __declspec(deprecated)
#else
#define XERXES_DEPRECATED
#endif

#if defined(_WIN32)
    #if defined(XERXES_SHARED_LIB)
        #define XERXES_API __declspec(dllexport)
    #else 
        #define XERXES_API __declspec(dllimport)
    #endif
#else // !defined(_WIN32)
    #if defined(XERXES_SHARED_LIB)
        #define XERXERXES_API __attribute__((visibility("default")))
    #else XERXERXES_API 
    #endif
#endif


#define XERXES_NOEXCEPT noexcept
#define XERXES_CONSTEXPR constexpr
#if defined(__clang__)
#define XERXES_FORCE_INLINE [[gnu::always_inline]] [[gnu::gnu_inline]] extern inline

#elif defined(__GNUC__)
#define XERXES_FORCE_INLINE [[gnu::always_inline]] inline

#elif defined(_MSC_VER)
#pragma warning(error: 4714)
#define XERXES_FORCE_INLINE __forceinline

#else
#error Unsupported compiler
#endif
