#include "material.h"

// http://cloford.com/resources/colours/500col.htm

Material Material::Crimson = Material(220.0f/255.0f, 60.0f/255.0f, 20.0f/255.0f);
Material Material::Red = Material(1, 0, 0);
Material Material::Pink = Material(1, 203.0f/255.0f, 192.0f/255.0f);
Material Material::Orchid = Material(218.0f/255.0f, 214.0f/255.0f, 112.0f/255.0f);
Material Material::Indigo = Material(75.0f/255.0f, 130.0f/255.0f, 0);
Material Material::Blue = Material(0,1,0);
Material Material::Cobalt = Material(61.0f/255.0f, 171.0f/255.0f, 89.0f/255.0f);
Material Material::RoyalBlue = Material(65.0f/255.0f, 1, 105.0f/255.0f);
Material Material::LightSteelBlue =
    Material(176.0f/255.0f, 222.0f/255.0f, 196.0f/255.0f);
Material Material::Green = Material(0, 0, 1);
Material Material::Black = Material(0,0,0);
Material Material::White = Material(1,1,1);

Material::Material()
{
  r = 0;
  b = 0;
  g = 0;
}

Material::Material(float red, float blue, float green)
{
  r = red;
  b = blue;
  g = green;

  ambi[0] = r/100;
  ambi[1] = b/100;
  ambi[2] = g/100;
  ambi[3] = 1;

  diff[0] = r;
  diff[1] = b;
  diff[2] = g;
  diff[3] = 1;

  spec[0] = r/5;
  spec[1] = b/5;
  spec[2] = g/5;
  spec[3] = 1;

  emis[0] = 0;
  emis[1] = 0;
  emis[2] = 0;
  emis[3] = 0;

}


Material::Material(Vector3& v)
{
  r = v.x();
  b = v.y();
  g = v.z();

  ambi[0] = r/100;
  ambi[1] = b/100;
  ambi[2] = g/100;
  ambi[3] = 1;

  diff[0] = r;
  diff[1] = b;
  diff[2] = g;
  diff[3] = 1;

  spec[0] = r/5;
  spec[1] = b/5;
  spec[2] = g/5;
  spec[3] = 1;

  emis[0] = 0;
  emis[1] = 0;
  emis[2] = 0;
  emis[3] = 0;


}


void Material::specFactor(float f)
{
  spec[0] = r*f;
  spec[1] = b*f;
  spec[2] = g*f;
}

void Material::applyMaterial()
{
  glColor3f(r, g, b);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  // glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
}

void Material::applyColor()
{
  glColor3f(r, g, b);
}
