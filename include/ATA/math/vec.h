#ifndef ATA_VEC_H
#define ATA_VEC_H
#include "ATA/types.h"
#include "ATA/math/functions.h"

namespace ata
{
    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    struct vec2
	{
		ATA_CONSTEXPR vec2() :
			x{0},
			y{0}
		{
		}

		ATA_CONSTEXPR vec2(T _x, T _y) :
			x{_x},
			y{_y}
		{
		}

		template<typename U>
		ATA_CONSTEXPR vec2(U _x, U _y) :
			x{static_cast<T>(_x)},
			y{static_cast<T>(_y)}
		{
		}

		float length() const
		{
            return std::sqrt(x * x + y * y);
		}

		vec2 normalized() const
		{
		    float len = length();
            return vec2{x / len, y / len};
		}

		template<typename U>
		ATA_CONSTEXPR vec2(const vec2<U>& v) :
			x{static_cast<T>(v.x)},
			y{static_cast<T>(v.y)}
		{
		}

		ATA_CONSTEXPR vec2(const vec2<T>& v) :
			x{v.x},
			y{v.y}
		{
		}

		ATA_CONSTEXPR vec2<T>& operator=(const vec2<T>& v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}
		
		template<typename U>
		ATA_CONSTEXPR vec2<T>& operator=(const vec2<U>& v)
		{
			x = static_cast<T>(v.x);
			y = static_cast<T>(v.y);
			return *this;
		}

		T x;
		T y;
	};

	template<typename T>
	float dot(const vec2<T>& v1, const vec2<T>& v2)
	{
	    return {v1.x * v2.x + v1.y * v2.y};
	}

	template<typename T>
	float angle(const vec2<T>& v1, const vec2<T>& v2)
    {
        return std::acos(dot(v1, v2) / v1.length() * v2.length()) * 180.f / 3.141592654f;
    }

    template <typename T, typename U>
    float angle(const vec2<T>& v1, const vec2<U>& v2)
    {
        return std::acos(dot(v1, v2) / v1.length() * v2.length()) * 180.f / 3.141592654f;
    }

    template <typename T>
    float angle(const vec2<T>& v)
    {
        return fmod(std::atan2(v.y, v.x) * 180.f / (3.141592654f) + 360.f, 360.f);
    }

    template<typename T>
    float distance(const vec2<T>& v1, const vec2<T>& v2)
    {
        return std::sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
    }

    template<typename T>
	ATA_CONSTEXPR vec2<T> operator-(const vec2<T>& v);

	template<typename T>
	ATA_CONSTEXPR vec2<T> operator+(const vec2<T>& v1, const vec2<T> v2);

	template<typename T>
	ATA_CONSTEXPR vec2<T> operator-(const vec2<T>& v1, const vec2<T> v2);

	template<typename T, typename U>
	ATA_CONSTEXPR vec2<T> operator+(const vec2<T>& v1, const vec2<U> v2);

	template<typename U, typename T>
	ATA_CONSTEXPR vec2<T> operator+(const vec2<U>& v1, const vec2<T> v2);

	template<typename T, typename U>
	ATA_CONSTEXPR vec2<T> operator-(const vec2<T>& v1, const vec2<U> v2);

	template<typename U, typename T>
	ATA_CONSTEXPR vec2<T> operator-(const vec2<U>& v1, const vec2<U> v2);

	template<typename T>
	ATA_CONSTEXPR vec2<T> operator*(const vec2<T>& v, float s);

	template<typename T>
	ATA_CONSTEXPR vec2<T> operator*(float s, const vec2<T>& v);

	template<typename T>
	float operator*(const vec2<T>& v1, const vec2<T>& v2);

	template<typename T, typename U>
	float operator*(const vec2<T>& v1, const vec2<U>& v2);

	template<typename T>
	bool operator==(const vec2<T>& v1, const vec2<T>& v2);

	template<typename T, typename U>
	bool operator==(const vec2<T>& v1, const vec2<U>& v2);

	template<typename T>
	bool operator!=(const vec2<T>& v1, const vec2<T>& v2);

	template<typename T, typename U>
	bool operator!=(const vec2<T>& v1, const vec2<U>& v2);

	template<typename T, typename U>
	bool operator!=(const vec2<T>& v1, const vec2<U>& v2);

	template<typename T>
	ATA_CONSTEXPR vec2<T>& operator+=(vec2<T>& v1, const vec2<T>& v2);

	template<typename T>
	ATA_CONSTEXPR vec2<T>& operator-=(vec2<T>& v1, const vec2<T>& v2);

	template<typename T, typename U>
	ATA_CONSTEXPR vec2<T>& operator+=(vec2<T>& v1, const vec2<U>& v2);

	template<typename T, typename U>
	ATA_CONSTEXPR vec2<T>& operator-=(vec2<T>& v1, const vec2<U>& v2);

	template<typename T>
	ATA_CONSTEXPR vec2<T>& operator*=(vec2<T>& v, float s);

	template<typename T>
	ATA_CONSTEXPR vec2<T>& operator*=(float s, vec2<T>& v);
		
	template <typename T>
	struct vec3
	{
		vec3() :
			x(0),
			y(0),
			z(0)
		{
		}
		
		vec3(T X, T Y, T Z) :
			x(X),
			y(Y),
			z(Z)
		{
		}

		template <typename U>
		vec3(const vec3<U>& vector) :
			x(static_cast<T>(vector.x)),
			y(static_cast<T>(vector.y)),
			z(static_cast<T>(vector.z))
		{
		}
		
		float length() const
		{
            return std::sqrt(x * x + y * y + z * z);
		}

		vec3 normalized() const
		{
		    float len = length();
            return vec3{x / len, y / len, z / len};
		}
		
		T x;
		T y;
		T z;
	};

	template <typename T>
	ATA_CONSTEXPR vec3<T> operator-(const vec3<T>& left);

	template <typename T>
	ATA_CONSTEXPR vec3<T>& operator+=(vec3<T>& left, const vec3<T>& right);

	template <typename T>
	ATA_CONSTEXPR vec3<T>& operator-=(vec3<T>& left, const vec3<T>& right);

	template <typename T>
	ATA_CONSTEXPR vec3<T> operator+(const vec3<T>& left, const vec3<T>& right);

	template <typename T>
	ATA_CONSTEXPR vec3<T> operator-(const vec3<T>& left, const vec3<T>& right);

	template <typename T>
	ATA_CONSTEXPR vec3<T> operator*(const vec3<T>& left, T right);

	template <typename T>
	ATA_CONSTEXPR vec3<T> operator*(T left, const vec3<T>& right);

	template <typename T>
	ATA_CONSTEXPR vec3<T>& operator*=(vec3<T>& left, T right);

	template <typename T>
	ATA_CONSTEXPR vec3<T> operator/(const vec3<T>& left, T right);

	template <typename T>
	ATA_CONSTEXPR vec3<T>& operator/=(vec3<T>& left, T right);

	template <typename T>
	ATA_CONSTEXPR bool operator==(const vec3<T>& left, const vec3<T>& right);

	template <typename T>
	ATA_CONSTEXPR bool operator!=(const vec3<T>& left, const vec3<T>& right);

#include "ATA/math/vec_impl.inl"

	using vec2f = vec2<float>;
	using vec2d = vec2<double>;
	using vec2i = vec2<int>;
	using vec2u = vec2<unsigned int>;
	using vec2b = vec2<bool>;
	using vec3i = vec3<int>;
	using vec3f = vec3<float>;

}

#endif
