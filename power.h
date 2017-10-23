// power.h - pow, sqrt, cbrt, hypot, norm
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include "exp.h"
#include "log.h"

// pow(T, int)
template<class T, std::size_t N>
inline dual::number<T,N> pow(const dual::number<T,N>& a, int n)
{
	dual::number<T,N> c(1); // identity

	// not efficient
	if (n > 0) {
		while (n-- != 0)
			c *= a;
	}
	else if (n < 0) {
		while (n++ != 0)
			c /= a;
	}

	return c;
}

// pow(number<T>, T)
template<class T, std::size_t N>
inline dual::number<T,N> pow(const dual::number<T,N>& a, T p)
{
	return exp(p*log(a));
}
/*
// multiply by 2^e
template<class T, std::size_t N>
inline dual::number<T,N> pow2(const dual::number<T,N>& x, int e)
{
	return dual::number<T,N>(x).pow2(e);
}

template<class T, std::size_t N>
inline dual::number<T,N> ldexp(const dual::number<T,N>& x, int e)
{
	return dual::number<T,N>(x).pow2(e);
}


template<class T, std::size_t N>
inline dual::number<T,N> frexp(const dual::number<T,N>& x, int *e)
{
	dual::number<T,N> x_(x);

	frexp(x[0], e);
	x_.pow2(-*e);

	return x_;
}
*/