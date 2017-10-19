#include <cmath>
#include "boxes.h"
#include <algorithm>

double boxes_3d_is::eval(double X, double Y, double Z) {
  // box 1:
  double v1[] = {0, 0, 0};
  double len1[] = {3.0, 1.0, 1.0};
  double box1 = box(X, Y, Z, v1, len1);

  // box 2:
  double v2[] = {0.2, 0.2, 0.7};
  double len2[] = {2.6, 0.6, 1.0};
  double box2 = box(X, Y, Z, v2, len2);
  return r_int(box1, -box2);
}

double boxes_3d_is::r_uni(double f, double g)
{
  return f + g + sqrt(f*f + g*g);
  //  return std::max(f,g);
}

  
double boxes_3d_is::r_int(double f, double g)
{
  return f + g - sqrt(f*f + g*g);
  //  return std::min(f,g);
}

  
double boxes_3d_is::hf_blend_uni(double f, double g,
				 double a0, double a1, double a2)
{
  double disp = a0 / (1.0 + (f/a1)*(f/a1) + (g/a2)*(g/a2));
  return r_uni(f, g) + disp;
}


// Defines a box whose faces are orthogonal 
// to each axis of the coord. system
double boxes_3d_is::box(double X, double Y, double Z, double vert[3], double len[3])
{
  double nx[3] = {1.0, 0.0, 0.0};
  double plane1 = plane(X, Y, Z, nx, -vert[0]);

  double nx_neg[3] = {-1.0, 0.0, 0.0};
  double plane2 = plane(X, Y, Z, nx_neg, len[0] + vert[0]);

  double ny[3] = {0.0, 1.0, 0.0};
  double plane3 = plane(X, Y, Z, ny, -vert[1]);

  double ny_neg[3] = {0.0, -1.0, 0.0};
  double plane4 = plane(X, Y, Z, ny_neg, len[1] + vert[1]);

  double nz[3] = {0.0, 0.0, 1.0};
  double plane5 = plane(X, Y, Z, nz, -vert[2]);

  double nz_neg[3] = {0.0, 0.0, -1.0};
  double plane6 = plane(X, Y, Z, nz_neg, len[2] + vert[2]);

  return r_int(r_int(r_int(r_int(r_int(plane1, plane2),
				 plane3), plane4), plane5), plane6);
}

double boxes_3d_is::plane(double X, double Y, double Z, double normal[3], double d)
{
  return X*normal[0] + Y*normal[1] + Z*normal[2] + d;
}
