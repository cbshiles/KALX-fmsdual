// exp.h - exponential function
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include "dual.h"

// exp(aJ^k)
template<class T, size_t N>
inline dual::number<T,N> expak(T a, size_t k)
{
	dual::number<T,N> e(1);

	T ak(1); // a^k/k!
	for (size_t i = 1; k*i < N; ++i) {
		ak *= a/i;
		e[k*i] = ak;
	}

	return e;
}

// exp(x) = 1 + x + x^2/2! + ...
// exp(a0 + a1 J + a2 J^2 + ... ) = exp(a0) exp(a1 J) exp(a2 J^2) ...
template<class T, size_t N>
inline dual::number<T,N> exp(const dual::number<T,N>& X)
{
	dual::number<T,N> Y(exp(X[0]));

	for (size_t k = 1; k < N; ++k) {
		Y *= expak<T,N>(X[k], k);
	}

	return Y;
}

/*
// exp(a J^k) = I + aJ^k + a^2J^2k/2!
template<class T, std::size_t N>
inline dual::number<T,N> expak(const T& a, std::size_t k)
{
	dual::number<T,N> eak(1., 0.);

	double f = 1;
	for (size_t i = 1; i/k < N; ++i) {
		f *= a/i;
		eak += f*dual::number<T,N>(i*k);
	}

	return eak;
}

// exp(a0 I + a1 J + a2 J^2 + ...)
template<class T, std::size_t N>
inline dual::number<T,N> exp(const dual::number<T,N>& a)
{
	dual::number<T,N> e;

	e = dual::number<T,N>(::exp(a[0]), 0);
	for (std::size_t i = 1; i < N; ++i) {
		if (a[i])
			e *= expak<T,N>(a[i], i);
	}

	return e;
}
*/

#if 0
/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*/


//double polevl(), p1evl(), floor(), ldexp();
//int isnan(), isfinite();
#ifdef INFINITIES
extern double INFINITY;
#endif

template<class T>
inline T exp(T x)
{
static double LOGE2  =  6.93147180559945309417E-1;    /* log(2) */
static double LOG2E  =  1.4426950408889634073599;     /* 1/log(2) */
static double MAXLOG =  7.08396418532264106224E2;     /* log 2**1022 */
static double MINLOG = -7.08396418532264106224E2;     /* log 2**-1022 */
static double MAXNUM =  1.79769313486231570815E308;    /* 2**1024*(1-MACHEP) */

static double P[] = {
 1.26177193074810590878E-4,
 3.02994407707441961300E-2,
 9.99999999999999999910E-1,
};
static double Q[] = {
 3.00198505138664455042E-6,
 2.52448340349684104192E-3,
 2.27265548208155028766E-1,
 2.00000000000000000009E0,
};
static double C1 = 6.93145751953125E-1;
static double C2 = 1.42860682030941723212E-6;

T px, xx;
int n;

#ifdef NANS
if( isnan(x) )
	return(x);
#endif
if( x > MAXLOG)
	{
#ifdef INFINITIES
	return( INFINITY );
#else
//	mtherr( "exp", OVERFLOW );
	return( MAXNUM );
#endif
	}

if( x < MINLOG )
	{
#ifndef INFINITIES
//	mtherr( "exp", UNDERFLOW );
#endif
	return(0.0);
	}

/* Express e**x = e**g 2**n
 *   = e**g e**( n loge(2) )
 *   = e**( g + n loge(2) )
 */
px = floor(x/M_LOGE2 + 0.5); /* floor() truncates toward -infinity. */
n = px;
x -= px * C1;
x -= px * C2;

/* rational approximation for exponential
 * of the fractional part:
 * e**x = 1 + 2x P(x**2)/( Q(x**2) - P(x**2) )
 */
xx = x * x;
px = x * polynomial::horner(3, P, xx);
x =  px/( polynomial::horner(4, Q, xx) - px );
x = 1.0 + 2.0 * x;

/* multiply by power of 2 */
x = ldexp( x, n );
return x;
}
#endif

