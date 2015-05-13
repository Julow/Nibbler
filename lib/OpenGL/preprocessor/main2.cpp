
#include <iostream>
#include <cmath>
#include <iomanip>

namespace ftce //ft_ConstExpr
{
template<typename T>
constexpr T			pow(T x, int p)
{
	T	ret(static_cast<T>(1));

	if (p > 0)
		for (int i = 0; i < p; i++)
			ret *= x;
	else if (p < 0)
		for (int i = 0; i < -p; i++)
			ret /= x;
	return (ret);
}

template<typename T>
constexpr T			factorial(T x)
{
	T	ret(x);

	while ((x -= static_cast<T>(1)) > static_cast<T>(0))
		ret *= x;
	return (ret);
}

template<typename T>
constexpr T			sqrt(T a)
{
	T		z = a; 
	T		ret = 0.0;
	T		j = 1.0;

	for(int i = 2 ; i > 0 ; i--)
	{
		T const		ip10 = ftce::pow(static_cast<T>(10.f), i);
		T const		ret2 = static_cast<T>(2.f) * ret;

		if (z - (ret2 + j * ip10) * j * ip10 >= 0)
		{
			while(z - (ret2 + j * ip10) * j * ip10 >= 0)
			{
				j++;
				if (j >= 10)
					break;
			}
			j--;
			z -= (ret2 + j * ip10) * j * ip10;
			ret += j * ip10;
			j = 1.0;
		}
	}
	for(int i = 0 ; i >= -2 ; i--)
	{
		T const		ip10 = ftce::pow(static_cast<T>(10.f), i);
		T const		ret2 = static_cast<T>(2.f) * ret;

		if (z - (ret2 + j * ip10) * j * ip10 >= 0)
		{
			while (z - (ret2 + j * ip10) * j * ip10 >= 0)
				j++;
			j--;
			z -= (ret2 + j * ip10) * j * ip10;
			ret += j * ip10;
			j = 1.0;
		}
	}
	return (ret);
}

template<typename T>
constexpr T			cos(T x)
{
	while (x > M_PI)
		x -= 2.f * M_PI;
	while (x < -M_PI)
		x += 2.f * M_PI;
	return (static_cast<T>(1)
		- (ftce::pow(x, 2) / ftce::factorial(2))
		+ (ftce::pow(x, 4) / ftce::factorial(4))
		- (ftce::pow(x, 6) / ftce::factorial(6))
		+ (ftce::pow(x, 8) / ftce::factorial(8))	// MaxError: +0.0239781(-2.3978114%)
		- (ftce::pow(x, 10) / ftce::factorial(10))	// MaxError: +0.0018293(-0.1829267%)
		+ (ftce::pow(x, 12) / ftce::factorial(12))	// MaxError: +0.0001009(-0.0100911%)
		// - (ftce::pow(x, 14) / ftce::factorial(14))	// MaxError: +0.0070322(-0.7032156%)
		// + (ftce::pow(x, 16) / ftce::factorial(16))	// MaxError: +0.0378902(-3.7890196%)
		);
}
};



#include <vector>
#include <tuple>
#include <functional>

namespace ftce //ft_ConstExpr
{
template<typename T>
void								test_sqrt(void)
{
#define STEP static_cast<T>(0.01f)
	typedef std::tuple<T, T, T, float>	t_result; //nbr, nbr mod2pi, realcos, mycos, 
	std::vector<t_result>					vect;

	for (T f = 0.1f;
		 f < 30000.f;
		 f += STEP)
	{
		T	his(std::sqrt(f));
		T	mine(ftce::sqrt<T>(f));
		vect.push_back(std::make_tuple(f, his, mine,
			fabs(his - mine) / his));
	}
	
	std::cout << "Greatest deltas in " << vect.size() << " samples" << std::endl;
	std::cout << "		   Value" <<
				 "		Ref Sqrt" <<
				 "		 My Sqrt" <<
				 "			Diff" <<
				 std::endl;
	
	float		maxdiff;
	t_result	*ptr;
		std::cout << std::fixed;		std::cout << std::setprecision(7);
		std::cout << std::showpos;
	for (int i = 1; i <= 20; i++)
	{
		maxdiff = 0.f;
		for (auto &v : vect)
		{
			if (std::get<3>(v) > maxdiff)
			{
				ptr = &v;
				maxdiff = std::get<3>(v);
			}
		}
		std::cout << std::setw(16);
		std::cout << std::get<0>(*ptr);
		std::cout << std::setw(16);
		std::cout << std::get<1>(*ptr);
		std::cout << std::setw(16);
		std::cout << std::get<2>(*ptr);
		std::cout << std::setw(16);
		std::cout << maxdiff * 100 << "%";
		// std::cout << maxdiff << "(" << maxdiff / std::get<2>(*ptr) * 100 << "%)";
		std::cout << std::endl;
		std::get<3>(*ptr) = 0.f;
	}
#undef STEP
}

template<typename T>
void								test_cos(void)
{
#define STEP static_cast<T>(0.00001f)
	typedef std::tuple<T, T, T, T, float>	t_result; //nbr, nbr mod2pi, realcos, mycos, 
	std::vector<t_result>					vect;

	for (T f = -M_PI * 5.f - STEP * 10.f;
		 f < M_PI * 5.f + STEP * 10.f;
		 f += STEP)
	{
		T	f2(f);

		while (f2 > M_PI)
			f2 -= 2.f * M_PI;
		while (f2 < -M_PI)
			f2 += 2.f * M_PI;
		T	his(std::cos(f));
		T	mine(ftce::cos<T>(f));
		vect.push_back(std::make_tuple(f, f2, his, mine,
			fabs(his - mine)));
	}
	
	std::cout << "Greatest deltas in " << vect.size() << " samples" << std::endl;
	std::cout << "		   Value" <<
				 "   Value mod 2pi" <<
				 "	 Ref Cosinus" <<
				 "	  My Cosinus" <<
				 "			Diff" <<
				 std::endl;
	
	float		maxdiff;
	t_result	*ptr;
		std::cout << std::fixed;		std::cout << std::setprecision(7);
		std::cout << std::showpos;
	for (int i = 1; i <= 20; i++)
	{
		maxdiff = 0.f;
		for (auto &v : vect)
		{
			if (std::get<4>(v) > maxdiff)
			{
				ptr = &v;
				maxdiff = std::get<4>(v);
			}
		}
		std::cout << std::setw(16);
		std::cout << std::get<0>(*ptr);
		std::cout << std::setw(16);
		std::cout << std::get<1>(*ptr);
		std::cout << std::setw(16);
		std::cout << std::get<2>(*ptr);
		std::cout << std::setw(16);
		std::cout << std::get<3>(*ptr);
		std::cout << std::setw(16);
		std::cout << maxdiff << "(" << maxdiff / std::get<2>(*ptr) * 100 << "%)";
		std::cout << std::endl;
		std::get<4>(*ptr) = 0.f;
	}
#undef STEP
}
};

int									main(void)
{
	// ftce::test_cos<float>();
	// constexpr float test1 = ftce::cos(1.f);
	// constexpr float test2 = ftce::sqrt(1.f);
	
	
	ftce::test_sqrt<float>();
	return (0);
}