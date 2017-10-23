// limits.h - numeric_limits for dual numbers
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once
#include <limits>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#define FMS_NUMERIC_LIMITS(f) static dual::number<T,N> f() { return dual::number<T,N>(std::numeric_limits<T>::f()); }

namespace std {
	template<class T, std::size_t N>
	struct numeric_limits<dual::number<T,N>> {
		FMS_NUMERIC_LIMITS(min)
		FMS_NUMERIC_LIMITS(max)
		FMS_NUMERIC_LIMITS(lowest)
		FMS_NUMERIC_LIMITS(epsilon)
		FMS_NUMERIC_LIMITS(round_error)
		FMS_NUMERIC_LIMITS(denorm_min)
		FMS_NUMERIC_LIMITS(infinity)
		FMS_NUMERIC_LIMITS(quiet_NaN)
		FMS_NUMERIC_LIMITS(signaling_NaN)
	};
}

#undef FMS_NUMERIC_LIMITS