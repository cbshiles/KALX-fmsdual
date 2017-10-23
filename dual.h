// dual.h - Dual numbers f(xI + J) = f(x)I + f'(x) J + f''(x)/2! J^2 + ...
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma once

#pragma warning(disable: 4244)

#ifndef ensure
#include <cassert>
#define ensure(x) assert(x)
#endif

#include "number.h"
#include "limits.h"
#include "operator.h"
#include "traits.h"

#include "exponential.h"
#include "math.h"
#include "power.h"
#include "special.h"
#include "trigonometric.h"

#pragma warning(default: 4244)
