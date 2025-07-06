#include "ATA/config/glfw_3_3.h"
#include "GL/glew.h"
#include "ATA/core/context.h"
#include "ATA/core/log.h"
#include "ATA/core/monitor.h"
#include "ATA/run/lock.h"
#include "ATA/run/thread_local_ptr.h"
/*
#include "ATA/gfx/ogl/glhelper.h"
#include "ATA/gfx/ogl/gldebug.h"
#include "ATA/gfx/renderer.h"
*/

namespace ata
{	
    class SharedContext : public Context
    {
        public:
            SharedContext();
           ~SharedContext();

            virtual bool create(WindowConfig config) override;
    };
}

namespace
{
    ata::Mutex contextGuard;
    unsigned int resourceCount = 0;
    ata::SharedContext* sharedContext = NULL;
    ata::ThreadLocalPtr<ata::Context> currentContext(NULL);

    GLFWwindow* handleToPtr(void* ptr)
    {
        return static_cast<GLFWwindow*>(ptr);
    }

	inline int translateOpenGlProfile(ata::OpenGlProfile profile)
	{
		switch(profile)
		{
			case ata::OpenGlProfile::Compat: return GLFW_OPENGL_COMPAT_PROFILE;
			case ata::OpenGlProfile::Core: return GLFW_OPENGL_CORE_PROFILE;
			default: break;
		}

		return GLFW_OPENGL_ANY_PROFILE;
	}
	
        /*
	inline int translateClientState(ata::GLClientState state)
	{
		switch(state)
		{
			case ata::GLClientState::ColorArray: return GL_COLOR_ARRAY;
			case ata::GLClientState::EdgeFlagArray: return GL_EDGE_FLAG_ARRAY;
			case ata::GLClientState::FogCoordArray: return GL_FOG_COORD_ARRAY;
			case ata::GLClientState::IndexArray: return GL_INDEX_ARRAY;
			case ata::GLClientState::NormalArray: return GL_NORMAL_ARRAY;
			case ata::GLClientState::SecondaryColorArray: return GL_SECONDARY_COLOR_ARRAY;
			case ata::GLClientState::TextureCoordArray: return GL_TEXTURE_COORD_ARRAY;
			case ata::GLClientState::VertexArray: return GL_VERTEX_ARRAY;
		}
		
		return 0;
	}
        */

    struct FallbackContext : public ata::NonCopyable
    {
        public:
            FallbackContext() :
                refCount {0},
                enabledFromThis {false}
            {
				assert(sharedContext && "Cannot provide context for non GL-objects");

                if(!currentContext)
                {
                    // there is currently no context active, enable the shared context
                    sharedContext->makeCurrent(true);
                    enabledFromThis = true;
                }
            }

           ~FallbackContext()
            {
                if(enabledFromThis)
                    sharedContext->makeCurrent(false);
            }

            unsigned int refCount;
            bool enabledFromThis;
    } *fallbackContext;
}

namespace ata
{
	inline void errorCallback(int errorCode, const char* msg)
        {
		err() << msg << " (Error Code 0x" << std::hex << errorCode << ")" << std::dec << std::endl;
        }

	inline void monitorCallback(GLFWmonitor* monitor, int eventType)
        {
                ata::monitorEvent.emit(ata::Monitor{monitor}, (ata::MonitorEventType)eventType);
        }
	
