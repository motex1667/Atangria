#ifndef ATA_CONTEXT_H
#define ATA_CONTEXT_H
#include "ATA/config.h"
#include "ATA/core/apidefs.h"
#include "ATA/core/glresource.h"
#include "ATA/gfx.h"

namespace ata
{	
	struct ContextCache
	{
		/*
		explicit ContextCache() :
			textureData {},
			blending {BlendNone},
			clientStateMask {0}
		{
		}
		
		struct TextureData
		{
			ata::Texture::Unit unit = ata::Texture::Unit::Unit0;
			ata::Texture::CoordinateType coordinateType = ata::Texture::CoordinateType::Normalized;
			SPuint32 id = 0;
		} textureData;
		
		Blending blending;
		SPubyte clientStateMask;*/
	};
			
	class ContextManager
	{
		public:
		
			ContextManager() = delete;
			
			static void applyConfigs(const ata::WindowConfig& config);

			static void* getSharedContext();
			
			static void ensureExtensionsInit();
			
			static ATA_proc getProcAddress(const char* procName);
			
			/*
			 *	expected behavior:
			 *	
			 *	- update the currently bound texture, if it is different from the last one
			 *	- binding to NULL will disable the tex-coords client state, so no tex-coord data is sent down the pipeline
			 *	- 
			 */
			//static void applyTexture(const ata::Texture* texture, Texture::CoordinateType coordinateType, Texture::Unit unit);
			
			//static void applyShader(const ata::Shader* shader);
			
			//static void applyBlending(const Blending& blending);
			
			//static void enableClientState(GLClientState state, bool enable);
			
			//static bool isClientStateEnabled(GLClientState state);
			
		private:
			friend class GLResource;
			friend class ContextLock;
			friend class BaseRenderer;
			
			static const ContextCache* getContextCache();
			
			static void initSharedContext();
			
			static void destroySharedContext();
			
			static void acquireContext();
			
			static void releaseContext();	
	};
	
    /*
     *
     * all contexts share their objects with a common default context
     *
     * context life cycle:
     * - only objects derived from GLResource can instantiate a shared context, e.g. textures, framebuffers, shaders or even other contexts
     * - the shared context persists until the last GL-resource object has been destroyed
     * - actual graphics contexts are managed by surfaces
     *
     * context creation:
     * when a surface instantiates a graphics context (GC), the GC will also create the shared context (SC), if not having been created already..
     * this happens because any GC is also a GLResource, where an SC is not considered to be a GLResource
     * context locks will always only trigger the SC, when no GC is available
     *
     * it is worth mentioning that surfaces are not GL-resources themselves
     *
     */
    class Context
    {
        public:
		    // context is managed by a surface and provides a graphics context
		    // it also sets up a shared context at creation
            friend class Surface;
            friend class GLResource;

            virtual ~Context();

            virtual bool create(WindowConfig config) = 0;

            virtual bool isCurrent() const;
			
            virtual bool makeCurrent(bool set);
			
        protected:
			friend class ContextManager;
			friend class BaseRenderer;
			
            Context();
			
            void* m_handle;
						
			ContextCache m_context_cache;
    };

    class GraphicsContext : public Context, public GLResource
    {
        private:
            friend class Surface;
            GraphicsContext();
           ~GraphicsContext();

            virtual bool create(WindowConfig conf) override;
    };
}

#endif
