// gamma.h - Gamma and incomplete Gamma functions
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
/*
Gautschi, Walter 1979. A computational procedure for incomplete gamma functions.
ACM Trans. Math. Software, 5, 466-481

Armido R DiDonato and Alfred H Morris, Jr.. 1986. Computation of the incomplete gamma function ratios and their inverse. 
ACM Trans. Math. Softw. 12, 4 (December 1986), 377-393. DOI=10.1145/22721.23109 http://doi.acm.org/10.1145/22721.23109

incomplete gamma
gamma(a,x) = exp(-x) x^a sum 0 to infinity 1/gammma(a + 1 + k) x^k (good for x < a + 1)
           = exp(-x) x^a (1/x +/ (1 - a)/1 +/ 1/x +/ (2 - 1)/1 +/ 2/x +/...) (good for x > a + 1)
		   = exp(-x) x^a (1/x + 1 - a -/ 1.(1-a)/x + 3 - a -/ 2.(2 - a)/x + 5 - a -/...)

Note: gamma(z + a)/gamma(z + b) = z^(a - b) + O(1/z).
*/
#pragma once
#include <cmath>
#include "log.h"
#include "power.h"
#include "sqrt.h"

// log(Gamma(x))
template<class T>
inline T 
lgamma(const T& p)
{
  static T alr2pi = 0.918938533204673;
  static T r1[9] = {
    -2.66685511495, 
    -24.4387534237, 
    -21.9698958928, 
     11.1667541262, 
     3.13060547623, 
     0.607771387771, 
     11.9400905721, 
     31.4690115749, 
     15.2346874070 };
  static T r2[9] = {
    -78.3359299449, 
    -142.046296688, 
     137.519416416, 
     78.6994924154, 
     4.16438922228, 
     47.0668766060, 
     313.399215894, 
     263.505074721, 
     43.3400022514 };
  static T r3[9] = {
    -2.12159572323E+05, 
     2.30661510616E+05, 
     2.74647644705E+04, 
    -4.02621119975E+04, 
    -2.29660729780E+03, 
    -1.16328495004E+05, 
    -1.46025937511E+05, 
    -2.42357409629E+04, 
    -5.70691009324E+02 };
  static T r4[5] = {
     0.279195317918525, 
     0.4917317610505968, 
     0.0692910599291889, 
     3.350343815022304, 
     6.012459259764103 };
  T value;
  T x;
  T x1;
  T x2;
  T xlge = 510000.0;
  T xlgst = 1.0E+30;
  T y;

  x = p;
  value = 0.0;
//
//  Check the input.
//
  if ( xlgst <= x )
  {
    return std::numeric_limits<T>::infinity();
  }

  if ( x <= 0.0 )
  {
    return std::numeric_limits<T>::quiet_NaN();
  }

//
//  Calculation for 0 < X < 0.5 and 0.5 <= X < 1.5 combined.
//
  if ( x < 1.5 )
  {
    if ( x < 0.5 )
    {
      value = - log ( x );
      y = x + 1.0;
//
//  Test whether X < machine epsilon.
//
      if ( y == 1.0 )
      {
        return value;
      }
    }
    else
    {
      value = 0.0;
      y = x;
      x = ( x - 0.5 ) - 0.5;
    }

    value = value + x * (((( 
        r1[4]   * y 
      + r1[3] ) * y 
      + r1[2] ) * y 
      + r1[1] ) * y 
      + r1[0] ) / (((( 
                  y 
      + r1[8] ) * y 
      + r1[7] ) * y 
      + r1[6] ) * y 
      + r1[5] );

    return value;
  }
//
//  Calculation for 1.5 <= X < 4.0.
//
  if ( x < 4.0 )
  {
    y = ( x - 1.0 ) - 1.0;

    value = y * (((( 
        r2[4]   * x 
      + r2[3] ) * x 
      + r2[2] ) * x 
      + r2[1] ) * x 
      + r2[0] ) / (((( 
                  x 
      + r2[8] ) * x 
      + r2[7] ) * x 
      + r2[6] ) * x 
      + r2[5] );
  }
//
//  Calculation for 4.0 <= X < 12.0.
//
  else if ( x < 12.0 ) 
  {
    value = (((( 
        r3[4]   * x 
      + r3[3] ) * x 
      + r3[2] ) * x 
      + r3[1] ) * x 
      + r3[0] ) / (((( 
                  x 
      + r3[8] ) * x 
      + r3[7] ) * x 
      + r3[6] ) * x 
      + r3[5] );
  }
//
//  Calculation for 12.0 <= X.
//
  else
  {
    y = log ( x );
    value = x * ( y - 1.0 ) - 0.5 * y + alr2pi;

    if ( x <= xlge )
    {
      x1 = 1.0 / x;
      x2 = x1 * x1;

      value = value + x1 * ( ( 
             r4[2]   * 
        x2 + r4[1] ) * 
        x2 + r4[0] ) / ( ( 
        x2 + r4[4] ) * 
        x2 + r4[3] );
    }
  }

  return value;
}

