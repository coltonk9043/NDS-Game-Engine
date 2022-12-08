#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "nds.h"
#include "GameObject.h"

class SceneGraph{
    public:
        SceneGraph(GameObject* root);
        ~SceneGraph();
        void addObject(GameObject* parent, GameObject* child);
        void transformObject(GameObject* child, float x, float y, float z);
        void rotateObject(GameObject* child, float rx, float ry, float rz);
        void scaleObject(GameObject* child, float sx, float sy, float sz);
        void removeObject(GameObject* child);
        void Update(u16 keysHeld);
        void Draw();
        int getNumberOfObjects();
    private:
        GameObject* root;
        int numObjects;
};

#endif