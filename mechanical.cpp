#include <cmath>
#include "hfoperations.h"
#include "hfprimitives.h"

double eval(double x, double y,  double z){
  double xyz[3], cyl45, cyl44, sub46, cyl52, cyl54, c0, c1, c2, box61, box62, box58, sub55, scale, box47, my_model;
  //  double xt, yt, zt;

  xyz[0] = x;                          // xt = x;
  xyz[1] = y;                          // yt = y;
  xyz[2] = z;                          // zt = z;

  hfShift3D(xyz, 0, 0, 2.5);  // (xt, yt, zt) = hfShift3D(xt, yt, zt, 0, 0, 2.5);
  hfRotate3DX(xyz, M_PI);     // (xt, yt, zt) = hfRotate3DX(xt, yt, zt, M_PI);

  cyl45 = 1 - xyz[0]*xyz[0]/16.0 - xyz[1]*xyz[1]/16.0;
  //  cyl45 = hfInt(cyl45, (-(xyz[2]*xyz[2]-25.0/4.0)));
  cyl44 = 1 - xyz[0]*xyz[0]/25.0 - xyz[1]*xyz[1]/25.0;
  cyl44 = hfInt(cyl44, (-(xyz[2]*xyz[2]-25.0/4.0)));
  sub46 = hfSub(cyl44, cyl45);

  xyz[0] = x;
  xyz[1] = y;
  xyz[2] = z; 

  hfShift3D(xyz, 28.0, 0.0, 2.5);
  hfRotate3DY(xyz, -M_PI);
  cyl52 = (1 - xyz[0]*xyz[0]/25.0 - xyz[1]*xyz[1]/25.0);
  cyl52 = hfInt(cyl52, (-(xyz[2]*xyz[2]-25.0/4.0)));
  cyl54 = (1 - xyz[0]*xyz[0]/9.0 - xyz[1]*xyz[1]/9.0);
  //  cyl54 = hfInt(cyl54, (-(xyz[2]*xyz[2]-25.0/4.0)));


  c0 = 27.0;
  c1 = 3.0;
  c2 = 0.0;
  box61 = hfBlock(x, y, z, c0, c1, c2, 1.0, 4.0, 5.0);
  c0 = 27.0 ;
  c1 = -7.0 ;
  c2 = 0.0;
  box62 = hfBlock(x, y, z, c0, c1, c2, 1.0, 4.0, 5.0);
  c0 = 28.0;
  c1 = -10.0 ;
  c2 = -1.0;
  box58 = hfBlock(x, y, z, c0, c1, c2, 7.0, 20.0, 7.0);
  sub55 = hfSub(cyl52, cyl54);
  sub55 = hfSub(sub55, box58);
  sub55 = hfUni(sub55, box61);
  sub55 = hfUni(sub55, box62);

  xyz[0] = x;
  xyz[1] = y;
  xyz[2] = z;

  if(xyz[0] < 4)scale = 1.0;
  else if(xyz[0] > 25)scale = 2.0;
  else scale = (xyz[0]-4)/21.0 + 1.0;

  xyz[1] = xyz[1] / scale;

  c0 = 4.5;
  c1 = -2.0;
  c2 = 1.0;

  box47 = hfBlock(xyz[0], xyz[1], xyz[2], c0, c1, c2, 21.0, 4.0, 3.0);
  my_model = hfUni(box47, sub46);
  my_model = hfUni(my_model, sub55);

  return my_model;
}
