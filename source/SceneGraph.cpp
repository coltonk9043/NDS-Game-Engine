#include "SceneGraph.h"

// Constructor for a Scene graph. Requires a root GameObject.
SceneGraph::SceneGraph(GameObject* root){
    this->root = root;
}

// Deconstructor for a Scene Graph.
SceneGraph::~SceneGraph(){

}

// Adds an object to the scene given a parent.
void SceneGraph::addObject(GameObject* parent, GameObject* child){
    parent->addChild(child);
    numObjects++;
}

// Removes an Object from the scene graph.
void SceneGraph::removeObject(GameObject* obj){
    obj->parent->removeChild(obj);
    delete obj;
    numObjects--;
}

// Transforms a specific object by x, y, z coordinates.
void SceneGraph::transformObject(GameObject* obj, float x, float y, float z){
    obj->GetTransform()->position.Translate(x,y,z);
}

// Rotates a specific object by yaw, pitch, roll coordinates.
void SceneGraph::rotateObject(GameObject* obj, float rx, float ry, float rz){
    obj->GetTransform()->rotation.Translate(rx,ry,rz);
}

// Scales a specific object by x, y, z coordinates.
void SceneGraph::scaleObject(GameObject* obj, float sx, float sy, float sz){
    obj->GetTransform()->scale.Translate(sx,sy,sz);
}

// Updates the entire SceneGraph and all of its children.
void SceneGraph::Update(u16 keysHeld){
    root->Update(keysHeld);
}

// Draws the entire SceneGraph and all of its children.
void SceneGraph::Draw(){
    root->Draw();
}

int SceneGraph::getNumberOfObjects(){
    return this->numObjects;
}