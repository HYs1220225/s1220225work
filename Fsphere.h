#ifndef _FMECHANICAL_H_
#define _FMECHANICAL_H_

#include <openvdb/openvdb.h>
#include <string>
#include "func.h"
/* #include <vector> */

/* using namespace std; */
/* using namespace openvdb; */
class Fsph : public Func{
 public:
  virtual void create(openvdb::FloatGrid::Ptr, const openvdb::CoordBBox&, float);
};

#endif
