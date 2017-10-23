// normal.h - Standard Gaussian distribution
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include "log.h"
#include "sqrt.h"

template<class T>
inline T
normal_pdf(const T& x)
{
	return static_cast<T>(exp(-x*x/2)/M_SQRT2PI);
}

template<class T>
inline T
normal_cdf(const T& x)
{
	T s=x,t=0.,b=x,x2=x*x,i=1.;
	
	while(s!=t)
		s=(t=s)+(b*=x2/(i+=2.));

	return  static_cast<T>(.5+s*exp(-.5*x2-.91893853320467274178));
}

// Abramowitz and Stegun. Handbook of Mathematical functions 26.24 AS_P1
template<class T> 
inline T
normal_inv0(const T& p)
{
	return p > 0.5
		? static_cast<T>(sqrt(-(M_PI_2)*log(4*p*(1-p))))
		: static_cast<T>(-sqrt(-(M_PI_2)*log(4*p*(1-p))));
}


template<class T> 
inline T
normal_inv(const T& p)
{
	T x, y = 0.;

	if (p < 0.5)
		return -normal_inv(1 - p);

	for (x = normal_inv0(p); x != y; x = y) {
		y = x - (normal_cdf(x) - p)/normal_pdf(x); 
	}

	return x;
}

