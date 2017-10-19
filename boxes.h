#ifndef _BOXES_H_
#define _BOXES_H_

class boxes_3d_is {
public:
  virtual double eval(double X, double Y, double Z);

private:
  double r_uni(double f, double g);
  
  double r_int(double f, double g);
  
  double hf_blend_uni(double f, double g, double a0, double a1, double a2);

  double box(double X, double Y, double Z, double vert[3], double len[3]);

  double plane(double X, double Y, double Z, double normal[3], double d);
};

#endif
