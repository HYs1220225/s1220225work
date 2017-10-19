#include <cmath>
#include "hfprimitives.h"

double hfBlock(double x, double y, double z, double cx, double cy, double cz, double lx, double ly, double lz){
  double xt, yt, zt, f;
  xt = (x-cx)*(cx+lx-x);
  yt = (y-cy)*(cy+ly-y);
  zt = (z-cz)*(cz+lz-z);
  f = xt + yt - sqrt(xt*xt + yt*yt);
  f = f + zt - sqrt(f*f + zt*zt);
  return f;
}
