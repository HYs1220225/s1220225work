#include <iostream>
#include <fstream>
#include <string>
#include <openvdb/openvdb.h>
// #include <openvdb/tools/SignedFloodFill.h>
// #include <openvdb/tools/VolumeToMesh.h>
// #include <openvdb/tools/LevelSetRebuild.h>
// #include <openvdb/tools/LevelSetFilter.h>
#include <openvdb/util/CpuTimer.h>
//#include "func.h"
#include "Fmechanical.h"
// #include <vector>
//#include "mechanical.h"

using namespace std;
using namespace openvdb;

openvdb::util::CpuTimer t;

int main(){
  string model("mechanical");
  Fmecha f;
  openvdb::initialize();

  float backgroundValue = 1000.0f;
  float offset = -0.90; // -0.15 -> -0.30
  
  // Create an empty floating-point grid
  
  t.start();
  
  openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create(backgroundValue);
  CoordBBox indexBB(Coord(-70,-80,-20), Coord(300,80,70));
  f.create(grid, indexBB, 0.1f);
  
  t.stop();
  
  //  save 0 level set object -> .off
  //  f.test(grid, model);
  
  
  //  f.computeoffset(grid, offset, model);
  //  f.useoffset(grid, offset, model);
  //  f.Rounding_computeoffset(grid, offset, model);
  //  f.Filleting_computeoffset(grid, offset, model);
  f.Smoothing_computeoffset(grid, offset, model);
  //  f.Rounding_useoffset(grid, offset, model);
  //  f.Filleting_useoffset(grid, offset, model);
  //  f.Smoothing_useoffset(grid, offset, model);
  
  
  return 0;
}
