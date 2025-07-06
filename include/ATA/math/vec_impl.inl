template<typename T>
ATA_CONSTEXPR vec2<T> operator-(const vec2<T>& v)
{
    vec2<T> vres;
    vres.x = -v.x;
    vres.y = -v.y;
    return vres;
}

template<typename T>
ATA_CONSTEXPR vec2<T> operator+(const vec2<T>& v1, const vec2<T> v2)
{
    vec2<T> vres;
    vres.x = v1.x + v2.x;
    vres.y = v1.y + v2.y;
    return vres;
}

template<typename T>
ATA_CONSTEXPR vec2<T> operator-(const vec2<T>& v1, const vec2<T> v2)
{
    vec2<T> vres;
    vres.x = v1.x - v2.x;
    vres.y = v1.y - v2.y;
    return vres;
}

template<typename T, typename U>
ATA_CONSTEXPR vec2<T> operator+(const vec2<T>& v1, const vec2<U> v2)
{
    vec2<T> vres;
    vres.x = v1.x + static_cast<T>(v2.x);
    vres.y = v1.y + static_cast<T>(v2.y);
    return vres;
}

template<typename T, typename U>
ATA_CONSTEXPR vec2<T> operator+(const vec2<U>& v1, const vec2<U> v2)
{
    vec2<T> vres;
    vres.x = static_cast<T>(v1.x) + v2.x;
    vres.y = static_cast<T>(v1.y) + v2.y;
    return vres;
}

template<typename T, typename U>
ATA_CONSTEXPR vec2<T> operator-(const vec2<T>& v1, const vec2<U> v2)
{
    vec2<T> vres;
    vres.x = v1.x - static_cast<T>(v2.x);
    vres.y = v1.y - static_cast<T>(v2.y);
    return vres;
}

template<typename T, typename U>
ATA_CONSTEXPR vec2<T> operator-(const vec2<U>& v1, const vec2<T> v2)
{
    vec2<T> vres;
    vres.x = static_cast<T>(v1.x) - v2.x;
    vres.y = static_cast<T>(v1.y) - v2.y;
    return vres;
}

template<typename T>
ATA_CONSTEXPR vec2<T> operator*(const vec2<T>& v, float s)
{
    vec2<T> vres;
    vres.x = v.x * s;
    vres.y = v.y * s;
    return vres;
}

template<typename T>
ATA_CONSTEXPR vec2<T> operator*(float s, const vec2<T>& v)
{
    vec2<T> vres;
    vres.x = v.x * s;
    vres.y = v.y * s;
    return vres;
}

template<typename T>
float operator*(const vec2<T>& v1, const vec2<T>& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}


