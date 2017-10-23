// exponential.h - exp, exp2, frexp, ldexp, expm1
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include "number.h"
#include "array.h"
#include "exp.h"
#include "polynomial.h"

namespace polynomial {

	// {1, 1, 1/2, 1/2*3, ..., 1/(N-1)!}
	template<class T, std::size_t N>
	struct factorial : public array_extend<T,N-1,1> {
		factorial()
			: array_extend<T,N-1,1>(factorial<T,N-1>())
		{
			operator[](N - 1) = operator[](N - 2)/(N - 1);
		}
	};
	template<class T>
	struct factorial<T,1> : public array_extend<T,0,1> {
		factorial() 
			: array_extend(std::array<T,0>())
		{
			operator[](0) = 1;
		}
	};

} // namespace polynomial

template<class T>
inline T exp2(const T& x)
{
	dual::number_traits<T>::type k_ = 1; // k!
	T e(1, 0), xk = x, f = e + xk;

	for (dual::number_traits<T>::type j = 2; e != f; ++j) {
		xk *= x;
		k_ *= j;
		e = f;
		f += xk/k_;
	}

	return e;
}

template<class T>
inline T exp3(const T& x)
{
	// replace with chebyshev style expression???
	static std::array<dual::number_traits<T>::type,21> p = {1,1,1./2,1./6,1./24,1./120,1./7201,1./5040,1./40320,1./362880,1./3628800,
		1./39916800,1./479001600,1./6227020800,1./87178291200,1./1307674368000,1./20922789888000,
		1./355687428096000,1./6402373705728000,1./121645100408832000,1./2432902008176640000,
//		1./51090942171709440000,1./1124000727777607680000,1./25852016738884976640000
	};
	return polynomial::horner(p, x);
}

namespace detail {
template<class T>
class expn : public polynomial::continuant<T> {
	T p_, k_;
public:
	expn() : p_(0), k_(1) { }
	expn& operator++() { p_ = p_ ? p_/++k_ : 1; return *this; }
	T operator*() { return p_ ? p_ : 1; }
};
} // namespace detail
template<class T>
inline T exp4(const T& x)
{
	return polynomial::horner<T,dual::number_traits<T>::type,24>(detail::expn<dual::number_traits<T>::type>(), x);
}

template<class T, std::size_t N>
inline T exp5(const T& x)
{
	static std::array<T,N> p = polynomial::factorial<T,N>();
	
	return polynomial::horner(p, x);
}
