#include <cmath>
#include "hfoperations.h"

double hfUni(double f1, double f2){
  return f1 + f2 + sqrt(f1*f1 + f2*f2);
}

double hfInt(double f1, double f2){
  return f1 + f2 - sqrt(f1*f1 + f2*f2);
}

void hfRotate3DX(double *xyzt, double angle){
  double yc, zc, ct, st;
  // xyzt[0] = xt
  // xyzt[1] = yt
  // xyzt[2] = zt
  // xt unchanged
  yc = xyzt[1];
  zc = xyzt[2];

  ct = cos(angle);
  st = sin(angle);

  xyzt[1] = yc*ct + zc*st;
  xyzt[2] = -yc*st + zc*ct;
}

void hfRotate3DY(double *xyzt, double angle){
  double xc, zc, ct, st;
  // yt unchanged
  xc = xyzt[0];
  zc = xyzt[2];

  ct = cos(angle);
  st = sin(angle);

  xyzt[2] = zc*ct + xc*st;
  xyzt[0] = -zc*st + xc*ct;
}

double hfSub(double f1, double f2){
  return f1 - f2 - sqrt(f1*f1 + f2*f2);
}

void hfShift3D(double *xyzt, double sx, double sy, double sz){
  xyzt[0] = xyzt[0] - sx;
  xyzt[1] = xyzt[1] - sy;
  xyzt[2] = xyzt[2] - sz;
}
