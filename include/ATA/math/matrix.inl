template<typename T>
using enable_if_floating_point = typename std::enable_if<std::is_floating_point<T>::value>::type;

template<typename T, size_t L>
using fp_matrix_t = base_matrix<T, L, enable_if_floating_point<T>>;

template<typename T, size_t L>
base_matrix<T, L, enable_if_floating_point<T>>::base_matrix() :
    m_matrix    {nullptr},
    m_inv_matrix{nullptr},
    m_calc_inv  {true},
    m_calc_det  {true},
    m_det       {static_cast<T>(0.0)}
{
    m_matrix = new T[L * L];
	memset(m_matrix, static_cast<T>(0.0), sizeof(T) * L * L);
	for(size_t i = 0; i < L; i++)
	{
		// set up the identity matrix by default..
		m_matrix[i * L + i] = static_cast<T>(1.0);
	}
}

template<typename T, size_t L>
base_matrix<T, L, enable_if_floating_point<T>>::base_matrix(const base_matrix& other) :
    m_matrix    {nullptr},
    m_inv_matrix{nullptr},
    m_calc_inv  {true},
    m_calc_det  {true},
    m_det       {static_cast<T>(0.0)}
{
    m_matrix = new T[L * L];
    memcpy(m_matrix, other.m_matrix, sizeof(T) * L * L);
}

template<typename T, size_t L>
base_matrix<T,L>& base_matrix<T, L, enable_if_floating_point<T>>::operator=(const base_matrix<T,L>& other)
{
    if(this != &other)
    {
        m_calc_det = m_calc_inv = true;
        memcpy(m_matrix, other.m_matrix, sizeof(T) * L * L);
    }
    return *this;
}

template<typename T, size_t L>
base_matrix<T, L, enable_if_floating_point<T>>::base_matrix(base_matrix&& other) noexcept : base_matrix()
{
    memmove(m_matrix, other.m_matrix, sizeof(T) * L * L);
    delete other.m_matrix;
    other.m_matrix = nullptr;
    other.m_det = static_cast<T>(0.0);
    other.m_calc_det = true;

    if(other.m_inv_matrix)
    {
        delete other.m_inv_matrix;
        other.m_inv_matrix = nullptr;
        other.m_calc_inv = true;
    }
}

template<typename T, size_t L>
base_matrix<T, L>& base_matrix<T, L, enable_if_floating_point<T>>::operator=(base_matrix<T, L>&& other) noexcept
{
    if(this != &other)
    {
        m_calc_det = m_calc_inv = true;
        memmove(m_matrix, other.m_matrix, sizeof(T) * L * L);
        delete other.m_matrix;
        other.m_matrix = nullptr;
        other.m_det = static_cast<T>(0.0);
        other.m_calc_det = true;

        if(other.m_inv_matrix)
        {
            delete other.m_inv_matrix;
            other.m_inv_matrix = nullptr;
            other.m_calc_inv = true;

        }
    }
    return *this;
}

template<typename T, size_t L>
base_matrix<T, L, enable_if_floating_point<T>>::~base_matrix()
{
    if(m_matrix)
    {
        delete m_matrix;
    }

    if(m_inv_matrix)
    {
        delete m_inv_matrix;
    }
}

template<typename T, size_t L>
fp_matrix_t<T, L>& base_matrix<T, L, enable_if_floating_point<T>>::operator+=(const fp_matrix_t<T, L>& other)
{
	for(size_t i = 0; i < L; i++)
	{
		for(size_t j = 0; j < L; j++)
		{
			m_matrix[i * L + j] += other.m_matrix[i * L + j];
		}
	}
	return *this;
}

template<typename T, size_t L>
fp_matrix_t<T, L>& base_matrix<T, L, enable_if_floating_point<T>>::operator-=(const fp_matrix_t<T, L>& other)
{
	for(size_t i = 0; i < L; i++)
	{
		for(size_t j = 0; j < L; j++)
		{
			m_matrix[i * L + j] -= other.m_matrix[i * L + j];
		}
	}
	return *this;
}

