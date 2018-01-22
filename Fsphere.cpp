#include <iostream>
#include <fstream>
#include <string>
#include <openvdb/openvdb.h>
#include <openvdb/tools/SignedFloodFill.h>
#include <openvdb/tools/VolumeToMesh.h>
#include <openvdb/tools/LevelSetRebuild.h>
#include <openvdb/tools/LevelSetFilter.h>
// #include <openvdb/util/CpuTimer.h>
// #include <vector>
#include "Fsphere.h"
// #include "boxes.h"

using namespace std;
using namespace openvdb;
// using openvdb::tools::LevelSetFilter;


void Fsph::create(FloatGrid::Ptr grid, const CoordBBox& indexBB, float h){
  typename FloatGrid::Accessor accessor = grid->getAccessor();
  // float distance;
  // cout << "run sphere" << endl;
  
  // for (Int32 i = indexBB.min().x(); i <= indexBB.max().x(); ++i) {
  //   for (Int32 j = indexBB.min().y(); j <= indexBB.max().y(); ++j) {
  //     for (Int32 k = indexBB.min().z(); k <= indexBB.max().z(); ++k) {
  // 	// transform point (i,j,k) of index space into world space
  // 	// assume that hx=hy=hz=h (each cell is a cube)
  // 	Vec3f p(i*h, j*h, k*h);

  // 	// compute level set function value
  // 	// note the convention: negative inside / positive outside

  // 	//	distance = -eval(p.x(), p.y(), p.z());

  // 	// set the value in the grid
  // 	accessor.setValue(Coord(i,j,k), distance);
  //     }
  //   }
  // }

  // // In order to use the grid further, we need to associate a scaling transform
  // // to this grid from voxel in index space to voxel in world space
  // grid->setTransform(openvdb::math::Transform::createLinearTransform(h));
}
