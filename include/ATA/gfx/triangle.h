#ifndef ATA_TRIANGLE_H
#define ATA_TRIANGLE_H

namespace ata
{
	class Triangle // : public Drawable
	{
		public:
			Triangle();
			~Triangle();


			ata::vec3f surfaceNormal();

		private:
			ata::Vertex3D m_vertices[3];
	}
}

#endif