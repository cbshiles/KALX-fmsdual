// continuant.h - term in a polynomial, rational function or continued fraction.
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once

namespace polynomial {

	// numerator or denominator of continued fraction
	template<class T>
	struct continuant {
		// prefix
		virtual continuant& operator++() = 0;
		virtual T operator*() = 0;
	};

} // namespace polynomial
