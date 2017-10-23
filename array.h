// array.h - compile time arrays
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
// T(n) = 2 T(1) T(n - 1) - T(n - 2), T(0) = 1, T(1) = x
// Note: this is independent of dual numbers.
#pragma once
#include <algorithm>
#include <array>
#include <functional>

namespace polynomial {

	// a Op b
	template<class T, std::size_t N, class Op>
	struct array_op : public std::array<T,N> {
		array_op(const std::array<T,N>& a, const std::array<T,N>& b)
			: std::array<T,N>()
		{
			std::transform(a.begin(), a.end(), b.begin(), begin(), Op());
		}
		array_op(const T& a, const std::array<T,N>& b)
			: std::array<T,N>(b)
		{
			std::transform(begin(), end(), begin(), std::bind1st(Op(), a));
		}
		array_op(const std::array<T,N>& a, const T& b)
			: std::array<T,N>(a)
		{
			std::transform(begin(), end(), begin(), std::bind2nd(Op(), b));
		}
	};
	// extend array<T,N> to array<T,N+K>
	template<class T, std::size_t N, std::size_t K>
	struct array_extend : public std::array<T,N + K> {
		array_extend(const std::array<T,N>& a, bool shift = false)
			: std::array<T,N + K>()
		{
			if (shift) {
				std::copy(a.begin(), a.end(), begin() + K);
				std::fill(begin(), begin() + K, 0);
			}
			else {
				std::copy(a.begin(), a.end(), begin());
				std::fill(begin() + N, end(), 0);
			}
		}
	};

} // namepsace polynomial
