/*
.. Colton Kennedy - 251 089 374 - 10/28/2022
.. A class that represents a Camera.
*/
#include "GameObject.h"

// Empty constructors for camera.
Camera::Camera(Vector3 position, Vector3 rotation, Vector3 scale) : GameObject(position, rotation, scale){}
Camera::~Camera(){}

// Applies the view transformation based on the cameras position and angle.
void Camera::applyViewingTransformation(){
    Vector3 forward = this->transform.position + this->transform.front;
    gluLookAt(  this->transform.position.x,     this->transform.position.y,     this->transform.position.z,
	    	    forward.x,                      forward.y,                      forward.z,	
				0,                              1,                              0);
}

void Camera::UpdateEntity(u16 keysHeld){
    // If the viewing matrix is out of date, recalculate it.
    if(!matrixUpdated) UpdateCameraMatrix();

    // Camera Update
	this->SetVelocity(0,0,0);

    // If any of the keys are held, transform and rotate the camera.
    if((keysHeld & KEY_A)){
        this->SetVelocity(this->transform.front * 2.0f);
        matrixUpdated = false;
    }
	if((keysHeld & KEY_B)) {
        this->SetVelocity(this->transform.front * -2.0f);
        matrixUpdated = false;
    }
	if((keysHeld & KEY_LEFT)){
        this->transform.rotation.x -= 2.0f;
        matrixUpdated = false;
    } 
	else if((keysHeld & KEY_RIGHT)){
        this->transform.rotation.x += 2.0f;
        matrixUpdated = false;
    } 
	else if((keysHeld & KEY_UP)){
        this->transform.rotation.y += 2.0f;
        matrixUpdated = false;
    } 
	else if((keysHeld & KEY_DOWN)){
        this->transform.rotation.y -= 2.0f;
        matrixUpdated = false;
    } 
    // Ensures the camera doesn't flip when yaw and pitch are too high.
    if(this->transform.rotation.y > 85.0f) this->transform.rotation.y = 85.0f;
    if(this->transform.rotation.y < -85.0f) this->transform.rotation.y = -85.0f;
}

void Camera::UpdateCameraMatrix(){
    // Updates camera rotation based off of pitch, roll, and yaw.
    Vector3 rotation = this->transform.rotation;
    s16 yaw = degreesToAngle(rotation.x);
    s16 pitch = degreesToAngle(rotation.y);

    // Calculates the new 'forward' vector of the camera using its rotation values.
    Vector3 forward;
    s16 cosPitch = cosLerp(pitch);
    forward.x = fixedToFloat(cosLerp(yaw) * cosPitch, 16);
    forward.y = fixedToFloat(sinLerp(pitch) * cosLerp(0), 16);
    forward.z = fixedToFloat(sinLerp(yaw)*cosPitch, 16);

    // Normalizes the forward vector.
    forward.Normalize();

    // Set the forward transform.
    this->transform.front.Set(forward);
    matrixUpdated = true;
}

void Camera::DrawEntity(){}