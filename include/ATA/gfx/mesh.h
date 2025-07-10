#ifndef ATA_MESH_H
#define ATA_MESH_H

namespace ata
{
        class Mesh // : public Drawable, public GLResource
        {
                public:
                        Mesh();
                        ~Mesh();

			void addTriangle(const ata::vec3f& a, const ata::vec3f& b, const ata::vec3f& c);

        };
}
#endif