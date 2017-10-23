// tdual.cpp - test dual numbers
#include <ctime>
#include <functional>
#pragma warning(disable: 4305)
#pragma warning(disable: 4244)
#include "dual.h"
#include "norm.h"


using namespace std;
using namespace dual;
using namespace polynomial;

double timer(const std::function<void (void)>& f, size_t count)
{
	clock_t b = clock(); 
	while (count--) 
		f(); 
	clock_t e = clock();

	return 1.*(e - b)/CLOCKS_PER_SEC;
}

template<class T> 
void
fms_test_constructors(void)
{
	number<T,1> d1; // 0
	ensure (d1.size() == 1);
	ensure (d1[0] == 0);

	number<T,2> d2; // 0
	ensure (d2.size() == 2);
	ensure (d2[0] == 0);
	ensure (d2[1] == 0);

	number<T,3> d3; // 0
	ensure (d3.size() == 3);
	ensure (d3[0] == 0);
	ensure (d3[1] == 0);
	ensure (d3[2] == 0);

	T x(1.2), y(3.4);
	number<T,3> d4(x, y); // 1.2 I + 3.4 J
	ensure (d4.size() == 3);
	ensure (d4[0] == x);
	ensure (d4[1] == y);
	ensure (d4[2] == 0);

	number<T,3> d6(1.5);
	ensure (d6.size() == 3);
	ensure (d6[0] == 1.5);
	ensure (d6[1] == 0);
	ensure (d6[2] == 0);

	number<T,3> d7(1.5);
	ensure (d7.size() == 3);
	ensure (d7[0] == 1.5);
	ensure (d7[1] == 0);
	ensure (d7[2] == 0);

	number<T,3> d8((T)3);
	ensure (d8.size() == 3);
	ensure (d8[0] == 3);
	ensure (d8[1] == 0);
	ensure (d8[2] == 0);


	number<T,3> d9((T)3,(T)4);
	ensure (d9.size() == 3);
	ensure (d9[0] == 3);
	ensure (d9[1] == 4);
	ensure (d9[2] == 0);
}

template<class T>
void
fms_test_number(void)
{
	number<T, 2> x(1, 1), y;
	ensure (x.size() == 2);
	ensure (x[0] == 1);
	ensure (x[1] == 1);

	x *= x;
	ensure (x.size() == 2);
	ensure (x[0] == 1);
	ensure (x[1] == 2);

	y = x*x;
	ensure (y.size() == 2);
	ensure (y[0] == 1);
	ensure (y[1] == 4);

	number<T, 2> z(y);
	z.invert();
	ensure (z[0] == 1);
	ensure (z[1] == -4);

	z *= y;
	ensure (z[0] == 1);
	ensure (z[1] == 0);

	number<T, 3> w(1, 1);
	w *= w; // (I + J)*(I + J) = I + 2J + J^2
	ensure (w[0] == 1);
	ensure (w[1] == 2);
	ensure (w[2] == 1);

	number<T, 3> a(2,1), b(2,1);
	a *= a;
	b.mul_eq(b);
	ensure (a == b);
//	T u[] = {1,2,1};
//	ensure (w == number<T,3>(u));
}

template<class T>
void
fms_test_operator(void)
{
	number<T, 3> one(1);
	number<T, 3> x(2., 1);
	x += 1.0;
	ensure (x[0] == 3);
	ensure (x[1] == 1); // only the main diagonal
	ensure (x[2] == 0);

	x -= one;
	ensure (x[0] == 2);
	ensure (x[1] == 1); // only the main diagonal
	ensure (x[2] == 0);

	number<T, 3> y = 1/x;
	ensure (one == x*y);
	ensure (one == y*x);

	std::array<T, 3> z0 = {1, 2, 3};
//	number<T, 3> z = {1, 2, 3}; // fail: types with a base cannot be aggregate type
	number<T, 3> z = z0;
	ensure (z.size() == 3);
	ensure (z[0] == 1);
	ensure (z[1] == 2);
	ensure (z[2] == 3);
	z = -z;
	ensure (z[0] == -1);
	ensure (z[1] == -2);
	ensure (z[2] == -3);

	number<T, 3> a(1, 2), b(1, 3), c(2, 0);
	ensure (a < b);
	ensure (!(a == b));
	ensure (a != b);
	ensure (a <= b);
	ensure (!(a > b));
	ensure (!(a >= b));

	ensure (a < c);
	ensure (!(a == c));
	ensure (a != c);
	ensure (a <= c);
	ensure (!(a > c));
	ensure (!(a >= c));

	ensure (a == 1);
	ensure (!(a < 1));
	ensure (a <= 1);
	ensure (!(a > 1));
	ensure (a >= 1);
}

