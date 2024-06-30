#pragma once

#include "defines.h"
#include "prime/maths/maths.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace prime::core
{
	class Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> s_handle;

	public:
		static void init();
		static void shutdown();

		static std::shared_ptr<spdlog::logger>& get() { return s_handle; }
	};
}

// types logging
// vec2
template <>
struct fmt::formatter<prime::maths::vec2> : fmt::formatter<std::string>
{
    auto format(prime::maths::vec2 vec, format_context& ctx) const -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "vec 2 ({0}, {1})", vec.x, vec.y);
    }
};

// vec3
template <>
struct fmt::formatter<prime::maths::vec3> : fmt::formatter<std::string>
{
    auto format(prime::maths::vec3 vec, format_context& ctx) const -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "vec 3 ({0}, {1}, {2})", vec.x, vec.y, vec.z);
    }
};

// vec4
template <>
struct fmt::formatter<prime::maths::vec4> : fmt::formatter<std::string>
{
    auto format(prime::maths::vec4 vec, format_context& ctx) const -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "vec 4 ({0}, {1}, {2}, {3})", vec.x, vec.y, vec.z, vec.w);
    }
};

#ifdef PCONFIG_DEBUG
#define PTRACE(...)         prime::core::Logger::get()->trace(__VA_ARGS__)
#define PDEBUG(...)         prime::core::Logger::get()->debug(__VA_ARGS__)
#define PINFO(...)          prime::core::Logger::get()->info(__VA_ARGS__)
#define PWARN(...)          prime::core::Logger::get()->warn(__VA_ARGS__)
#define PERROR(...)         prime::core::Logger::get()->error(__VA_ARGS__)
#else
#define PTRACE(...)         void()
#define PDEBUG(...)         void()
#define PINFO(...)          void()
#define PWARN(...)          void()
#define PERROR(...)         void()
#endif // PCONFIG_DEBUG
