#ifndef ATA_FUNCTIONS_H
#define ATA_FUNCTIONS_H
#include "ATA/config.h"
#include <cmath>
#include <limits>
#include <type_traits>
#include <algorithm>

namespace ata
{
    template<typename F>
    ATA_CONSTEXPR bool equal(F a, F b)
    {
        return std::fabs(a - b) <= std::numeric_limits<F>::epsilon();
    }

    ATA_CONSTEXPR bool dequal(double a, double b)
    {
        return equal<double>(a, b);
    }

    ATA_CONSTEXPR bool fequal(float a, float b)
    {
        return equal<float>(a, b);
    }

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	ATA_CONSTEXPR T clamp(T val, T low, T high)
	{
		return std::max(low, std::min(val, high));
	}

    ATA_CONSTEXPR float fclamp(float val, float low, float high)
	{
	    return clamp<float>(val, low, high);
	}
}


#endif // MATH_H_INCLUDED