        /*
	void ContextManager::applyTexture(const ata::Texture* texture, Texture::CoordinateType coordinateType, Texture::Unit unit)
	{
		Lock lock(contextGuard);
		
		Context* context = currentContext;
		if(context)
		{
			assert(context->isCurrent() && "Expected context to be active");
			SPuint32 textureID = texture ? texture->getHandleGL() : 0;
			if((context->m_context_cache.textureData.id != textureID) ||
			   (context->m_context_cache.textureData.coordinateType != coordinateType) ||
			   (context->m_context_cache.textureData.unit != unit))
			{
				context->m_context_cache.textureData.id = textureID;
				context->m_context_cache.textureData.coordinateType = coordinateType;
				context->m_context_cache.textureData.unit = unit;
				
				bool textureAvailable = (context->m_context_cache.textureData.id != 0);
				bool updateTCA = !textureAvailable != !isClientStateEnabled(GLClientState::TextureCoordArray);
				
				ata::Texture::bind(texture, coordinateType, unit);
				
#ifndef ATA_OPENGL_CORE_PROFILE
				if(updateTCA)
				{
					enableClientState(GLClientState::TextureCoordArray, textureAvailable);
				}
#endif
			}
		}
	}
	
	void ContextManager::applyShader(const ata::Shader* shader)
	{
		Lock lock(contextGuard);
		
		Context* context = currentContext;
		if(context)
		{
			assert(context->isCurrent() && "Expected context to be active");
			
			if(Shader::shadersSupported())
			{
#ifndef ATA_OPENGL_CORE_PROFILE
				if(shader)
				{
					enableClientState(GLClientState::TextureCoordArray, true);
				}
#endif
				ata::Shader::bind(shader);
			}
		}
	}

	void ContextManager::applyBlending(const Blending& blending)
	{
		Lock lock(contextGuard);
		
		Context* context = currentContext;
		if(context)
		{
			assert(context->isCurrent() && "Expected context to be active");
			if(context->m_context_cache.blending != blending)
			{
				Blending::bind(blending);
				context->m_context_cache.blending = blending;
			}
		}
	}
	
	void ContextManager::enableClientState(GLClientState state, bool enable)
	{
		Lock lock(contextGuard);
		
		Context* context = currentContext;
		if(context)
		{
			assert(context->isCurrent() && "Expected context to be active");
			bool isEnabled = (context->m_context_cache.clientStateMask & static_cast<unsigned char>(state)) != 0;
			if(isEnabled != enable)
			{
				if(enable)
				{
					context->m_context_cache.clientStateMask |= static_cast<unsigned char>(state);
					spCheck(glEnableClientState(translateClientState(state)));
				}
				else
				{
					context->m_context_cache.clientStateMask &= ~static_cast<unsigned char>(state);
					spCheck(glDisableClientState(translateClientState(state)));
				}
			}
		}
	}
	
	bool ContextManager::isClientStateEnabled(GLClientState state)
	{
		Lock lock(contextGuard);
		Context* context = currentContext;
		
		bool enabled = false;
		if(context)
		{
			assert(context->isCurrent() && "Expected context to be active");
			enabled = (context->m_context_cache.clientStateMask & static_cast<unsigned char>(state)) != 0;
		}
		
		return enabled;
	}
        */
	
    void ContextManager::initSharedContext()
    {
        ata::Lock lock(contextGuard);
        if(resourceCount == 0)
        {
            if(!sharedContext)
            {
                sharedContext = new SharedContext();
                sharedContext->makeCurrent(false);
            }
        }
        resourceCount++;
    }

    void ContextManager::destroySharedContext()
    {
        ata::Lock lock(contextGuard);
        resourceCount--;
        if(resourceCount == 0)
        {
            if(sharedContext)
            {
                delete sharedContext;
                sharedContext = NULL;
            }
        }
    }

    void ContextManager::acquireContext()
    {
        Lock lock(contextGuard);

        if(!fallbackContext)
            fallbackContext = new FallbackContext;

        fallbackContext->refCount++;
    }

    void ContextManager::releaseContext()
    {
        Lock lock(contextGuard);
        assert(fallbackContext && "Expected context-saver to be non-null");
        fallbackContext->refCount--;

        if(fallbackContext->refCount == 0)
        {
            delete fallbackContext;
            fallbackContext = nullptr;
        }
    }
	
	SPproc ContextManager::getProcAddress(const char* procName)
	{
		return reinterpret_cast<SPproc>(glfwGetProcAddress(procName));
	}
	
    void* ContextManager::getSharedContext()
    {
        return sharedContext ? sharedContext->m_handle : nullptr;
    }

	void ContextManager::ensureExtensionsInit()
	{
		static bool checked = false;
                if(!checked)
                {
                        checked = true;
                        //spCheckExtensions();
                }
	}

	void ContextManager::applyConfigs(const ata::WindowConfig& conf)
	{
        glfwWindowHint(GLFW_RESIZABLE, conf.resizable);
        glfwWindowHint(GLFW_VISIBLE, conf.visible);
        glfwWindowHint(GLFW_DECORATED, conf.decorated);
        glfwWindowHint(GLFW_FOCUSED, conf.focused);
        glfwWindowHint(GLFW_AUTO_ICONIFY, conf.autoIconify);
        glfwWindowHint(GLFW_FLOATING, conf.floating);
        glfwWindowHint(GLFW_MAXIMIZED, conf.maximized);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, conf.transparentFramebuffer);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, conf.focusOnShow);
        glfwWindowHint(GLFW_SCALE_TO_MONITOR, conf.scaleToMonitor);

        glfwWindowHint(GLFW_RED_BITS, conf.redBits);
        glfwWindowHint(GLFW_GREEN_BITS, conf.greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, conf.blueBits);
        glfwWindowHint(GLFW_ALPHA_BITS, conf.alphaBits);
        glfwWindowHint(GLFW_DEPTH_BITS, conf.depthBits);
        glfwWindowHint(GLFW_STENCIL_BITS, conf.stencilBits);
        glfwWindowHint(GLFW_ACCUM_RED_BITS, conf.accumRedBits);
        glfwWindowHint(GLFW_ACCUM_GREEN_BITS, conf.accumGreenBits);
        glfwWindowHint(GLFW_ACCUM_BLUE_BITS, conf.accumBlueBits);
        glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, conf.accumAlphaBits);

        glfwWindowHint(GLFW_AUX_BUFFERS, conf.auxBuffers);
        glfwWindowHint(GLFW_SAMPLES, conf.samples);
        glfwWindowHint(GLFW_REFRESH_RATE, conf.refreshRate);
        glfwWindowHint(GLFW_STEREO, conf.stereo);
        glfwWindowHint(GLFW_SRGB_CAPABLE, conf.srgbCapable);
        glfwWindowHint(GLFW_DOUBLEBUFFER, conf.doubleBuffer);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ATA_OPENGL_VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ATA_OPENGL_VERSION_MINOR);
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_ANY_RELEASE_BEHAVIOR);