template<class T>
struct one : public continuant<T> {
	one& operator++() { return *this; }
	T operator*() { return 1; }
};

template<class T>
void
fms_test_polynomial(void)
{
	// p(x) = 1 + 2x + 3x^2
	array<T, 3> p = {1, 2, 3};
	T x = (T)2, y;

	y = polynomial::horner<T,T,3>(p.data(), x);
	ensure (y == 1 + x*(2 + x*3));
	y = polynomial::horner(p, x);
	ensure (y == 1 + x*(2 + x*3));
	y = polynomial::horner(p.size(), p.data(), x);
	ensure (y == 1 + x*(2 + x*3));

	number<T, 3> X(x,1), Y;
	Y = polynomial::horner(p, X);
	ensure (Y._(0) == 17);
	// p'(x) = 2 + 6x;
	ensure (Y._(1) == 2 + 6*2);
	// p''(x) == 6
	ensure (Y._(2) == 6);

	array<number<T, 3>, 3> P; // = { p[0], p[1], p[2] };
	P[0] = number<T, 3>(p[0]); // scalars
	P[1] = number<T, 3>(p[1]);
	P[2] = number<T, 3>(p[2]);
	Y = polynomial::horner<>(P, X);
	ensure (Y._(0) == 17);
	// p'(x) = 2 + 6x;
	ensure (Y._(1) == 2 + 6*2);
	// p''(x) == 6
	ensure (Y._(2) == 6);

	expn<T> e;
	ensure (*e == 1);
	ensure (*++e == 1);
	ensure (*++e == 1./2);
	ensure (*++e == 1./6);

	y = horner<T,T,1>(expn<T>(), 1); 
	y = horner<T,T,2>(expn<T>(), 1); 
	y = horner<T,T,3>(expn<T>(), 1); 
	y = horner<T,T,4>(expn<T>(), 1); 
	y = horner<T,T,5>(expn<T>(), 1); 
	y = horner<T,T,18>(expn<T>(), 1); 
	T one(1);
	ensure (y == ::exp(one));
}


template<class T>
T sq(const T& t)
{
	return t*t;
}

template<class T>
T id(const T& t)
{
	return 1 - 1/(1 - 1/(1 - 1/t));
}

template<class T>
void
fms_test_deriv(void)
{
	T x = 2;
	T d = sq(number<T,2>(x, 1)).derivative(1);
	ensure (d == 2*x);

	// same with lambda;
	number<T,2> X(x, 1);
	d = [](number<T,2> t){ return t*t; }(X).derivative(1);
	ensure (d == 2*x);

	number<T, 3> y, t(x,1);
	y = t*t*t + t*t + t;
	ensure (y.derivative(0) == x*x*x + x*x + x);
	ensure (y.derivative(1) == 3*x*x + 2*x + 1);
	ensure (y.derivative(2) == (6*x + 2));

	d = [](number<T,2> t) { return t*t*t + t*t + t; }(X).derivative(1);
	ensure (d == 3*x*x + 2*x + 1);

	number<T,3> X3(x, 1);
	d = [](number<T,3> t) { return t*t*t + t*t + t; }(X3).derivative(2);
	ensure (d == 6*x + 2);

	d = [](number<T,3> t) { return 2.*pow(t, 3); }(X3).derivative(1);
	ensure (d == 6*x*x);

	d = [](number<T,3> t) { return 3. + 2.*t + t*t; }(X3).derivative(1);
	ensure (d == 2 + 2*x);

	d = [](number<T,3> t) { return 1/t; }(X3).derivative(1);
	ensure (d == -1/(x*x));

	d = id(number<T,2>(X)).derivative(1);
	ensure (d == 1);
	
	std::function<number<T,3>(number<T,3>)> f = [](number<T,3> t) { return 1 - 1/(1 - 1/(1 - 1/t)); };
	d = f(X3).derivative(1);
	ensure (d == 1);
	X3 = number<T,3>(2., 1);
	X3 = f(X3);
	d = f(X3).derivative(1);
	ensure (fabs(d - 1) < 1e-15);
}

template<class T>
void 
fms_test_log(void)
{
	T x = 2, y, z;

	number<T, 2> X(x, 1), Y, Z;
	Y = log(X);
	Z = exp(Y);
	ensure (Z == X);

	Y = sqrt(X);
	Z = Y*Y;
	y = sqrt(x);
	z = y*y;
	ensure (norm(Z - X, static_cast<T>(1)) < fabs(z - x)*Z.size());

	for (T x = .1; x < 1000; x += .1) {
		number<T,3> X(x, 1), Y;
		T y;

		Y = log(X);
		y = log(x);

		ensure (fabs(Y[0] - y) < 1e-15);
	}
}


