#include "Vector3.h"

// Default constructor for a Vector.
Vector3::Vector3(){
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

// Constructor for a Vector with 3 coordinates.
Vector3::Vector3(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

// Sets the Vector's coordinates.
void Vector3::Set(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

// Sets the Vector equal to another Vector.
void Vector3::Set(Vector3 vector){
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
}

// Translates a vector by it's x, y, and z.
void Vector3::Translate(float x, float y, float z){
    this->x += x;
    this->y += y;
    this->z += z;
}

// Normalizes the Vector (does not return the normalized Vector)
void Vector3::Normalize(){
    float32 magnitude = this->Magnitude();
    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

// Returns the Magnitude of the vector.
float32 Vector3::Magnitude(){
    float32 x1 = (this->x > 0) ? this->x: -this->x;
    float32 y1 = (this->y > 0) ? this->y: -this->y; 
    float32 z1 = (this->z > 0) ? this->z: -this->z;
    return f32tofloat(sqrtf32(floattof32(x1*x1 + y1*y1 + z1*z1)));
}

// Returns the cross product of this and another Vector.
Vector3 Vector3::Cross(Vector3 vector){
    Vector3 product {this->y*vector.z - this->z*vector.y, this->z*vector.x - this->x*vector.z, this->x*vector.y - this->y*vector.x};
    return product;
}

// Returns a Normalized representation of this Vector.
Vector3 Vector3::Normalized(){
    float magnitude = this->Magnitude();
    return Vector3{this->x / magnitude, this->y / magnitude, this->z / magnitude};
}

// Overloads the addition operator. Adds each element by another vector's element.
Vector3 Vector3::operator+(const Vector3& v){
    Vector3 vec;
    vec.x = this->x + v.x;
    vec.y = this->y + v.y;
    vec.z = this->z + v.z;
    return vec;
}

// Overloads the subtraction operator. Subtracts each element by another vector's element.
Vector3 Vector3::operator-(const Vector3& v){
    Vector3 vec;
    vec.x = this->x - v.x;
    vec.y = this->y - v.y;
    vec.z = this->z - v.z;
    return vec;
}

// Overloads the multiplication operator. Multiplied each element by a constant.
Vector3 Vector3::operator*(float multiplier){
    Vector3 vec;
    vec.x = this->x * multiplier;
    vec.y = this->y * multiplier;
    vec.z = this->z * multiplier;
    return vec;
}

// Overloads the division operator. Divides each element by a constant.
Vector3 Vector3::operator/(float division){
    Vector3 vec;
    vec.x = this->x / division;
    vec.y = this->y / division;
    vec.z = this->z / division;
    return vec;
}