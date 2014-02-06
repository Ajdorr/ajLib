#include "object.h"

void destroyObject(void* obj){
    delete (Object*)obj;
}

// helper function to render and update an object and all children
void renderAndUpdateObject(void* obj, void* inf) {
    // TODO
    (void)inf;
    // renderself
    // render children
    ((Object*)obj)->renderUpdate();
}

Object::Object(std::string& n):
    pos(0.0f,0.0f,0.0f),
    children(destroyObject),
    name(n)
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
        glScaled(scale.x, scale.y, scale.z);
        glTranslated(pos.x, pos.y, pos.z);
        glRotated(rot.z, 0, 0, 1);
        glRotated(rot.y, 0, 1, 0);
        glRotated(rot.x, 1, 0, 0);

        this->render();
        this->update();

        children.execAll(renderAndUpdateObject, NULL);
    glPopMatrix();
}

int Object::attachChild(Object* obj) {
    return children.insert(obj->name.c_str(),
                           obj->name.length(),
                           obj);
}
