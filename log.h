// log.h - Natural logarithm
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.

#pragma once
#include "dual.h"

// log (1 + x) = x - x^2/2 + x^3/3 - ...
// log (a0 + a1 x) = log a0 + log (1 + (a1/a0)x);
template<class T, size_t N>
inline dual::number<T,N> log(const dual::number<T,N>& X)
{
	dual::number<T,N> Y(log(X[0])), Xi(X);
	
	Xi -= X[0];
	Xi /= X[0];
	Y += Xi;

	for (size_t i = 2; i < N; ++i) {
		Xi *= -X;
		Y += Xi/static_cast<T>(i);
	}

	return Y;
}