template<typename T, typename U>
float operator*(const vec2<T>& v1, const vec2<U>& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

template<typename T>
bool operator==(const vec2<T>& v1, const vec2<T>& v2)
{
    return (v1.x == v2.x && v1.y == v2.y);
}

template<>
ATA_CONSTEXPR bool operator==<float>(const vec2<float>& v1, const vec2<float>& v2)
{
    return (fequal(v1.x, v2.x) && fequal(v1.y, v2.y));
}

template<>
ATA_CONSTEXPR bool operator==<double>(const vec2<double>& v1, const vec2<double>& v2)
{
    return (dequal(v1.x, v2.x) && dequal(v1.y, v2.y));
}

template<>
ATA_CONSTEXPR bool operator!=<float>(const vec2<float>& v1, const vec2<float>& v2)
{
    return !(v1 == v2);
}

template<>
ATA_CONSTEXPR bool operator!=<double>(const vec2<double>& v1, const vec2<double>& v2)
{
    return !(v1 == v2);
}

template<typename T, typename U>
bool operator==(const vec2<T>& v1, const vec2<U>& v2)
{
    return (
        (v1.x == static_cast<T>(v2.x))
    &&	(v1.y == static_cast<T>(v2.y)));
}

template<typename T>
bool operator!=(const vec2<T>& v1, const vec2<T>& v2)
{
    return !(v1 == v2);
}

template<typename T, typename U>
bool operator!=(const vec2<T>& v1, const vec2<U>& v2)
{
    return !(v1 == v2);
}

template<typename T>
ATA_CONSTEXPR vec2<T>& operator+=(vec2<T>& v1, const vec2<T>& v2)
{
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

template<typename T>
ATA_CONSTEXPR vec2<T>& operator-=(vec2<T>& v1, const vec2<T>& v2)
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

template<typename T, typename U>
ATA_CONSTEXPR vec2<T>& operator+=(vec2<T>& v1, const vec2<U>& v2)
{
    v1.x += static_cast<T>(v2.x);
    v1.y += static_cast<T>(v2.y);
    return v1;
}

template<typename T, typename U>
ATA_CONSTEXPR vec2<T>& operator-=(vec2<T>& v1, const vec2<U>& v2)
{
    v1.x -= static_cast<T>(v2.x);
    v1.y -= static_cast<T>(v2.y);
    return v1;
}

template<typename T>
ATA_CONSTEXPR vec2<T>& operator*=(vec2<T>& v, float s)
{
    v.x *= s;
    v.y *= s;
    return v;
}

template<typename T>
ATA_CONSTEXPR vec2<T>& operator*=(float s, vec2<T>& v)
{
    v.x *= s;
    v.y *= s;
    return v;
}

template <typename T>
ATA_CONSTEXPR vec3<T> operator -(const vec3<T>& left)
{
    return vec3<T>(-left.x, -left.y, -left.z);
}

template <typename T>
ATA_CONSTEXPR vec3<T>& operator +=(vec3<T>& left, const vec3<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;

    return left;
}

template <typename T>
ATA_CONSTEXPR vec3<T>& operator -=(vec3<T>& left, const vec3<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;

    return left;
}

template <typename T>
ATA_CONSTEXPR vec3<T> operator +(const vec3<T>& left, const vec3<T>& right)
{
    return vec3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template <typename T>
ATA_CONSTEXPR vec3<T> operator -(const vec3<T>& left, const vec3<T>& right)
{
    return vec3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template <typename T>
ATA_CONSTEXPR vec3<T> operator *(const vec3<T>& left, T right)
{
    return vec3<T>(left.x * right, left.y * right, left.z * right);
}

template <typename T>
ATA_CONSTEXPR vec3<T> operator *(T left, const vec3<T>& right)
{
    return vec3<T>(right.x * left, right.y * left, right.z * left);
}

template <typename T>
ATA_CONSTEXPR vec3<T>& operator *=(vec3<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;

    return left;
}

template <typename T>
ATA_CONSTEXPR vec3<T> operator /(const vec3<T>& left, T right)
{
    return vec3<T>(left.x / right, left.y / right, left.z / right);
}

template <typename T>
ATA_CONSTEXPR vec3<T>& operator /=(vec3<T>& left, T right)
{
    left.x /= right;
    left.y /= right;
    left.z /= right;

    return left;
}

template <typename T>
ATA_CONSTEXPR bool operator ==(const vec3<T>& left, const vec3<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

template <typename T>
ATA_CONSTEXPR bool operator !=(const vec3<T>& left, const vec3<T>& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}

template<>
ATA_CONSTEXPR bool operator==<float>(const vec3<float>& v1, const vec3<float>& v2)
{
    return (fequal(v1.x, v2.x) && fequal(v1.y, v2.y) && fequal(v1.z, v2.z));
}

template<>
ATA_CONSTEXPR bool operator==<double>(const vec3<double>& v1, const vec3<double>& v2)
{
    return (dequal(v1.x, v2.x) && dequal(v1.y, v2.y) && dequal(v1.z, v2.z));
}

template<>
ATA_CONSTEXPR bool operator!=<float>(const vec3<float>& v1, const vec3<float>& v2)
{
    return !(v1 == v2);
}

template<>
ATA_CONSTEXPR bool operator!=<double>(const vec3<double>& v1, const vec3<double>& v2)
{
    return !(v1 == v2);
}