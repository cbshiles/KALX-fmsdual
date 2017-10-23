// number.h - dual numbers
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include <cmath>
#include <algorithm>
#include <array>
#include <functional>
#pragma warning(push)
#pragma warning(disable: 4244) // 'argument' : conversion from 'double' to 'float', possible loss of data
#include <numeric>
#pragma warning(pop)

	
namespace dual {

/* compile time factorial
template<size_t val>
struct factorial { 
	enum {value = val*factorial<val-1>::value}; 
};
template<> struct factorial<0>{ 
	enum {value = 1};
};
*/
	// Dual numbers represented as first row of diagonal matrix.
	// E.g. d0 I + d1 J + d2 J^2 = [ d0 d1 d2] ~ {d0, d1, d2}
	//                             [  0 d0 d1]
	//                             [  0  0 d0]
	template<class T, std::size_t N>
	class number : public std::array<T,N> {
	public:
		//
		// Constructors
		//

		// 0 I
		number()
		{
			fill(0);
		}
		// d I
		explicit number(T d)
		{
			fill(0);
			operator[](0) = d;
		}
		// d I
/*		explicit number(int d)
		{
			fill(0);
			operator[](0) = (T)d;
		}
*/		// d0 I + d1 J
		number(const T& d0, const T& d1)
		{
			fill(0);
			operator[](0) = d0;
			if (size() > 1)
				operator[](1) = d1;
		}
		// d0 I + d1 J + ... + d[n-1] J^(n-1)
		number(const T* d, std::size_t n = 0)
		{
			std::copy(d, d + std::min(n, N), begin());
		}
		number(const number& d)
			: std::array<T,N>(d)
		{
		}
		number(const std::array<T,N>& d)
			: std::array<T,N>(d)
		{ }

		// d*J^k
		number& diagonal(std::size_t k, T d = 1)
		{
			fill(0);
			if (size() > k)
				operator[](k) = d;

			return *this;
		}

		//
		// Initializers
		//

		number& operator=(const std::array<T,N>& d)
		{
			std::array<T,N>::operator=(d);

			return *this;
		}
		// dI
		number& operator=(T d)
		{
			fill(0);
			operator[](0) = d;

			return *this;
		}

		~number()
		{ }

		operator std::array<T,N>()
		{
			return *this;
		}

		// == dI
		bool is_scalar() const
		{
			return std::find_if(begin() + 1, end(), [](T x) { return x != 0; }) == end();
		}

		static inline size_t factorial(size_t i)
		{
			return (i == 0 || i == 1) ? 1 : i*factorial(i - 1);
		}

		// i! d_[i] is the i-th derivative
		T derivative(std::size_t i) const
		{
			return factorial(i)*operator[](i);
		}
		// alias for derivative
		T _(std::size_t i) const
		{
			return derivative(i);
		}
		//
		// Relational operators
		//

		bool operator==(const number& d) const
		{
			return static_cast<std::array<T,N>>(*this) == static_cast<std::array<T,N>>(d);
		}
		bool operator==(double d) const
		{
			return operator[](0) == d;
		}
		bool operator==(float d) const
		{
			return operator[](0) == (T)d;
		}
		bool operator==(int d) const
		{
			return operator[](0) == d;
		}

		bool operator<(const number& d) const
		{
			return static_cast<std::array<T,N>>(*this) < static_cast<std::array<T,N>>(d);
		}
		bool operator<(double d) const
		{
			return operator[](0) < d;
		}
		bool operator<(float d) const
		{
			return operator[](0) < d;
		}
		bool operator<(int d) const
		{
			return operator[](0) < d;
		}

		//
		// Arithmetic operators
		//

		number& operator+=(const number& d)
		{
			std::transform(begin(), end(), d.begin(), begin(), std::plus<T>());

			return *this;
		}
		number& operator+=(double d)
		{
			operator[](0) += (T)d;

			return *this;
		}
		number& operator+=(float d)
		{
			operator[](0) += d;

			return *this;
		}
		number& operator+=(int d)
		{
			operator[](0) += d;

			return *this;
		}

		// unary minus
		number& operator-()
		{
			std::transform(begin(), end(), begin(), [](T x) { return -x; });

			return *this;
		}

		number& operator-=(const number& d)
		{
			std::transform(begin(), end(), d.begin(), begin(), std::minus<T>());

			return *this;
		}
		number& operator-=(double d)
		{
			operator[](0) -= (T)d;

			return *this;
		}
		number& operator-=(float d)
		{
			operator[](0) -= d;

			return *this;
		}
		number& operator-=(int d)
		{
			operator[](0) -= d;

			return *this;
		}

