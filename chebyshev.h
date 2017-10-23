// chebyshev.h - compile time Chebyshev polynomials 
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
// T(n) = 2 T(1) T(n - 1) - T(n - 2), T(0) = 1, T(1) = x
// Note: this is independent of dual numbers.
#pragma once
#include "array.h"

namespace polynomial {

	template<class T, std::size_t N>
	struct chebyshev : public std::array<T,N + 1> { 
		chebyshev()
			: std::array<T,N + 1>(
				array_op<T,N + 1,std::minus<T>>(
					array_op<T,N + 1,std::multiplies<T>>(
						2
						, 
						array_extend<T,N,1>(chebyshev<T,N - 1>(),true)
					)
					,
					array_extend<T,N-1,2>(chebyshev<T,N-2>())
				)
			)
		{ }
		~chebyshev()
		{ }
	};
	template<class T>
	struct chebyshev<T,1> : public std::array<T,2> { 
		chebyshev() 
			: std::array<T,2>() // = x
		{
			operator[](0) = 0;
			operator[](1) = 1;
		}
	};
	template<class T>
	struct chebyshev<T,0> : public std::array<T,1> { 
		chebyshev() 
			: std::array<T,1>() // = 1
		{
			operator[](0) = 1;
		}
	};

} // namepsace polynomial
