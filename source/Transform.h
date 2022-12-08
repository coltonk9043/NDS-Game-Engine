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