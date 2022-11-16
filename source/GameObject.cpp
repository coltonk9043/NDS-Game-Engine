/*
.. Colton Kennedy - 251 089 374 - 10/28/2022
.. A class that represents a generic GameObject.
*/

#include "GameObject.h"

// Constructor for a GameObject
GameObject::GameObject(Vector3 position, Vector3 rotation, Vector3 scale){
    transform.position.Set(position);
    transform.rotation.Set(rotation);
    transform.scale.Set(scale);
    boundingBox.Set(scale);
    force.Set(0,0,0);
    mass = 1.0f;
}

// Deconstructor for a GameObject
GameObject::~GameObject(){
}

// Sets the GameObject to the parameter.
void GameObject::SetActive(bool active){
    this->active = active;
}

// A generic update that applies to every GameObject.
void GameObject::Update(u16 keysHeld){
    // Restrains the rotation to not exceed a range of -360 to 360
    if(this->transform.rotation.x >= 360) this->transform.rotation.x = 0;
    if(this->transform.rotation.y >= 360) this->transform.rotation.y = 0;
    if(this->transform.rotation.z >= 360) this->transform.rotation.z = 0;
    if(this->transform.rotation.x <= -360) this->transform.rotation.x = 0;
    if(this->transform.rotation.y <= -360) this->transform.rotation.y = 0;
    if(this->transform.rotation.z <= -360) this->transform.rotation.z = 0;

    // Calls a virtual Update function (allows for individual updates per class while retaining generic properties.)
    this->UpdateEntity(keysHeld);

    // Recalculates the velocity based off of the force applied to the object.
    this->velocity = this->velocity + (this->force / this->mass);

    // Moves the object based off of that velocity.
    this->transform.position = this->transform.position + (this->velocity / 60.0f);

    // Resets the net force at the end.
    force.Set(0,0,0);

    // For every child of the object, update it as well.
    for(GameObject* go : this->children){
        go->Update(keysHeld);
	}

    // Performs a box test per update in order to determine whether or not to render the entity during the draw call.
    int i = BoxTestf(this->transform.position.x, this->transform.position.y, this->transform.position.z, boundingBox.x, boundingBox.y, boundingBox.z);
    this->active = i>0;
}

// Virtual Functions
void GameObject::UpdateEntity(u16 keysHeld){}
void GameObject::DrawEntity(){}

// Draw Call function that performs generic transformations that apply to all GameObjects.
void GameObject::Draw(){
    // If this is active,
    if(this->active){
        // Push a new matrix onto the stack.
        glPushMatrix();
        
        // Transform the object by it's position, rotation, and scale.
        Vector3 position = this->transform.position;
        Vector3 scale = this->transform.scale;
        glTranslatef(position.x, position.y, position.z);
        glRotateX(this->transform.rotation.x);
	    glRotateY(this->transform.rotation.y);
        glRotateZ(this->transform.rotation.z);
        glScalef(scale.x, scale.y, scale.z);
    
        // Draws the Entity (virtual, based on type)
        DrawEntity();

        // For every child of the object, draw it.
        for(GameObject* go : this->children){
            go->Draw();
	    }

        // Pop the matrix off of the stack.
        glPopMatrix(1);
    }
}

// Sets the velocity of the GameObject based on 3 floats.
void GameObject::SetVelocity(float x, float y, float z){
    this->velocity.x = x;
    this->velocity.y = y;
    this->velocity.z = z;
}

// Sets the velocity of the GameObject based on a Vector.
void GameObject::SetVelocity(Vector3 vector){ 
    this->velocity.Set(vector);
}

// Returns the Velocity of the GameObject as reference.
Vector3* GameObject::GetVelocity(){
    return &velocity;
}

// Returns the Transform of the GameObject as reference.
Transform* GameObject::GetTransform(){
    return &transform;
}

// Adds a child to the GameObject
void GameObject::addChild(GameObject* transform){
    // Pushes the child to the back of the list.
    this->children.push_back(transform);

    // Recalculates this GameObject's bounding box (for BoxTest)
    // Could be improved but it does work...
    Vector3 difference = this->transform.position - transform->transform.position;
    this->boundingBox.x += difference.x >= 0 ? difference.x : -difference.x;
    this->boundingBox.y += difference.y >= 0 ? difference.y : -difference.y;
    this->boundingBox.z += difference.z >= 0 ? difference.z : -difference.z;
}

void GameObject::removeChild(GameObject* transform){
}