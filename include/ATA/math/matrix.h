#ifndef ATA_MATRIX_H
#define ATA_MATRIX_H
#include "ATA/math/functions.h"
#include "ATA/math/vec.h"
#include "ATA/math/rect.h"
#include <stdint.h>
#include <type_traits>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace ata
{
    template<typename T, size_t, typename E = void>
    class base_matrix;
	
    template<typename T, size_t L>
    class base_matrix<T, L, typename std::enable_if<std::is_floating_point<T>::value>::type>
    {
        public:
            base_matrix();
            base_matrix(const base_matrix& other);
            base_matrix<T, L>& operator=(const base_matrix<T, L>& other);
            base_matrix(base_matrix&& other) noexcept;
            base_matrix<T, L>& operator=(base_matrix<T, L>&& other) noexcept;
            virtual ~base_matrix();

            void set(size_t index, T v);
            void set(size_t r, size_t c, T v);
            T get(size_t index) const;
            T get(size_t r, size_t c) const;
            bool hasInverse() const;
            T det() const;
            operator const T*() const;
            const T* inv() const;
			
			base_matrix& operator+=(const base_matrix& other);
			base_matrix& operator-=(const base_matrix& other);
			base_matrix& operator*=(const base_matrix& other);
			bool operator==(const base_matrix& other);
			bool operator!=(const base_matrix& other);
			
        protected:
            T* m_matrix;
			
        private:
            static T* minor(const T* m, size_t length, size_t r, size_t c);
            static T determinant(const T* m, size_t length);
            static T* transpose(const T* m);
            static T* adjoint(const T* m);
            static T* inverse(const T* m, T d);

            mutable T* m_inv_matrix;
            mutable bool m_calc_inv;
            mutable bool m_calc_det;
            mutable T m_det;
    };

    template<typename T>
    class mat2 : public base_matrix<T, 2>
    {
        public:
            mat2();
            mat2(T s00, T s01,
                 T s10, T s11);
				 
			static const mat2<T> Identity;
    };


    template<typename T>
    class mat3 : public base_matrix<T, 3>
    {
        public:
            mat3();
            mat3(T s00, T s01, T s02,
                 T s10, T s11, T s12,
                 T s20, T s21, T s22);
			
			static const mat3<T> Identity;
    };

    template<typename T>
    class mat4 : public base_matrix<T, 4>
    {
        public:
            mat4();

            mat4(T s00, T s01, T s02, T s03,
                 T s10, T s11, T s12, T s13,
                 T s20, T s21, T s22, T s23,
                 T s30, T s31, T s32, T s33);
				 
            mat4(T s00, T s01, T s02,
                 T s10, T s11, T s12,
                 T s20, T s21, T s22);
			
			template<typename U>
			vec2f transform(const vec2<U>& point) const;
			
			template<typename U>
			vec2f transform(U x, U y) const;
			
			template<typename U>
			rectf transform(const rect<U>& rectangle) const;
			
			mat4<T>& translate(const vec2<T>& offset);
			mat4<T>& translate(T x, T y);
			mat4<T>& rotate(T angle, T x = 0, T y = 0);
			mat4<T>& rotate(T angle, const vec2<T>& center);
			mat4<T>& scale(T sx, T sy, T cx = 0, T cy = 0);
			mat4<T>& scale(const vec2<T>& f);
			mat4<T>& scale(const vec2<T>& f, const vec2<T>& c);
			
			static const mat4<T> Identity;
    };
	
#include "ATA/math/matrix.inl"

    using mat2f = mat2<float>;
    using mat2d = mat2<double>;
    using mat3f = mat3<float>;
    using mat3d = mat3<double>;
    using mat4f = mat4<float>;
    using mat4d = mat4<double>;
}

#endif // MATRIX_H
