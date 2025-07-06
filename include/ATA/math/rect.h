#ifndef ATA_RECT_H
#define ATA_RECT_H
#include "ATA/config.h"
#include "ATA/math/vec.h"

namespace ata
{
    template <typename T>
    struct rect
    {
		public:
		
		    ATA_CONSTEXPR rect() :
		    	x {0},
		    	y {0},
		    	w {0},
		    	h {0}
		    {
		    }

		    ATA_CONSTEXPR rect(T rectLeft, T rectTop, T rectWidth, T rectHeight) :
		        x {rectLeft},
		        y {rectTop},
		        w {rectWidth},
		        h {rectHeight}
		    {
		    }

		    ATA_CONSTEXPR rect(const vec2<T>& v1, const vec2<T>& v2) :
		        x {v1.x},
		        y {v1.y},
		        w {v2.x},
		        h {v2.y}
		    {
		    }

		    ATA_CONSTEXPR rect(T _x, T _y, vec2<T> v) :
		        x {_x},
		        y {_y},
		        w {v.x},
		        h {v.y}
		    {
		    }

		    ATA_CONSTEXPR rect(vec2<T> v, T _x, T _y) :
		        x {v.x},
		        y {v.y},
		        w {_x},
		        h {_y}
		    {
		    }
		    
		    template <typename U>
		    ATA_CONSTEXPR rect(const rect<U>& r) :
		        x {static_cast<T>(r.x)},
		        y {static_cast<T>(r.y)},
		        w {static_cast<T>(r.w)},
		        h {static_cast<T>(r.h)}
		    {
		    }

		    template <typename U>
		    ATA_CONSTEXPR rect(const vec2<U>& v1, const vec2<U>& v2) :
		        x {static_cast<T>(v1.x)},
		        y {static_cast<T>(v1.y)},
		        w {static_cast<T>(v2.x)},
		        h {static_cast<T>(v2.y)}
		    {
		    }

		    template <typename U>
		    ATA_CONSTEXPR rect(U _x, U _y, const vec2<U>& v) :
		        x {static_cast<T>(_x)},
		        y {static_cast<T>(_y)},
		        w {static_cast<T>(v.x)},
		        h {static_cast<T>(v.y)}
		    {
		    }

		    template <typename U>
		    ATA_CONSTEXPR rect(const vec2<U>& v, U _x, U _y) :
		        x {static_cast<T>(v.x)},
		        y {static_cast<T>(v.y)},
		        w {static_cast<T>(_x)},
		        h {static_cast<T>(_y)}
		    {
		    }

			template <typename U>
			ATA_CONSTEXPR rect(U _x, U _y, U _w, U _h) :
				x {static_cast<T>(_x)},
				y {static_cast<T>(_y)},
				w {static_cast<T>(_w)},
				h {static_cast<T>(_h)}
			{
			}

		    ATA_CONSTEXPR void setPosition(vec2<T> position)
		    {
		        x = position.x;
		        y = position.y;
		    }

		    ATA_CONSTEXPR vec2<T> getPosition() const
		    {
		        return {x, y};
		    }

		    ATA_CONSTEXPR void setSize(vec2<T> size)
		    {
		        w = size.x;
		        h = size.y;
		    }

		    ATA_CONSTEXPR vec2<T> getSize() const
		    {
		        return {w, h};
		    }

		    ATA_CONSTEXPR bool contains(T _x, T _y) const
		    {
		        return (_x >= x) && (_x < x + w) && (_y >= y) && (_y <= y + h);
		    }
		    
		    ATA_CONSTEXPR bool contains(const vec2<T>& pos) const
		    {
		        return contains(pos.x, pos.y);
		    }

			rect<T>& operator=(const rect<T>& other)
			{
				if(this != &other)
				{
					x = other.x;
					y = other.y;
					w = other.w;
					h = other.h;
				}
				
				return *this;
			}
			
			
			template<typename U>
			ATA_CONSTEXPR rect<T>& operator=(const rect<U>& other)
			{
				x = static_cast<T>(other.x);
				y = static_cast<T>(other.y);
				w = static_cast<T>(other.w);
				h = static_cast<T>(other.h);
				return *this;
			}

		    ATA_CONSTEXPR bool intersects(const rect<T>& r) const
		    {
		        // Compute the intersection boundaries
		        const T interLeft   = std::max(x, r.x);
		        const T interTop    = std::max(y, r.y);
		        const T interRight  = std::min(x + w, r.x + r.w);
		        const T interBottom = std::min(y + h, r.y + r.h);

		        // If the intersection is valid (positive non zero area), then there is an intersection
		        return (interLeft < interRight) && (interTop < interBottom);
		    }

		public:

		    T x; //!< Left coordinate of the rectangle
		    T y; //!< Top coordinate of the rectangle
		    T w; //!< Width of the rectangle
		    T h; //!< Height of the rectangle
    };

    template <typename T>
    ATA_CONSTEXPR bool operator==(const rect<T>& left, const rect<T>& right)
    {
        return (left.x == right.x) && (left.w == right.w)
            && (left.y == right.y) && (left.h == right.h);
    }


    template <typename T>
    ATA_CONSTEXPR bool operator!=(const rect<T>& left, const rect<T>& right)
    {
        return !(left == right);
    }

    using rectf = rect<float>;
    using recti = rect<int>;
    using rectu = rect<unsigned int>;
}

#endif // RECT_H_INCLUDED