template<typename T, size_t L>
fp_matrix_t<T, L>& base_matrix<T, L, enable_if_floating_point<T>>::operator*=(const fp_matrix_t<T, L>& other)
{
	T result[L * L] = {0};
	for(size_t i = 0; i < L; i++)
	{
		for(size_t j = 0; j < L; j++)
		{
			for(size_t k = 0; k < L; k++)
			{
				result[i * L + j] += (m_matrix[k * L + j] * other.m_matrix[i * L + k]);
			}
		}
	}

	memcpy(m_matrix, result, sizeof(T) * L * L);
	return *this;
}

template<typename T, size_t L>
bool base_matrix<T, L, enable_if_floating_point<T>>::operator==(const fp_matrix_t<T, L>& other)
{
	for(size_t i = 0; i < L * L; i++)
	{
		if(!ata::equal<T>(m_matrix[i], other.m_matrix[i]))
			return false;
	}
	return true;
}

template<typename T, size_t L>
bool base_matrix<T, L, enable_if_floating_point<T>>::operator!=(const fp_matrix_t<T, L>& other)
{
	return !(*this == other);
}

template<typename T, size_t L>
void base_matrix<T, L, enable_if_floating_point<T>>::set(size_t index, T v)
{
    if((index < L * L) && !ata::equal<T>(m_matrix[index], v))
    {
        m_calc_det = m_calc_inv = true;
        m_matrix[index] = v;
    }
}

template<typename T, size_t L>
void base_matrix<T, L, enable_if_floating_point<T>>::set(size_t r, size_t c, T v)
{
    set(r * L + c, v);
}

template<typename T, size_t L>
T base_matrix<T, L, enable_if_floating_point<T>>::get(size_t index) const
{
    return (index < L * L) ? m_matrix[index] : static_cast<T>(0.0);
}

template<typename T, size_t L>
T base_matrix<T, L, enable_if_floating_point<T>>::get(size_t r, size_t c) const
{
    return get(r * L + c);
}

template<typename T, size_t L>
bool base_matrix<T, L, enable_if_floating_point<T>>::hasInverse() const
{
    return !ata::equal(det(), static_cast<T>(0.0));
}

template<typename T, size_t L>
T base_matrix<T, L, enable_if_floating_point<T>>::det() const
{
    if(m_calc_det)
    {
        m_det = determinant(m_matrix, L);
        m_calc_det = false;
    }
    return m_det;
}

template<typename T, size_t L>
base_matrix<T, L, enable_if_floating_point<T>>::operator const T*() const
{
    return m_matrix;
}

template<typename T, size_t L>
const T* base_matrix<T, L, enable_if_floating_point<T>>::inv() const
{
    if(m_calc_inv)
    {
		if(m_inv_matrix != nullptr)
		{
			delete m_inv_matrix;
		}

        m_inv_matrix = inverse(m_matrix, det());
        m_calc_inv = false;
    }
    return m_inv_matrix;
}

template<typename T, size_t L>
T* base_matrix<T, L, enable_if_floating_point<T>>::minor(const T* m, size_t length, size_t r, size_t c)
{
    assert(r < length && r >= 0 && "Invalid row");
    assert(c < length && c >= 0 && "Invalid column");

    size_t newLength = (length - 1) * (length - 1);
    T* res = new T[newLength];

    for(size_t iPrev = 0, iNew = 0; iPrev < length; iPrev++)
    {
        if(iPrev != r)
        {
            for(size_t jPrev = 0, jNew = 0; jPrev < length; jPrev++)
                if(jPrev != c)
                    res[iNew * (length - 1) + (jNew++)] = m[iPrev * length + jPrev];
            iNew++;
        }
    }
    return res;
}

template<typename T, size_t L>
T base_matrix<T, L, enable_if_floating_point<T>>::determinant(const T* m, size_t length)
{
    if(length == 2)
        return m[0] * m[length + 1] - m[length] * m[1];

    T det = static_cast<T>(0.0);
    bool conjugate = false;
    for(size_t j = 0; j < length; j++)
    {
        T* min = minor(m, length, 0, j);
        det +=  m[j] * determinant(min, length - 1) * (conjugate ? -1.0 : 1.0);
        delete min;
        conjugate = !conjugate;
    }

    return det;
}

