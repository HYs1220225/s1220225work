#ifndef _FBOX_H_
#define _FBOX_H_

#include <openvdb/openvdb.h>
#include <string>
#include "func.h"
/* #include <vector> */

/* using namespace std; */
/* using namespace openvdb; */
class Fbox : public Func{
 public:
  virtual void create(openvdb::FloatGrid::Ptr, const openvdb::CoordBBox&, float);
};

#endif
