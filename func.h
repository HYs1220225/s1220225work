#ifndef _FUNC_H_
#define _FUNC_H_

#include <openvdb/openvdb.h>
#include <string>
/* #include <vector> */

/* using namespace std; */
/* using namespace openvdb; */
class Func{
 public:
  void useoffset(openvdb::FloatGrid::Ptr, float, int);

  void computeoffset(openvdb::FloatGrid::Ptr, float, int);

  void test(openvdb::FloatGrid::Ptr, int);

  void create(openvdb::FloatGrid::Ptr, const openvdb::CoordBBox&, float, int);

  void createOFFFile(std::string, std::vector<openvdb::Vec3s>, std::vector<openvdb::Vec4I>);
};


#endif