template<class T>
void
fms_test_exp(void)
{
	number<T, 4> x = exp(number<T, 4>(0.,1)), y; // e^J = I + J + J^2/2! + J^3/3!
	ensure (x[0] == 1);
	ensure (x[1] == 1);
	ensure (x[2] == 1/2.);
	T onesixth = 1./6;
	ensure (x[3] == onesixth);
/*
	x = number<T,4>(1,1);
	y = polynomial::horner<dual::number<T,4>,T,1>(expn<T>(), x);
	y = polynomial::horner<dual::number<T,4>,T,2>(expn<T>(), x);
	y = polynomial::horner<dual::number<T,4>,T,3>(expn<T>(), x);
	y = polynomial::horner<dual::number<T,4>,T,4>(expn<T>(), x);
	y = polynomial::horner<dual::number<T,4>,T,5>(expn<T>(), x);
	y = polynomial::horner<dual::number<T,4>,T,6>(expn<T>(), x);
	y = polynomial::horner<dual::number<T,4>,T,7>(expn<T>(), x);
	y = polynomial::horner<dual::number<T,4>,T,8>(expn<T>(), x);
	double t;
	int n = 100;
	t = timer([x](void) { exp(x); return; }, n);
	y = exp(x);
	t = timer([x](void) { exp2(x); return; }, n);
	y = exp2(x);
	t = timer([x](void) { exp3(x); return; }, n);
	y = exp3(x);
	t = timer([x](void) { exp4(x); return; }, n);
	y = exp4(x);
*/
}

template<class T>
void
fms_test_normal(T x)
{
	T y, z, u;
	y = normal_pdf(x);
	z = normal_cdf(x);
	u = normal_inv(z);
//	z = u - x;
//	y = std::numeric_limits<T>::epsilon();
	ensure (fabs(u - x) < 20000.*std::numeric_limits<T>::epsilon());
}
/*
template<class T>
void
fms_test_normal_number(void)
{
	T eps = sqrt(std::numeric_limits<T>::epsilon());
	number<T,3> x(0.1, 1), y, z, u;
	y = normal_pdf(x);
	z = normal_cdf(x);
	ensure (fabs(y._(0) - z._(1)) < eps);
	ensure (fabs(y._(1) - z._(2)) < eps);
	// pdf'(x) = -x*pdf(x)
	ensure (fabs(z._(2) + x[0]*y[0]) < eps);

	u = normal_inv(z);
	T v;
	v = fabs(u - x);
	ensure (fabs(u - x) < eps);
}
*/
template<class T>
void
fms_test_continued_fraction(void)
{
	T a[] = {1, 1}, b[] = {1, 1, 1}, x;
	x = polynomial::continued_fraction<T,2>::evaluate(a, b);
	ensure (x == 1 + 1/(1 + 1./1));

	x = continued_fraction<T,2>::evaluate(one<T>(), one<T>());
	ensure (x == 1 + 1/(1 + 1./1));
	x = continued_fraction<T,38>::evaluate(one<T>(), one<T>());
	ensure (x == (1 + sqrt(5.))/2); // 37 fails
}

template<class T>
void
fms_test_chebyshev(void)
{
	polynomial::chebyshev<T,0> T0; 
	std::array<T,1> t0 = {1};
	ensure (T0 == t0);
	
	polynomial::chebyshev<T,1> T1; 
	std::array<T,2> t1 = {0, 1};
	ensure (T1 == t1);
	
	polynomial::chebyshev<T,2> T2; 
	std::array<T,3> t2 = {-1, 0, 2};
	ensure (T2 == t2);
	
	polynomial::chebyshev<T,3> T3; 
	std::array<T,4> t3 = {0, -3, 0, 4};
	ensure (T3 == t3);
}

template<class T>
void
fms_test_factorial(void)
{
	factorial<T,1> f1;
	ensure (f1.size() == 1);
	ensure (f1[0] == 1);

	factorial<T,2> f2;
	ensure (f2.size() == 2);
	ensure (f2[0] == 1);
	ensure (f2[1] == 1);

	factorial<T,3> f3;
	ensure (f3.size() == 3);
	ensure (f3[0] == 1);
	ensure (f3[1] == 1);
	ensure (f3[2] == f3[1]/2);

	factorial<T,4> f4;
	ensure (f4.size() == 4);
	ensure (f4[0] == 1);
	ensure (f4[1] == 1);
	ensure (f4[2] == f4[1]/2);
	ensure (f4[3] == f4[2]/3);
}

