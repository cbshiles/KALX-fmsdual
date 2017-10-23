// horner.h - Polynomial evaluation using the Horner method.
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
// Note: this is independent of dual numbers.
#pragma once
#include "polynomial.h"

namespace polynomial {

	// no partial specialization for functions
	template<std::size_t N>
	struct horner_struct {
		// p[0] + p[1]*x + ...  = p[0] + x*(p[1] + ...)
		template<class T, class U>
		static T horner(const U* p, const T& x)
		{
			return p[0] + x*horner_struct<N - 1>::horner<T,U>(p + 1, x);
		}
		template<class T, class U>
		static T horner(continuant<U>& p, const T& x)
		{
			T p0 = *p; // evaluate before incrementing

			return p0 + x*horner_struct<N - 1>::horner<T,U>(++p, x);
		}
	};
	template<>
	struct horner_struct<1> {
		template<class T, class U>
		static T horner(const U* p, const T&)
		{
			return p[0] + T();
		}	
		template<class T, class U>
		static T horner(continuant<U>& p, const T& x)
		{
			return *p + T();
		}	
	};

	template<class T, class U, std::size_t N>
	inline T horner(const U* p, const T& x)
	{
		return horner_struct<N>::horner<T,U>(p, x);
	}
	template<class T, class U, std::size_t N>
	inline T horner(continuant<U>& p, const T& x)
	{
		return horner_struct<N>::horner<T,U>(p, x);
	}
	template<class P, class T>
	inline T horner(const P& p, const T& x)
	{
		return horner<T, dual::number_traits<P>::type, dual::number_traits<P>::size>(p.data(), x);
	}

	// size not known until runtime
	template<class T, class U>
	inline T horner(std::size_t n, const U* p, const T& x)
	{
		T result;

		result = 0;
		for (p = p + n; n--; )
			result = *--p + x*result;
		
		return result;
	}

} // namepsace polynomial
