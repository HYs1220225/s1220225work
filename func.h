#ifndef _FUNC_H_
#define _FUNC_H_

#include <openvdb/openvdb.h>
#include <string>
/* #include <vector> */

/* using namespace std; */
/* using namespace openvdb; */
class Func{
 public:
  void useoffset(openvdb::FloatGrid::Ptr, float, std::string);

  void computeoffset(openvdb::FloatGrid::Ptr, float, std::string);

  void test(openvdb::FloatGrid::Ptr, std::string);

  virtual void create(openvdb::FloatGrid::Ptr, const openvdb::CoordBBox&, float) = 0;

  void createOFFFile(std::string, std::vector<openvdb::Vec3s>, std::vector<openvdb::Vec4I>);

  void Rounding(openvdb::FloatGrid::Ptr, float, std::string);
  
  void Filleting(openvdb::FloatGrid::Ptr, float, std::string);
  
  void Smoothing(openvdb::FloatGrid::Ptr, float, std::string);
};

#endif
