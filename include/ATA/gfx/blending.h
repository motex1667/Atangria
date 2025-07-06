#ifndef ATA_BLENDING_H
#define ATA_BLENDING_H
#include "ATA/config.h"
#include "ATA/core/glresource.h"

namespace ata
{
    enum class BlendFactor
    {
        Zero,
        One,
        SrcColor,        
        OneMinusSrcColor,
        DstColor,        
        OneMinusDstColor,
        SrcAlpha,        
        OneMinusSrcAlpha,
        DstAlpha,        
        OneMinusDstAlpha 
    };

    enum class BlendEquation
    {
        Add,
        Subtract,
        RevSubtract,
        Min,
        Max,
    };

    class ATA_API Blending
    {
		public:
			Blending();
			Blending(BlendFactor src, BlendFactor dst, BlendEquation = BlendEquation::Add);
			Blending(BlendFactor src, BlendFactor dst, BlendEquation color_eq,
					 BlendFactor alph_src, BlendFactor alph_dst, BlendEquation alpha_eq);
			
			BlendFactor     colorSrcFactor;
			BlendFactor     colorDstFactor;
			BlendEquation   colorEquation;
			BlendFactor     alphaSrcFactor;
			BlendFactor     alphaDstFactor;
			BlendEquation   alphaEquation;
		
		private:
			friend class BaseRenderer;
			friend class ContextManager;
			
			static void bind(const ata::Blending& b);
    };

    ATA_API bool operator==(const Blending& b1, const Blending& b2);
    ATA_API bool operator!=(const Blending& b1, const Blending& b2);

    ATA_API extern const Blending BlendAlpha;
    ATA_API extern const Blending BlendAdd;
    ATA_API extern const Blending BlendMultiply;
    ATA_API extern const Blending BlendNone;
}

#endif
