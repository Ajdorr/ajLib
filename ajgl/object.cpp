#include "object.h"

void destroyObject(void*){
    // delete (Object*)obj;
}

// helper function to render and update an object and all children
void renderAndUpdateObject(void* obj, void* inf) {
    (void)inf;
    ((Object*)obj)->display(); // renders self then children
}

Object::Object(const char* n, const Vector3 &p,
               const Vector3 &r, const Vector3 &s):
    name(n),
    children(destroyObject),
    pos(p),
    scale(s),
    rot(r)
{
  mat = NULL;
}


Object::~Object()
{
}

void Object::update() {}
void Object::render() {}

void Object::display(){
    glPushMatrix();

    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(rot[2], 0, 0, 1);
    glRotatef(rot[1], 0, 1, 0);
    glRotatef(rot[0], 1, 0, 0);
    glScalef(scale[0], scale[1], scale[2]);

    if (mat != NULL) mat->applyMaterial();

    this->update();
    this->render(); // render self

    children.execAll(renderAndUpdateObject, NULL);

    glPopMatrix();
}


void Object::rotateAround(const Vector3 &point, const Vector3 &axis,
                          const float angle)
{
    glTranslatef(point.x(), point.y(), point.z());
    glRotatef(angle, axis.x(), axis.y(), axis.z());
    glTranslatef(-point.x(), -point.y(), -point.z());
}

int Object::attachChild(Object* obj) {
    return children.insert(obj->name.c_str(),
                           obj->name.length(),
                           obj);
}


void Object::attachMaterial(Material* m) {
    mat = m;
}


const char* Object::getName()
{
    return name.c_str();
}


unsigned int Object::getNameLen()
{
    return name.length();
}