		// (a0 I + a1 J + a2 J^2 + ...)*(b0 I + b1 J + b2 J^2 + ...)
		// = a0 b0 I + (a1 b0 + a0 b1) J + (a2 b0 + a1 b1 + a0 b2) J^2
		number& operator*=(const number& b)
		{
			if (this != &b) {
				for (std::size_t i = N; i != 0; --i) {
					operator[](i - 1) *= b[0];
					for (std::size_t j = 1; j < i; ++j)
						operator[](i - 1) += operator[](i - 1 - j)*b[j];
				}
			}
			else { 
				// a^2
				number a_(*this);

				for (size_t k = 0; k < N; ++k) {
					operator[](k) = 0;
					for (size_t i = 0; i <= k; ++i)
						operator[](k) += a_[i]*a_[k - i];
				}
			}

			return *this;
		}
		number& mul_eq(const number& b)
		{
			for (size_t k = size() - 1; k != ~0; --k) {
				operator[](k) *= b[0];
				for (size_t i = 1; i < k; ++i)
					operator[](k) += operator[](i)*b[k - i]; //wrong!!!
			}

			return *this;
		}
		// scalar multiplication
		template<class U>
		number& mul_eq(U u)
		{
			std::transform(begin(), end(), begin(), [u](T x) { return x*u; });

			return *this;
		}
		number& operator*=(double d)
		{
			return mul_eq<double>(d);
		}
		number& operator*=(float d)
		{
			return mul_eq<float>(d);
		}
		number& operator*=(int d)
		{
			return mul_eq<int>(d);
		}

		number& operator/=(const number& b)
		{
			if (this != &b) {
				operator[](0) /= b[0];
				for (std::size_t i = 1; i < N; ++i) {
					for (std::size_t j = 0; j < i; ++j)
						operator[](i) -= operator[](j) * b[i - j];
					operator[](i) /= b[0];
				}
			}
			else {
				number a_(*this);
				a_ /= b;
				swap(a_);
			}

			return *this;
		}
		// (a0 I + a1 J + a2 J^2 + ...)^-1 = 1/a0 I - a1 b0/a0 J - (a1 b1 + a2 b0)/a0 J^2 + ... 
		number& invert(void)
		{
			number i(1);
			swap(i);
			
			return operator/=(i);
		}
		template<class U>
		number& div_eq(U u)
		{
			std::transform(begin(), end(), begin(), [u](T x) { return x/u; });

			return *this;
		}
		number& operator/=(double d)
		{
			return div_eq<double>(d);
		}
		number& operator/=(float d)
		{
			return div_eq<float>(d);
		}
		number& operator/=(int d)
		{
			return div_eq<int>(d);
		}

		//
		// Noninvasive math functions
		//

		// L^p norm of first row as a vector.
		T norm(T p) const
		{
			T result;

			if (p == 0)
				result = N;

			else if (p == 1)
				result = std::accumulate(begin(), end(), static_cast<T>(0), 
					[](T x, T y) { return x + ::fabs(y); });

			else if (p == std::numeric_limits<T>::infinity())
				result = std::accumulate(begin(), end(), -std::numeric_limits<T>::max(), 
					[](T x, T y) { return (std::max)(x, ::fabs(y)); });

			else
				result = ::pow(std::accumulate(begin(), end(), static_cast<T>(0), 
					[p](T x, T y) { return x + ::pow(::fabs(y), p); }), 1/p);
			

			return result;
		}

		//
		// Invasive math functions
		//

		// multiply by 2^e
		number& pow2(int e)
		{
			int e_;
			T xi;

			// scale by 2^e
			for (std::size_t i = 0; i < N; ++i) {
				xi = frexp(operator[](i), &e_);
				operator[](i) = ::ldexp(xi, e_ + e);
			}

			return *this;
		}

	};
} // namespace dual

// this can't possibly be necessary!!!
namespace std {
template<class _Ty,
	size_t _Size>
	struct tuple_size<dual::number<_Ty, _Size> >
	{	// struct to determine number of elements in array
	static const int value = _Size;
	};

template<size_t _Idx,
	class _Ty,
	size_t _Size>
	struct tuple_element<_Idx, dual::number<_Ty, _Size> >
	{	// struct to determine type of element _Idx in array
	typedef _Ty type;
	};
} // namespace std
/*
template<class T, size_t N>
struct pow {
//	static dual::number<T,N>&& *=
	static dual::number<T,N> operator()(const dual::number<T,N>& x, int n);
};
*/