template<typename T, size_t L>
T* base_matrix<T, L, enable_if_floating_point<T>>::transpose(const T* m)
{
    T* t = new T[L * L];
    for(size_t i = 0; i < L; i++)
        for(size_t j = 0; j < L; j++)
            t[j * L + i] = m[i * L + j];

    return t;
}

template<typename T, size_t L>
T* base_matrix<T, L, enable_if_floating_point<T>>::adjoint(const T* m)
{
    T* adj = new T[L * L];
    if(L == 2)
    {
        adj[0]     =  m[L + 1];
        adj[L]     = -m[L];
        adj[1]     = -m[1];
        adj[L + 1] =  m[0];
        return adj;
    }

    bool conjugate = false;
    for(size_t i = 0; i < L; i++)
    {
        for(size_t j = 0; j < L; j++)
        {
            T* min = minor(m, L, i, j);
            adj[i * L + j] = determinant(min, L - 1) * static_cast<T>((conjugate ? -1.0 : 1.0));
            delete min;
            conjugate = !conjugate;
        }

        if(L % 2 == 0)
            conjugate = !conjugate;
    }

    T* ptr = adj;
    adj = transpose(adj);
    delete ptr;
    return adj;
}

template<typename T, size_t L>
T* base_matrix<T, L, enable_if_floating_point<T>>::inverse(const T* m, T d)
{
    if(ata::equal<T>(d, static_cast<T>(0.0)))
        return nullptr;

    T invf = static_cast<T>(1.0) / d;
    T* adj = adjoint(m);
    for(size_t i = 0; i < L; i++)
        for(size_t j = 0; j < L; j++)
            adj[i * L + j] *= invf;

    return adj;
}

template<typename T>
mat2<T>::mat2() : base_matrix<T, 2>()
{
}

template<typename T>
mat2<T>::mat2(T s00, T s01,
              T s10, T s11) : base_matrix<T, 2>()
{
    base_matrix<T, 2>::m_matrix[0] = s00; base_matrix<T, 2>::m_matrix[2] = s01;
    base_matrix<T, 2>::m_matrix[1] = s10; base_matrix<T, 2>::m_matrix[3] = s11;
}

template<typename T>
const mat2<T> mat2<T>::Identity = mat2<T>(1, 0,
										  0, 1);

template<typename T>
mat3<T>::mat3() : base_matrix<T, 3>()
{
}

template<typename T>
mat3<T>::mat3(T s00, T s01, T s02,
        T s10, T s11, T s12,
        T s20, T s21, T s22) :
    base_matrix<T, 3>()
{
    base_matrix<T, 3>::m_matrix[0] = s00; base_matrix<T, 3>::m_matrix[3] = s01; base_matrix<T, 3>::m_matrix[6] = s02;
    base_matrix<T, 3>::m_matrix[1] = s10; base_matrix<T, 3>::m_matrix[4] = s11; base_matrix<T, 3>::m_matrix[7] = s12;
    base_matrix<T, 3>::m_matrix[2] = s20; base_matrix<T, 3>::m_matrix[5] = s21; base_matrix<T, 3>::m_matrix[8] = s22;
}

template<typename T>
const mat3<T> mat3<T>::Identity = mat3<T>(1, 0, 0,
										  0, 1, 0,
										  0, 0, 1);

template<typename T>
mat4<T>::mat4() : base_matrix<T, 4>()
{
}

template<typename T>
mat4<T>::mat4(
        T s00, T s01, T s02, T s03,
        T s10, T s11, T s12, T s13,
        T s20, T s21, T s22, T s23,
        T s30, T s31, T s32, T s33) :
    base_matrix<T, 4>()
{
    base_matrix<T, 4>::m_matrix[ 0] = s00; base_matrix<T, 4>::m_matrix[ 4] = s01; base_matrix<T, 4>::m_matrix[ 8] = s02; base_matrix<T, 4>::m_matrix[12] = s03;
    base_matrix<T, 4>::m_matrix[ 1] = s10; base_matrix<T, 4>::m_matrix[ 5] = s11; base_matrix<T, 4>::m_matrix[ 9] = s12; base_matrix<T, 4>::m_matrix[13] = s13;
    base_matrix<T, 4>::m_matrix[ 2] = s20; base_matrix<T, 4>::m_matrix[ 6] = s21; base_matrix<T, 4>::m_matrix[10] = s22; base_matrix<T, 4>::m_matrix[14] = s23;
    base_matrix<T, 4>::m_matrix[ 3] = s30; base_matrix<T, 4>::m_matrix[ 7] = s31; base_matrix<T, 4>::m_matrix[11] = s32; base_matrix<T, 4>::m_matrix[15] = s33;
}

