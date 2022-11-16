/*
.. Colton Kennedy - 251 089 374 - 10/28/2022
.. A header containing definition of a Transform class
*/
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "nds.h"
#include "Vector3.h"
class Transform{
    public:
        Transform();
        Transform(float x, float y, float z);
        Transform(Vector3 position, Vector3 rotation, Vector3 scale);
        ~Transform();
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;
        Vector3 front; 
};

#endif