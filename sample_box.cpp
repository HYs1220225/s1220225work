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
// #include "func.h"
#include "Fbox.h"
// #include "boxes.h"

using namespace std;
using namespace openvdb;

openvdb::util::CpuTimer t;

int main(){
  string model("box");
  Fbox f;
  openvdb::initialize();

  float backgroundValue = 1000.0f;
  float offset = -0.025; /*box*/
  
  // Create an empty floating-point grid
  
  t.start();
  
  openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create(backgroundValue);
  CoordBBox indexBB(Coord(-20,-20,-20), Coord(140,60,60)); /*box*/
  f.create(grid, indexBB, 0.025f/*box*/);
  
  t.stop();
  
  //  save 0 level set object -> .off
  f.test(grid, model);

  
  //  f.computeoffset(grid, offset, model);
  //  f.useoffset(grid, offset, model);
  //  f.Rounding(grid, offset, model);
  //  f.Filleting(grid, offset, model);
  f.Smoothing(grid, offset, model);
  
  return 0;
}