template<typename T>
mat4<T>::mat4(
        T s00, T s01, T s02,
        T s10, T s11, T s12,
        T s20, T s21, T s22) :
mat4(
        s00, s01, 0.0, s02,
        s10, s11, 0.0, s12,
        0.0, 0.0, 1.0, 0.0,
        s20, s21, 0.0, s22
    )
{
}

template<typename T>
const mat4<T> mat4<T>::Identity = mat4<T>(1, 0, 0, 0,
										  0, 1, 0, 0,
										  0, 0, 1, 0,
										  0, 0, 0, 1);

template<typename T>										  
template<typename U>
vec2f mat4<T>::transform(U x, U y) const
{
	vec2f result;
	result.x = base_matrix<T, 4>::m_matrix[0] * x + base_matrix<T, 4>::m_matrix[4] * y + base_matrix<T, 4>::m_matrix[12];
	result.y = base_matrix<T, 4>::m_matrix[1] * x + base_matrix<T, 4>::m_matrix[5] * y + base_matrix<T, 4>::m_matrix[13];
	return result;
}

template<typename T>										  
template<typename U>
vec2f mat4<T>::transform(const vec2<U>& point) const
{
	return transform(point.x, point.y);
}

template<typename T>
template<typename U>
rectf mat4<T>::transform(const rect<U>& rectangle) const
{
	const vec2f points[4] = 
	{
		transform(rectangle.left, rectangle.top),
		transform(rectangle.left, rectangle.top + rectangle.height),
		transform(rectangle.left + rectangle.width, rectangle.top),
		transform(rectangle.left + rectangle.width, rectangle.top + rectangle.height),
	};
	
	float left 	 = points[0].x;
	float top	 = points[0].y;
	float right	 = points[0].x;
	float bottom = points[0].y;
	
	for(size_t i = 0; i < 4; ++i)
	{
		if(points[i].x < left)   
			left = points[i].x;
        else if(points[i].x > right)
			right = points[i].x;
			
        if(points[i].y < top)
			top = points[i].y;
        else if(points[i].y > bottom)
			bottom = points[i].y;
	}
	
	return rectf(left, top, right - left, bottom - top);
}

template<typename T>
mat4<T>& mat4<T>::translate(T x, T y)
{
	mat4<T> translation(1, 0, x,
						0, 1, y,
						0, 0, 1);
	*this *= translation;
	return *this;
}

template<typename T>
mat4<T>& mat4<T>::translate(const vec2<T>& offset)
{
	return translate(offset.x, offset.y);
}

template<typename T>
mat4<T>& mat4<T>::rotate(T angle, T x, T y)
{
	T rad = static_cast<T>(angle * 3.141592654 / 180.0);
	T cos = std::cos(rad);
	T sin = std::sin(rad);
	
	mat4<T> rotation(cos, -sin, x * (1 - cos) + y * sin,
					 sin,  cos, y * (1 - cos) - x * sin,
					 0, 0, 1);
	*this *= rotation;
	return *this;
}

template<typename T>
mat4<T>& mat4<T>::rotate(T angle, const vec2<T>& center)
{
	return rotate(angle, center.x, center.y);
}

			
template<typename T>
mat4<T>& mat4<T>::scale(T x, T y, T cx, T cy)
{
	mat4<T> scaling(x, 0, cx * (1 - x),
					0, y, cy * (1 - y),
					0, 0, 1);
	*this *= scaling;
	return *this;
}

template<typename T>
mat4<T>& mat4<T>::scale(const vec2<T>& f)
{
	return scale(f.x, f.y);
}

template<typename T>
mat4<T>& mat4<T>::scale(const vec2<T>& f, const vec2<T>& c)
{
	return scale(f.x, f.y, c.x, c.y);
}