// 1, 1, 1/2, 1/6...
template<class T>
class expn : public continuant<T> {
	T p_, k_;
public:
	expn() : p_(0), k_(1) { }
	expn& operator++()
	{
		p_ = p_ ? p_/++k_ : 1;

		return *this;
	}
	T operator*()
	{
		return p_ ? p_ : 1;
	}
};

template<class T>
void
fms_test_gamma(void)
{
	ensure (T(0) == lgamma(T(1)));
	ensure (T(0) == lgamma(T(2)));
	ensure (fabs(2 - exp(lgamma(T(3)))) < M_SQRT_EPSILON);

	T f = 2;
	for (T x = 3; x <= 10; x += 1) {
		f *= x;
		ensure (fabs(log(f) - lgamma(x + 1)) < M_SQRT_EPSILON);
	}
}


template<class T>
inline void
fms_test_exp_()
{
	array<T,3> x = {0, 1, 2};
	array<T,3> y = {1, M_E, M_E*M_E};

	for (size_t i = 0; i < x.size(); ++i) {
		T z;
		z = y[i] - exp(x[i]);
		ensure (fabs(y[i] - exp(x[i])) < 10*std::numeric_limits<T>::epsilon());
		z = y[i] - exp(number<T,1>(x[i]))[0];
		ensure (fabs(y[i] - exp(number<T,1>(x[i]))[0]) < 10*std::numeric_limits<T>::epsilon());
		z = y[i] - exp2(number<T,1>(x[i]))[0];
		ensure (fabs(y[i] - exp2(number<T,1>(x[i]))[0]) < 10*std::numeric_limits<T>::epsilon());
		z = y[i] - exp3(number<T,1>(x[i]))[0];
//		ensure (fabs(y[i] - exp3(number<T,1>(x[i]))[0]) < 10*std::numeric_limits<T>::epsilon());
		z = y[i] - exp4(number<T,1>(x[i]))[0];
//		ensure (fabs(y[i] - exp4(number<T,1>(x[i]))[0]) < 10*std::numeric_limits<T>::epsilon());
		z = y[i] - exp5<T,24>(x[i]);
//		ensure (fabs(y[i] - exp5<T,24>(x[i])) < 10*std::numeric_limits<T>::epsilon());
	}
}

// Monte Carlo derivatives
template<class T, size_t N>
void fms_test_monte(void)
{
	::srand(static_cast<unsigned int>(::time(0)));

	double a = 0.5;
	dual::number<double,3> A(a, 1);
	dual::number<double,3> E(0.,1);

	for (int i = 0; i < N; ++i) {
		double x = 1.0*rand()/RAND_MAX;
		E = E + (x - A)*(x - A);
	}

	E = E/(1.*N);

	// X uniform [0,1]
	// E(X - a)^2 = 1/3 - 2a 1/2 + a^2
	// d/da E(X - a)^2 = -2 E(X - a) = 2a - 1
	// d^2/da^2 E(X - a)^2 = 2
	ensure (fabs(E._(0) - (1./3 - a + a*a)) < sqrt(1./N));
	ensure (fabs(E._(1) - (2*a - 1)) < sqrt(1./N));
	ensure (fabs(E._(2) - 2) < sqrt(1./N));
}

void
fms_test_dual(void)
{
	fms_test_constructors<float>();
	fms_test_constructors<double>();
	fms_test_number<float>();
	fms_test_number<double>();
	fms_test_operator<float>();
	fms_test_operator<double>();
	fms_test_deriv<float>();
	fms_test_deriv<double>();
	fms_test_exp<float>();
	fms_test_exp<double>();

	fms_test_polynomial<double>();
//	fms_test_polynomial<float>();
//	fms_test_polynomial<long double>();

	fms_test_log<double>();
	fms_test_log<float>();
//	fms_test_log<long double>();

	fms_test_normal<double>(0.1);
	fms_test_normal<float>(0.1F);
//	fms_test_normal<long double>(0.1L);
//		fms_test_normal<number<double,3>>(number<double,3>(0.,1));
//	fms_test_normal_number<double>();
	
	fms_test_gamma<double>();
//	fms_test_gamma<number<double,3>>();

	fms_test_chebyshev<double>();
	fms_test_continued_fraction<double>();
	fms_test_factorial<double>();

	fms_test_monte<double,100000>();
}
