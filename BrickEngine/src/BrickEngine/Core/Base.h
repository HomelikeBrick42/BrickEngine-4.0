#pragma once

#include "pch.h"

#include "BrickEngine/Core/Time.h"

#include "BrickEngine/Core/Log.h"

namespace BrickEngine {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#define BIT(x) (1 << x)

#define BRICKENGINE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef BRICKENGINE_DEBUG
	#define BRICKENGINE_CORE_ASSERT(x, ...) if (!(x)) { Log::CoreFatal(__VA_ARGS__); __debugbreak(); }
	#define BRICKENGINE_ASSERT(x, ...) if (!(x)) { Log::Fatal(__VA_ARGS__); __debugbreak(); }
#else
	#define BRICKENGINE_CORE_ASSERT(x, ...)
	#define BRICKENGINE_ASSERT(x, ...)
#endif
