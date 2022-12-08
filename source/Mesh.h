#ifndef MESH_H
#define MESH_H

#include <nds.h>

class Mesh{
    public:
        Mesh();
        Mesh(v16 verts[], u8 quads[], u32 uv[], u32 norms[], int polygons);
        void setVertices(v16 verts[]);
        void setQuads(u8 quads[]);
        void setUV(u32 uv[]);
        void setNormals(u32 norms[]);
        v16* getVertices();
        u8* getQuads();
        u32* getUV();
        u32* getNormals();
        int polygons = 0;
    private:
        v16* vertices;
        u8* quads;
        u32* uv;
        u32* normals;     
};

#endif