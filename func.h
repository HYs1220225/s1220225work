#ifndef _FUNC_H_
#define _FUNC_H_

#include <openvdb/openvdb.h>
#include <vector>
using namespace std;
using namespace openvdb;

void useoffset(FloatGrid::Ptr, float, int);

void computeoffset(FloatGrid::Ptr, float, int);

void test(FloatGrid::Ptr, int);

void create(FloatGrid::Ptr, const CoordBBox&, float, int);

void createOFFFile(string, vector<Vec3s>, vector<Vec4I>);


#endif
