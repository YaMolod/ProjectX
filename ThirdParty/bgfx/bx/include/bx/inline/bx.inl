/*
 * Copyright 2010-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx/blob/master/LICENSE
 */

#ifndef BX_H_HEADER_GUARD
#	error "Must be included from bx/bx.h!"
#endif // BX_H_HEADER_GUARD

namespace bx
{
	// Reference(S):
	// - https://web.archive.org/web/20181115035420/http://cnicholson.net/2011/01/stupid-c-tricks-a-better-sizeof_array/
	//
	template<typename Ty, size_t Num>
	char(&CountOfRequireArrayArgumentT(const Ty(&)[Num]))[Num];

	template<bool B>
	struct isEnabled
	{
		// Template for avoiding MSVC: C4127: conditional expression is constant
		static constexpr bool value = B;
	};

	inline constexpr bool ignoreC4127(bool _x)
	{
		return _x;
	}

	template<class Ty>
	inline constexpr bool isTriviallyCopyable()
	{
		return __is_trivially_copyable(Ty);
	}

	template<class Ty>
	inline Ty* addressOf(Ty& _a)
	{
		return reinterpret_cast<Ty*>(
				&const_cast<char&>(
					reinterpret_cast<const volatile char&>(_a)
				)
			);
	}

	template<typename Ty>
	inline Ty* addressOf(void* _ptr, ptrdiff_t _offsetInBytes)
	{
		return (Ty*)( (uint8_t*)_ptr + _offsetInBytes);
	}

	template<class Ty>
	inline const Ty* addressOf(const Ty& _a)
	{
		return reinterpret_cast<const Ty*>(
				&const_cast<char&>(
					reinterpret_cast<const volatile char&>(_a)
				)
			);
	}

	template<typename Ty>
	inline void swap(Ty& _a, Ty& _b)
	{
		Ty tmp = _a; _a = _b; _b = tmp;
	}

	template<typename Ty>
	inline constexpr Ty min(const Ty& _a, const Ty& _b)
	{
		return _a < _b ? _a : _b;
	}

	template<typename Ty>
	inline constexpr Ty max(const Ty& _a, const Ty& _b)
	{
		return _a > _b ? _a : _b;
	}

	template<typename Ty, typename... Args>
	inline constexpr Ty min(const Ty& _a, const Ty& _b, const Args&... _args)
	{
		return min(min(_a, _b), _args...);
	}

	template<typename Ty, typename... Args>
	inline constexpr Ty max(const Ty& _a, const Ty& _b, const Args&... _args)
	{
		return max(max(_a, _b), _args...);
	}

	template<typename Ty, typename... Args>
	inline constexpr Ty mid(const Ty& _a, const Ty& _b, const Args&... _args)
	{
		return max(min(_a, _b), min(max(_a, _b), _args...) );
	}

	template<typename Ty>
	inline constexpr Ty clamp(const Ty& _a, const Ty& _min, const Ty& _max)
	{
		return max(min(_a, _max), _min);
	}

	template<typename Ty>
	inline constexpr bool isPowerOf2(Ty _a)
	{
		return _a && !(_a & (_a - 1) );
	}

} // namespace bx
