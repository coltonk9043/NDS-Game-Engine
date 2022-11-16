/*
* Class containing all of the class definitions of different GameObjects
*/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <nds.h>
#include <nds/arm9/trig_lut.h>
#include "Transform.h"
#include "Mesh.h"
#include <nds/arm9/boxtest.h>
#include <list>
#include "Common.h"

class GameObject{
    public:
        GameObject(Vector3 position, Vector3 rotation, Vector3 scale);
        virtual ~GameObject();
        void Update(u16 keysHeld);
        void Draw();
        void SetActive(bool active);
        void SetVelocity(float x, float y, float z);
        void SetVelocity(Vector3 vector);
        void addChild(GameObject* transform);
        void removeChild(GameObject* transform);
        Vector3* GetVelocity();
        Transform* GetTransform();
        GameObject* parent;
    protected:
        Transform transform;
        Vector3 velocity;
        Vector3 force;
        Vector3 boundingBox;
        float mass;
        std::list<GameObject*> children;
        bool active = true;
        virtual void UpdateEntity(u16 keysHeld);
        virtual void DrawEntity();
};

class TexturedMeshedObject : public GameObject{
    public:
        TexturedMeshedObject(Vector3 position, Vector3 rotation, Vector3 scale, Mesh mesh, int textureID);
        ~TexturedMeshedObject();
    protected:
        void UpdateEntity(u16 keysHeld) override;
        void DrawEntity() override;
        int textureID;
        Mesh mesh;
};

class ColouredMeshedObject : public GameObject{
    public:
        ColouredMeshedObject(Vector3 position, Vector3 rotation, Vector3 scale, Mesh mesh, Vector3 color);
        ~ColouredMeshedObject();
    protected:
        void UpdateEntity(u16 keysHeld) override;
        void DrawEntity() override;
        Vector3 colour;
        Mesh mesh;
};

class Camera : public GameObject{
    public:
        Camera(Vector3 position, Vector3 rotation, Vector3 scale);
        ~Camera();
        void applyViewingTransformation();
    private:
        void UpdateEntity(u16 keysHeld) override;
        void DrawEntity() override;
        void UpdateCameraMatrix();
        bool matrixUpdated = false;
};



#endif