#ifndef ATA_TEXTURE2D_H
#define ATA_TEXTURE2D_H
namespace ata
{
	enum class Format : int
	{
		Red,
		Green,
		Blue,
		Alpha,
		Rg,
		Rgb,
		Rgba,
		Bgr,
		Bgra,
		RedInteger,
		RgInteger,
		RgbInteger,
		RgbaInteger,
		BgraInteger,
		Luminance,
		LuminanceAlpha,
		Intensity,
		StencilIndex,
		DepthComponent,
		DepthStencil
	};

	enum class Unit : int
	{
		_0 = 0,
		_1,
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
	};

	class Texture2D : public GLResource
	{
		public:
			friend class Framebuffer;
			Texture2D();
			~Texture2D();

			/*
			 * load() allocates and updates a texture.
			 */
			bool read(const std::string& path);
			bool read(const void* memory, size_t size);

			/*
			 * alloc() only allocates space for a texture.
			 */
			bool alloc(unsigned int width, unsigned int height, Format internalFormat = Format::Rgba, Format format = Format::Rgba);
			bool alloc(const vec2u& size, Format internalFormat = Format::Rgba, Format format = Format::Rgba);

			/*
			 * update() feeds a texture object with data
			 */
			bool update(const Texture2D& other);
			bool update(const void* memory, size_t size);
			bool update(const ata::Image& img);
			bool update(const ata::Texture2D& img);

			int getHandle() const;

			void free();
			void bind(Unit unit = Unit::_0);

		private:
			unsigned int m_object;
			Format m_format;
			Format m_internal_format;
			vec2u m_size;

	}
}
#endif