// operator.h - dual number relational and arithmetical operators
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include "number.h"
#include <xutility>

//using namespace std::rel_ops;

template<class T, std::size_t N>
inline bool operator==(const dual::number<T,N>& a, const dual::number<T,N>& b)
{
	return a.operator==(b);
}
template<class T, std::size_t N>
inline bool operator==(const dual::number<T,N>& a, double b)
{
	return a.operator==(b);
}
template<class T, std::size_t N>
inline bool operator==(const dual::number<T,N>& a, float b)
{
	return a.operator==(b);
}
template<class T, std::size_t N>
inline bool operator==(const dual::number<T,N>& a, int b)
{
	return a.operator==(b);
}

template<class T, std::size_t N>
inline bool operator!=(const dual::number<T,N>& a, const dual::number<T,N>& b)
{
	return !a.operator==(b);
}
template<class T, std::size_t N>
inline bool operator!=(const dual::number<T,N>& a, double b)
{
	return !a.operator==(b);
}
template<class T, std::size_t N>
inline bool operator!=(const dual::number<T,N>& a, float b)
{
	return !a.operator==(b);
}
template<class T, std::size_t N>
inline bool operator!=(const dual::number<T,N>& a, int b)
{
	return !a.operator==(b);
}

template<class T, std::size_t N>
inline bool operator<(const dual::number<T,N>& a, const dual::number<T,N>& b)
{
	return a.operator<(b);
}
template<class T, std::size_t N>
inline bool operator<(const dual::number<T,N>& a, double b)
{
	return a.operator<(b);
}
template<class T, std::size_t N>
inline bool operator<(const dual::number<T,N>& a, float b)
{
	return a.operator<(b);
}
template<class T, std::size_t N>
inline bool operator<(const dual::number<T,N>& a, int b)
{
	return a.operator<(b);
}
// std::rel_ops does not do non-homogeneous comparison
template<class T, std::size_t N>
inline bool operator<=(const dual::number<T,N>& a, double b)
{
	return a.operator<(b) || a.operator==(b);
}
template<class T, std::size_t N>
inline bool operator<=(const dual::number<T,N>& a, float b)
{
	return a.operator<(b) || a.operator==(b);
}
template<class T, std::size_t N>
inline bool operator<=(const dual::number<T,N>& a, int b)
{
	return a.operator<(b) || a.operator==(b);
}

template<class T, std::size_t N>
inline bool operator<=(double a, const dual::number<T,N>& b)
{
	return !b.operator<(a);
}
template<class T, std::size_t N>
inline bool operator<=(float a, const dual::number<T,N>& b)
{
	return !b.operator<(a);
}
template<class T, std::size_t N>
inline bool operator<=(int a, const dual::number<T,N>& b)
{
	return !b.operator<(a);
}

template<class T, std::size_t N>
inline bool operator>(const dual::number<T,N>& a, const dual::number<T,N>& b)
{
	return !operator<=(a, b);
}
template<class T, std::size_t N>
inline bool operator>(const dual::number<T,N>& a, double b)
{
	return !operator<=(a, b);
}
template<class T, std::size_t N>
inline bool operator>(const dual::number<T,N>& a, float b)
{
	return !operator<=(a, b);
}
template<class T, std::size_t N>
inline bool operator>(const dual::number<T,N>& a, int b)
{
	return !operator<=(a, b);
}
template<class T, std::size_t N>
inline bool operator>=(const dual::number<T,N>& a, const dual::number<T,N>& b)
{
	return !operator<(a, b);
}
template<class T, std::size_t N>
inline bool operator>=(const dual::number<T,N>& a, double b)
{
	return !operator<(a, b);
}
template<class T, std::size_t N>
inline bool operator>=(const dual::number<T,N>& a, float b)
{
	return !operator<(a, b);
}
template<class T, std::size_t N>
inline bool operator>=(const dual::number<T,N>& a, int b)
{
	return !operator<(a, b);
}

template<class T, std::size_t N>
inline dual::number<T,N> operator+(const dual::number<T,N>& a, const dual::number<T,N>& b)
{
	dual::number<T,N> c(a);

	c += b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator+(const dual::number<T,N>& a, double b)
{
	dual::number<T,N> c(a);

	c += b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator+(const dual::number<T,N>& a, float b)
{
	dual::number<T,N> c(a);

	c += b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator+(const dual::number<T,N>& a, int b)
{
	dual::number<T,N> c(a);

	c += b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator+(double b, const dual::number<T,N>& a)
{
	dual::number<T,N> c(a);

	c += b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator+(float b, const dual::number<T,N>& a)
{
	dual::number<T,N> c(a);

	c += b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator+(int b, const dual::number<T,N>& a)
{
	dual::number<T,N> c(a);

	c += b;

	return c;
}

template<class T, std::size_t N>
inline dual::number<T,N> operator-(const dual::number<T,N>& a)
{
	return -dual::number<T,N>(a);
}

	template<class T, std::size_t N>
inline dual::number<T,N> operator-(const dual::number<T,N>& a, const dual::number<T,N>& b)
{
	dual::number<T,N> c(a);

	c -= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator-(const dual::number<T,N>& a, double b)
{
	dual::number<T,N> c(a);

	c -= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator-(const dual::number<T,N>& a, float b)
{
	dual::number<T,N> c(a);

	c -= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator-(const dual::number<T,N>& a, int b)
{
	dual::number<T,N> c(a);

	c -= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator-(double a , const dual::number<T,N>& b)
{
	dual::number<T,N> c(a, 0);

	c -= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator-(float a , const dual::number<T,N>& b)
{
	dual::number<T,N> c(a, 0);

	c -= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator-(int a , const dual::number<T,N>& b)
{
	dual::number<T,N> c(a, 0);

	c -= b;

	return c;
}

template<class T, std::size_t N>
inline dual::number<T,N> operator*(const dual::number<T,N>& a, const dual::number<T,N>& b)
{
	dual::number<T,N> c(a);

	c *= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator*(const dual::number<T,N>& a, double b)
{
	dual::number<T,N> c(a);

	c *= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator*(const dual::number<T,N>& a, float b)
{
	dual::number<T,N> c(a);

	c *= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator*(const dual::number<T,N>& a, int b)
{
	dual::number<T,N> c(a);

	c *= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator*(double b, const dual::number<T,N>& a)
{
	dual::number<T,N> c(a);

	c *= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator*(float b, const dual::number<T,N>& a)
{
	dual::number<T,N> c(a);

	c *= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator*(int b, const dual::number<T,N>& a)
{
	dual::number<T,N> c(a);

	c *= b;

	return c;
}

template<class T, std::size_t N>
inline dual::number<T,N> operator/(const dual::number<T,N>& a, const dual::number<T,N>& b)
{
	dual::number<T,N> c(a);

	c /= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator/(const dual::number<T,N>& a, double b)
{
	dual::number<T,N> c(a);

	c /= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator/(const dual::number<T,N>& a, float b)
{
	dual::number<T,N> c(a);

	c /= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator/(const dual::number<T,N>& a, int b)
{
	dual::number<T,N> c(a);

	c /= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator/(double a, const dual::number<T,N>& b)
{
	dual::number<T,N> c((T)a,0);

	c /= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator/(float, const dual::number<T,N>& b)
{
	dual::number<T,N> c(a,0);

	c /= b;

	return c;
}
template<class T, std::size_t N>
inline dual::number<T,N> operator/(int a, const dual::number<T,N>& b)
{
	dual::number<T,N> c(a,0);

	c /= b;

	return c;
}
