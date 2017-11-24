#include <iostream>
#include <fstream>
#include <string>
#include "func.h"
#include <openvdb/openvdb.h>
// #include <openvdb/tools/SignedFloodFill.h>
// #include <openvdb/tools/VolumeToMesh.h>
// #include <openvdb/tools/LevelSetRebuild.h>
// #include <openvdb/tools/LevelSetFilter.h>
#include <openvdb/util/CpuTimer.h>
// #include <vector>
//#include "mechanical.h"

using namespace std;
using namespace openvdb;

openvdb::util::CpuTimer t;

int main(){
  int n = 0;
  Func f;
  openvdb::initialize();

  float backgroundValue = 1000.0f;
  float offset = -0.15;
  
  // Create an empty floating-point grid
  
  t.start();
  
  openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create(backgroundValue);
  CoordBBox indexBB(Coord(-70,-80,-20), Coord(300,80,70));
  f.create(grid, indexBB, 0.1f, n);
  
  t.stop();
  
  //  save 0 level set object -> .off
  //  f.test(grid, n);
  
  
    f.computeoffset(grid, offset, n);
  //  f.useoffset(grid, offset);
  
  return 0;
}
