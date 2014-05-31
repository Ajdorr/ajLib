#ifndef COLOR_H
#define COLOR_H

#include <GL/gl.h>

#include "ajmath/ajmath.h"

class Material
{
private:

public:
    float r, b, g;
    float ambi[4]; // ambient
    float diff[4]; // diffuse
    float spec[4]; // specular
    float emis[4]; // emission

    static Material Crimson;
    static Material Red;
    static Material Pink;
    static Material Orchid;
    static Material Indigo;
    static Material Blue;
    static Material Cobalt;
    static Material RoyalBlue;
    static Material LightSteelBlue;
    static Material Green;
    static Material Black;
    static Material White;

    Material();
    Material(float red, float blue, float green);
    Material(Vector3&);
    Material(Vector3);

    // void diffFactor(float);
    void specFactor(float);

    void applyMaterial();
    void applyColor();
};


#endif // COLOR_H