#if defined(ATA_OPENGL_CORE_PROFILE)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
        glfwWindowHint(GLFW_OPENGL_PROFILE, translateOpenGlProfile(OpenGlProfile::Core));
#else
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, false);
        glfwWindowHint(GLFW_OPENGL_PROFILE, translateOpenGlProfile(OpenGlProfile::Any));
#endif

#if defined(ATA_OPENGL_DEBUG_CONTEXT)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, conf.cocoaRetinaFramebuffer);
        glfwWindowHintString(GLFW_COCOA_FRAME_NAME, conf.cocoaFrameName);
        glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, conf.cocoaGraphicsSwitching);

        glfwWindowHintString(GLFW_X11_CLASS_NAME, conf.x11ClassName);
        glfwWindowHintString(GLFW_X11_INSTANCE_NAME, conf.x11InstanceName);
	}
	
	const ContextCache* ContextManager::getContextCache()
	{
		Lock lock(contextGuard);
		return currentContext ? &currentContext->m_context_cache : nullptr;
	}
	
    Context::Context() :
        m_handle{nullptr}
    {
    }

    Context::~Context()
    {
    }

    bool Context::isCurrent() const
    {
        return (glfwGetCurrentContext() == m_handle) && (m_handle != nullptr);
    }

    bool Context::makeCurrent(bool set)
    {
        Context* current = static_cast<Context*>(currentContext);
        if(set)
        {
            if(current != this)
            {
                glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_handle));
                currentContext = this;
            }
        }
        else
        {
            if(current == this)
            {
                glfwMakeContextCurrent(NULL);
                currentContext = NULL;
            }
        }

        return isCurrent() == set;
    }

	GraphicsContext::GraphicsContext() :
	    GLResource(),
	    Context()
    {
    }

    GraphicsContext::~GraphicsContext()
    {
        makeCurrent(false);
        glfwDestroyWindow(handleToPtr(m_handle));
    }

    bool GraphicsContext::create(WindowConfig conf)
	{
	    ContextManager::applyConfigs(conf);
        assert(ata::ContextManager::getSharedContext() != NULL && "Expected shared context");
        m_handle = glfwCreateWindow(conf.width, conf.height, conf.title,
                                    (conf.monitor != NULL) ? static_cast<GLFWmonitor*>(conf.monitor->m_handle) : NULL,
                                    static_cast<GLFWwindow*>(ata::ContextManager::getSharedContext()));

        return m_handle != NULL;
	}

    SharedContext::SharedContext()
    {
        WindowConfig config;
        config.width = 1; config.height = 1;
        config.visible = false;
        assert(create(config) && "Failed to create shared context");
        ContextManager::applyConfigs(WindowConfig{});
    }

    SharedContext::~SharedContext()
    {
        //ata::Renderer::destroy();
        makeCurrent(false);
        glfwDestroyWindow(handleToPtr(m_handle));
        glfwTerminate();
    }

    bool SharedContext::create(WindowConfig conf)
    {
        // init GLFW-API
        assert(sharedContext == NULL && "Expected \"this\" to be first shared-context instance");
        assert(glfwInit() == GLFW_TRUE && "Failed to initialize back end API");

        glfwSetTime(0.0);
        glfwSetErrorCallback(errorCallback);
		glfwSetMonitorCallback(monitorCallback);

        ContextManager::applyConfigs(conf);

        // create the hidden context-window
        m_handle = glfwCreateWindow(1, 1, "", NULL, NULL);
        assert(m_handle != NULL && "Failed to create shared context");

        makeCurrent(true);
        // load the GL-functions
        if(glewInit() == GLEW_OK)
        {
            ContextManager::ensureExtensionsInit();
            //Renderer::init();
        }
        else
        {
            err() << "Failed to load GL-functions" << std::endl;
            makeCurrent(false);
            return false;
        }

        // make no context current
        makeCurrent(false);

        return true;
    }
}
