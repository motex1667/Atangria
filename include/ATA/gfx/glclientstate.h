#ifndef ATA_GLCLIENTSTATE_H
#define ATA_GLCLIENTSTATE_H

namespace ata
{
	enum class GLClientState : unsigned char
	{
		ColorArray = 1,
		EdgeFlagArray = 1 << 1,
		FogCoordArray = 1 << 2,
		IndexArray = 1 << 3,
		NormalArray	= 1 << 4,
		SecondaryColorArray = 1 << 5,
		TextureCoordArray = 1 << 6,
		VertexArray = 1 << 7
	};
}

#endif