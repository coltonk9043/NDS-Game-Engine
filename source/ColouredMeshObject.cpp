/*
.. Colton Kennedy - 251 089 374 - 10/28/2022
.. A class that represents GameObject with a mesh and colour.
*/

#include "GameObject.h"

// Constructor for a coloured GameObject.
ColouredMeshedObject::ColouredMeshedObject(Vector3 position, Vector3 rotation, Vector3 scale, Mesh mesh, Vector3 colour) : GameObject(position, rotation, scale){
    this->mesh = mesh;
    this->colour = colour;
}

// Deconstructor for a coloured GameObject.
ColouredMeshedObject::~ColouredMeshedObject(){}

// Generic Update for a ColouredObject.
void ColouredMeshedObject::UpdateEntity(u16 keysHeld) {}

/*
// Draw call function
*/
void ColouredMeshedObject::DrawEntity(){
    // Gets the mesh data.
    v16* vertices = this->mesh.getVertices();
    u8* quads = this->mesh.getQuads();
    u32* normals = this->mesh.getNormals();

    // For every polygon in the mesh, draw it.
    for(int i = 0; i < this->mesh.polygons; i++){
        if(Counter::Mesh::polygons >= 4000) return;

        // Gets the vertices of the quad.
        u32 f1 = quads[i * 4] ;
	    u32 f2 = quads[i * 4 + 1] ;
	    u32 f3 = quads[i * 4 + 2] ;
	    u32 f4 = quads[i * 4 + 3] ;

        // OpenGL draw quad.
        glBegin(GL_QUAD);
        glNormal(normals[i]);

        glColor3f(colour.x, colour.y, colour.z);
	    glVertex3v16(vertices[f1*3], vertices[f1*3 + 1], vertices[f1*3 +  2] );
    
        glColor3f(colour.x, colour.y, colour.z);
	    glVertex3v16(vertices[f2*3], vertices[f2*3 + 1], vertices[f2*3 + 2] );
	
        glColor3f(colour.x, colour.y - 0.2f, colour.z);
	    glVertex3v16(vertices[f3*3], vertices[f3*3 + 1], vertices[f3*3 + 2] );

        glColor3f(colour.x, colour.y - 0.2f, colour.z);
	    glVertex3v16(vertices[f4*3], vertices[f4*3 + 1], vertices[f4*3 + 2] );

        glEnd();

        Counter::Mesh::polygons += 2;
        Counter::Mesh::vertices += 4;
    }
}   