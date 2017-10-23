// norm.h - Lp norms based on first row of dual number
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include "number.h"

template<class T, std::size_t N>
inline T norm(const dual::number<T,N>& a, T p)
{
	return a.norm(p);
}

template<class T, std::size_t N>
inline T fabs(const dual::number<T,N>& a)
{
	return a.norm(2); // agree with complex for N = 2
}