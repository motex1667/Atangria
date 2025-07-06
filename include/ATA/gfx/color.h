#ifndef ATA_COLOR_H
#define ATA_COLOR_H
#include "ATA/config.h"

namespace ata
{
	struct ATA_API Color
	{
		Color(SPuint8 r = 255, SPuint8 g = 255, SPuint8 b = 255, SPuint8 a = 255) :
			r(r),
			g(g),
			b(b),
			a(a)
		{
		}
		
		SPuint8 r;
		SPuint8 g;
		SPuint8 b;
		SPuint8 a;

		const static Color Black;
        	const static Color White;
        	const static Color Red;
        	const static Color Green;
	        const static Color Blue;
	        const static Color Yellow;
        	const static Color Magenta;
        	const static Color Cyan;
        	const static Color Transparent;
	};

	ATA_API ATA_CONSTEXPR bool operator==(const Color& c1, const Color& c2)
    	{
        	return (c1.r == c2.r
             	     && c1.g == c2.g
             	     && c1.b == c2.b
             	     && c1.a == c2.a);
    	}

	ATA_API ATA_CONSTEXPR bool operator!=(const Color& c1, const Color& c2)
	{
	    return !(c1 == c2);
	}
}

#endif
