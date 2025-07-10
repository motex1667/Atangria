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

	class Texture2D : public GLResource
	{
		public:
			Texture2D();
			~Texture2D();

			bool load(const std::string& path);
			bool load(const void* memory, ATAsize size);
			
			bool alloc(unsigned int width, unsigned int height, Format internalFormat = Format::Rgba, Format format = Format::Rgba);
			bool alloc(const vec2u& size, Format internalFormat = Format::Rgba, Format format = Format::Rgba);

			bool update(const void* memory, ATAsize size);
	}
}
#endif