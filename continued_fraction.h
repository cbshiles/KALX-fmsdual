// continued_fraction.h - Continued fractions.
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include "continuant.h"

namespace polynomial {

	// xn = b0 + a0/(b1 + a1/(b2 + ... /bn))
	template<class T, std::size_t N>
	struct continued_fraction {
		static T evaluate(const T* a, const T* b)
		{
			return b[0] + (*a)/continued_fraction<T,N-1>::evaluate(a + 1, b + 1);
		}
		static T evaluate(continuant<T>& A, continuant<T>& B)
		{
			T B0 = *B;

			return B0 + (*A)/continued_fraction<T,N-1>::evaluate(++A, ++B);
		}
	};
	template<class T>
	struct continued_fraction<T,0> {
		static T evaluate(const T* a, const T* b)
		{
			return *b;
		}
		static T evaluate(continuant<T>& A, continuant<T>& B)
		{
			return *B;
		}
	};

} // namespace polynomial
