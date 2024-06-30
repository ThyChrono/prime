#pragma once

#include <string>
#include <memory>

// Unsigned int types.

/** @brief Unsigned 8-bit integer */
using u8 = unsigned char;

/** @brief Unsigned 16-bit integer */
using u16 = unsigned short;

/** @brief Unsigned 32-bit integer */
using u32 = unsigned int;

/** @brief Unsigned 64-bit integer */
using u64 = unsigned long long;

// Signed int types.

/** @brief Signed 8-bit integer */
using i8 = signed char;

/** @brief Signed 16-bit integer */
using i16 = signed short;

/** @brief Signed 32-bit integer */
using i32 = signed int;

/** @brief Signed 64-bit integer */
using i64 = signed long long;

// Floating point types

/** @brief 32-bit floating point number */
using f32 = float;

/** @brief 64-bit floating point number */
using f64 = double;

// Boolean types

/** @brief 32-bit boolean type, used for APIs which require it */
using b32 = int;

/** @brief 8-bit boolean type */
using b8 = bool;

/** @brief string type */
using str = std::string;

// // Properly define static assertions.
// Ensure all types are of the correct size.

/** @brief Assert u8 to be 1 byte.*/
// static_assert(sizeof(uint8_t) == 1, "Expected u8 to be 1 byte.");
static_assert(sizeof(uint8_t) == 1, "Expected u8 to be 1 byte.");

// /** @brief Assert u16 to be 2 bytes.*/
static_assert(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");

/** @brief Assert u32 to be 4 bytes.*/
static_assert(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");

/** @brief Assert u64 to be 8 bytes.*/
static_assert(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");

/** @brief Assert i8 to be 1 byte.*/
static_assert(sizeof(i8) == 1, "Expected i8 to be 1 byte.");

/** @brief Assert i16 to be 2 bytes.*/
static_assert(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");

/** @brief Assert i32 to be 4 bytes.*/
static_assert(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");

/** @brief Assert i64 to be 8 bytes.*/
static_assert(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");

/** @brief Assert f32 to be 4 bytes.*/
static_assert(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");

/** @brief Assert f64 to be 8 bytes.*/
static_assert(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

/** @brief window handle.*/
using WindowHandle = void*;

/** @brief context handle.*/
using ContextHandle = void*;

// platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define PPLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define PPLATFORM_LINUX 1
#if defined(__ANDROID__)
#define PPLATFORM_ANDROID 1
#endif
#elif defined(__unix__)
// Catch anything not caught by the above.
#define PPLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#define PPLATFORM_POSIX 1
#elif __APPLE__
// Apple platforms
#define PPLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define PPLATFORM_IOS 1
#define PPLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define PPLATFORM_IOS 1
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif

/** @brief convert to string */
#define PSTR(x) #x

/** @brief get the line number */
#define PLINE __LINE__

/** @brief get function name */
#define PFUNC __FUNCTION__

/** @brief get file name */
#define PFILE __FILE__

/** @brief make inline */
#define PINLINE inline

/** @brief debug breakpoint */
#ifdef PPLATFORM_WINDOWS
#define PBREAK __debugbreak();
#else
#define PBREAK void() 0
#endif // PPLATFORM_WINDOWS

/** @brief unique pointer */
template <typename T>
using Scope = std::unique_ptr<T>;

/** @brief make a unique pointer */
template <typename TClass, typename... TArgs>
constexpr Scope<TClass> createScope(TArgs &&...args)
{
    return std::make_unique<TClass>(std::forward<TArgs>(args)...);
}

/** @brief shared pointer */
template <typename T>
using Ref = std::shared_ptr<T>;

/** @brief make a shared pointer */
template <typename TClass, typename... TArgs>
constexpr Ref<TClass> createRef(TArgs &&...args)
{
    return std::make_shared<TClass>(std::forward<TArgs>(args)...);
}