// standard normal distribution
template<class T>
inline T 
alnorm(T x, bool upper)
{
  T a1 = 5.75885480458;
  T a2 = 2.62433121679;
  T a3 = 5.92885724438;
  T b1 = -29.8213557807;
  T b2 = 48.6959930692;
  T c1 = -0.000000038052;
  T c2 = 0.000398064794;
  T c3 = -0.151679116635;
  T c4 = 4.8385912808;
  T c5 = 0.742380924027;
  T c6 = 3.99019417011;
  T con = 1.28;
  T d1 = 1.00000615302;
  T d2 = 1.98615381364;
  T d3 = 5.29330324926;
  T d4 = -15.1508972451;
  T d5 = 30.789933034;
  T ltone = 7.0;
  T p = 0.398942280444;
  T q = 0.39990348504;
  T r = 0.398942280385;
  bool up;
  T utzero = 18.66;
  T value;
  T y;
  T z;

  up = upper;
  z = x;

  if ( z < 0.0 )
  {
    up = !up;
    z = - z;
  }

  if ( ltone < z && ( ( !up ) || utzero < z ) )
  {
    if ( up )
    {
      value = 0.0;
    }
    else
    {
      value = 1.0;
    }
    return value;
  }

  y = 0.5 * z * z;

  if ( z <= con )
  {
    value = 0.5 - z * ( p - q * y 
      / ( y + a1 + b1 
      / ( y + a2 + b2 
      / ( y + a3 ))));
  }
  else
  {
    value = r * exp ( - y ) 
      / ( z + c1 + d1 
      / ( z + c2 + d2 
      / ( z + c3 + d3 
      / ( z + c4 + d4 
      / ( z + c5 + d5 
      / ( z + c6 ))))));
  }

  if ( !up )
  {
    value = 1.0 - value;
  }

  return value;
}

// int 0 to x t^(p - 1) exp(-t) dt
template<class P, class T>
inline T 
lgamma(const P& p, const T& x)
{
  T a;
  T an;
  T arg;
  T b;
  T c;
  T elimit = - 88.0;
  T oflo = 1.0E+37;
  T plimit = 1000.0;
  T pn1;
  T pn2;
  T pn3;
  T pn4;
  T pn5;
  T pn6;
  T rn;
  T tol = 1.0E-14;
  bool upper;
  T value;
  T xbig = 1.0E+08;

  value = 0.0;
//
//  Check the input.
//
  if ( x < 0.0 )
  {
    return std::numeric_limits<T>::quiet_NaN();
  }

  if ( p <= 0.0 )
  {
    return std::numeric_limits<T>::quiet_NaN();
  }

  if ( x == 0.0 )
  {
    value = 0.0;
    return value;
  }
//
//  If P is large, use a normal approximation.
//
  if ( plimit < p )
  {
    pn1 = 3.0 * sqrt ( p ) * ( pow ( x / p, 1.0 / 3.0 ) 
    + 1.0 / ( 9.0 * p ) - 1.0 );

    upper = false;
    value = alnorm ( pn1, upper );
    return value;
  }
//
//  If X is large set value = 1.
//
  if (x > xbig)
  {
    value = 1.0;
    return value;
  }
//
//  Use Pearson's series expansion.
//  (Note that P is not large enough to force overflow in ALOGAM).
//  No need to test IFAULT on exit since P > 0.
//
  if ( x <= 1.0 || x < p )
  {
    arg = p * log ( x ) - x - lgamma (p + 1.0);
    c = 1.0;
    value = 1.0;
    a = p;

    for ( ; ; )
    {
      a = a + 1.0;
      c = c * x / a;
      value = value + c;

      if ( c <= tol )
      {
        break;
      }
    }

    arg = arg + log ( value );

    if ( elimit <= arg )
    {
      value = exp ( arg );
    }
    else
    {
      value = 0.0;
    }
  }
//
//  Use a continued fraction expansion.
//
  else 
  {
    arg = p * log(x) - x - lgamma(p);
    a = 1.0 - p;
    b = a + x + 1.0;
    c = 0.0;
    pn1 = 1.0;
    pn2 = x;
    pn3 = x + 1.0;
    pn4 = x * b;
    value = pn3 / pn4;

    for ( ; ; )
    {
      a = a + 1.0;
      b = b + 2.0;
      c = c + 1.0;
      an = a * c;
      pn5 = b * pn3 - an * pn1;
      pn6 = b * pn4 - an * pn2;

      if ( pn6 != 0.0 )
      {
        rn = pn5 / pn6;

        if ( fabs ( value - rn ) <= std::min ( tol, tol * rn ) )
        {
          break;
        }
        value = rn;
      }

      pn1 = pn3;
      pn2 = pn4;
      pn3 = pn5;
      pn4 = pn6;
//
//  Re-scale terms in continued fraction if terms are large.
//
      if ( oflo <= fabs ( pn5 ) )
      {
        pn1 = pn1 / oflo;
        pn2 = pn2 / oflo;
        pn3 = pn3 / oflo;
        pn4 = pn4 / oflo;
      }
    }

    arg = arg + log ( value );

    if ( elimit <= arg )
    {
      value = 1.0 - exp ( arg );
    }
    else
    {
      value = 1.0;
    }
  }

  return value;
}
