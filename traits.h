// traits.h - traits for dual numbers
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include <array>

namespace dual {
	template<class T>
	struct number_traits {
		typedef typename T::value_type type;
		static const std::size_t size = std::tuple_size<T>::value;
	};

	template<>
	struct number_traits<float> {
		typedef float type;
		static const std::size_t size = 1;
	};
	template<>
	struct number_traits<double> {
		typedef double type;
		static const std::size_t size = 1;
	};
	template<>
	struct number_traits<long double> {
		typedef long double type;
		static const std::size_t size = 1;
	};
}

#undef FMS_NUMERIC_LIMITS