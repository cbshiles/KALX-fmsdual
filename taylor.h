// taylor.h - Polynomial evaluation using the Taylor series coefficients.
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
// Note: this is independent of dual numbers.
#pragma once
#include "polynomial.h"

namespace polynomial {

	// no partial specialization for functions
	template<std::size_t N>
	struct taylor_struct {
		// p[0] + p[1] x + p[2]/2! x + ...  + p[n]/n! x^n = p[0] + x (p[1] + x/2 (p[2] + x/3 (p[3] + ... + x/n p[n])))
		template<class T, class U>
		static T taylor(const U* p, const T& x)
		{
			return taylor_struct<N - 1>::taylor<T,U>(p, x/N)*;
		}
		template<class T, class U>
		static T taylor(continuant<U>& p, const T& x)
		{
			T p0 = *p; // evaluate before incrementing

			return p0 + x*taylor_struct<N - 1>::taylor<T,U>(++p, x);
		}
	};
	template<>
	struct taylor_struct<1> {
		template<class T, class U>
		static T taylor(const U* p, const T&)
		{
			return p[0] + T();
		}	
		template<class T, class U>
		static T taylor(continuant<U>& p, const T& x)
		{
			return *p + T();
		}	
	};

	template<class T, class U, std::size_t N>
	inline T taylor(const U* p, const T& x)
	{
		return taylor_struct<N>::taylor<T,U>(p, x);
	}
	template<class T, class U, std::size_t N>
	inline T taylor(continuant<U>& p, const T& x)
	{
		return taylor_struct<N>::taylor<T,U>(p, x);
	}
	template<class P, class T>
	inline T taylor(const P& p, const T& x)
	{
		return taylor<T, dual::number_traits<P>::type, dual::number_traits<P>::size>(p.data(), x);
	}

	// size not known until runtime
	template<class T, class U>
	inline T taylor(std::size_t n, const U* p, const T& x)
	{
		T result;

		result = 0;
		for (p = p + n; n--; )
			result = *--p + x*result;
		
		return result;
	}

} // namepsace polynomial
