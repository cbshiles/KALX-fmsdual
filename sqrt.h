// sqrt.h - square root
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1988, 2000 by Stephen L. Moshier
*/
#pragma once
#include "exp.h"
#include "log.h"

template<class T, size_t N>
inline dual::number<T,N> sqrt(const dual::number<T,N>& x)
{
	return exp(log(x)/2);
}

#if 0

#define SQRT2 1.41421356237309504880

template<class T>
inline T sqrt(T x)
{
int e;
T z, w;

if( x <= 0.0 )
	{
	if( x < 0.0 )
//		mtherr( "sqrt", DOMAIN );
	return( 0.0 );
	}
w = x;
/* separate exponent and significand */
z = frexp( x, &e );

/* Note, frexp and ldexp are used in order to
 * handle denormal numbers properly.
 */

/* approximate square root of number between 0.5 and 1
 * relative error of approximation = 7.47e-3
 */
x = 4.173075996388649989089E-1 + 5.9016206709064458299663E-1 * z;

/* adjust for odd powers of 2 */
if( (e & 1) != 0 )
	x *= SQRT2;

/* re-insert exponent */
x = ldexp( x, (e >> 1) );

/* Newton iterations: */
x = 0.5*(x + w/x);
x = 0.5*(x + w/x);
x = 0.5*(x + w/x);

return x;
}

#endif // 0