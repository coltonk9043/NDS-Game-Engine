#include "Mesh.h"

// Default Constructor for a Mesh
Mesh::Mesh(){

}

// Constructor for a mesh given Mesh data. 
Mesh::Mesh(v16 verts[], u8 quads[], u32 uv[], u32 norms[], int polygons){
    this->vertices = verts;
    this->quads = quads;
    this->uv = uv;
    this->normals = norms;
    this->polygons = polygons;
}

// Setters for the verts, quads, uv, and norms.
void Mesh::setVertices(v16 verts[]){ this->vertices = verts; }
void Mesh::setQuads(u8 quads[]){ this->quads = quads; }
void Mesh::setUV(u32 uv[]){ this->uv = uv; }
void Mesh::setNormals(u32 norms[]){ this->normals = norms; };

// Getters for the verts, quads, uv, and norms.
v16* Mesh::getVertices() { return this->vertices; }
u8* Mesh::getQuads(){ return this->quads; }
u32* Mesh::getUV(){ return this->uv; }
u32* Mesh::getNormals(){ return this->normals; }