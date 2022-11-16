/*
.. Colton Kennedy - 251 089 374 - 10/28/2022
.. A header containing definition of a Vector class
*/
#ifndef VECTOR3F_H
#define VECTOR3F_H

#include "nds/arm9/math.h"

class Vector3{
    public:
        // Variables
        float x,y,z;
        // Functions
        Vector3();
        Vector3(float x, float y, float z);
        void Set(float x, float y, float z);
        void Set(Vector3 vector);
        void Translate(float x, float y, float z);
        void Normalize();
        float Magnitude();
        Vector3 Cross(Vector3 vector);
        Vector3 Normalized();

        // Overload Functions
        Vector3 operator+(const Vector3& v);
        Vector3 operator-(const Vector3& v);
        Vector3 operator*(float multiplier);
        Vector3 operator/(float division);
        
};

#endif