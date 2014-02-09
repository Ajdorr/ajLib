#include "object.h"

void destroyObject(void* obj){
    delete (Object*)obj;
}

// helper function to render and update an object and all children
void renderAndUpdateObject(void* obj, void* inf) {
    (void)inf;
    ((Object*)obj)->renderUpdate(); // renders self then children
}

Object::Object(const char* n, Vector3 p, Vector3 s, Vector3 r):
    name(n),
    children(destroyObject),
    pos(p),
    scale(s),
    rot(r)
{
}


Object::~Object()
{
}

void Object::update() {

}

void Object::render() {

}

void Object::renderUpdate(){
    glPushMatrix();
    this->update();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rot.z, 0, 0, 1);
    glRotatef(rot.y, 0, 1, 0);
    glRotatef(rot.x, 1, 0, 0);
    glScalef(scale.x, scale.y, scale.z);

    this->render(); // render self

    children.execAll(renderAndUpdateObject, NULL);
    glPopMatrix();
}


void Object::rotateAround(Vector3 point, Vector3 axis, float angle)
{
    glTranslatef(point.x, point.y, point.z);
    glRotatef(angle, axis.x, axis.y, axis.z);
    glTranslatef(-point.x, -point.y, -point.z);
}

int Object::attachChild(Object* obj) {
    return children.insert(obj->name.c_str(),
                           obj->name.length(),
                           obj);
}


const char* Object::getName()
{
    return name.c_str();
}


unsigned int Object::getNameLen()
{
    return name.length();
}
