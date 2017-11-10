#include <iostream>
#include <fstream>
#include <string>
#include <openvdb/openvdb.h>
// #include <openvdb/tools/SignedFloodFill.h>
// #include <openvdb/tools/VolumeToMesh.h>
// #include <openvdb/tools/LevelSetRebuild.h>
// #include <openvdb/tools/LevelSetFilter.h>
#include <openvdb/util/CpuTimer.h>
// #include <vector>
#include "func.h"
// #include "boxes.h"

using namespace std;
using namespace openvdb;

openvdb::util::CpuTimer t;

int main(){
  int n = 1;
  openvdb::initialize();

  float backgroundValue = 1000.0f;
  float offset = -0.025; /*box*/
  
  // Create an empty floating-point grid
  
  t.start();
  
  openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create(backgroundValue);
  CoordBBox indexBB(Coord(-20,-20,-20), Coord(140,60,60)); /*box*/
  create(grid, indexBB, 0.025f/*box*/, n);
  
  t.stop();
  
  //  save 0 level set object -> .off
  test(grid, n);

  
  //  computeoffset(grid, offset);
  //  useoffset(grid, offset);
  
  return 0;
}


