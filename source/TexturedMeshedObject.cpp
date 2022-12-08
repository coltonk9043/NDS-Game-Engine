#include "GameObject.h"

// Constructor for a MeshedObject.
TexturedMeshedObject::TexturedMeshedObject(Vector3 position, Vector3 rotation, Vector3 scale, Mesh mesh, int textureID) : GameObject(position, rotation, scale){
    this->mesh = mesh;
    this->textureID = textureID;
}

// Deconstructor for a MeshedObject.
TexturedMeshedObject::~TexturedMeshedObject(){}

// Generic Update for a ColouredObject.
void TexturedMeshedObject::UpdateEntity(u16 keysHeld) {}

// Draws the MeshedObject
void TexturedMeshedObject::DrawEntity(){
    // Gets the mesh data.
    v16* vertices = this->mesh.getVertices();
    u8* quads = this->mesh.getQuads();
    u32* uv = this->mesh.getUV();
    u32* normals = this->mesh.getNormals();

    // Binds the texture to OpenGL.
    glBindTexture(0, textureID);

    // For every polygon in the mesh, draw it.
    for(int i = 0; i < this->mesh.polygons; i++){
        if(Counter::Mesh::polygons >= 4000) return;

        // Gets the vertices of the quad.
        u32 f1 = quads[i * 4] ;
	    u32 f2 = quads[i * 4 + 1] ;
	    u32 f3 = quads[i * 4 + 2] ;
	    u32 f4 = quads[i * 4 + 3] ;

        // OpenGL draw quad.
        glBegin(GL_QUADS);
        glNormal(normals[i]);

        GFX_TEX_COORD = (uv[0]);
	    glVertex3v16(vertices[f1*3], vertices[f1*3 + 1], vertices[f1*3 +  2] );
	
	    GFX_TEX_COORD = (uv[1]);
	    glVertex3v16(vertices[f2*3], vertices[f2*3 + 1], vertices[f2*3 + 2] );
	
	    GFX_TEX_COORD = (uv[2]);
	    glVertex3v16(vertices[f3*3], vertices[f3*3 + 1], vertices[f3*3 + 2] );

	    GFX_TEX_COORD = (uv[3]);
	    glVertex3v16(vertices[f4*3], vertices[f4*3 + 1], vertices[f4*3 + 2] );
        glEnd();
        
        Counter::Mesh::polygons += 2;
        Counter::Mesh::vertices += 4;
    }
}   