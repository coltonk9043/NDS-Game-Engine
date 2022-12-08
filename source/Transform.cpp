#include "Transform.h"

// Default constructor for a Transform.
Transform::Transform(){
    this->position.Set(0,0,0);
    this->scale.Set(1,1,1);
    this->front.Set(0,0,1);
}

// Constructor for a Transform with 3 coordinates.
Transform::Transform(float x, float y, float z){
    this->position.Set(x,y,z);
    this->scale.Set(1,1,1);
    this->front.Set(0,0,1);
}

// Constructor for a Transform given 3 Vectors (pos, rot, scale)
Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale){
    this->position.Set(position);
    this->rotation.Set(rotation);
    this->scale.Set(scale);
    this->front.Set(0,0,1);
}

// Deconstructor for a transform.
Transform::~Transform(){
    
}

