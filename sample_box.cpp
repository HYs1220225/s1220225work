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
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"

using namespace std;
using namespace openvdb;
using namespace tbb;

openvdb::util::CpuTimer t;

int main(){
  string model("box");
  int n;
  Fbox f;
  openvdb::initialize();

  float backgroundValue = 1000.0f;
  float offset = -0.05; // -0.025 -> -0.05
  
  // Create an empty floating-point grid
  
  t.start();
  tick_count t0 = tick_count::now();
  
  openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create(backgroundValue);
  CoordBBox indexBB(Coord(-20,-20,-20), Coord(140,60,60));
  f.create(grid, indexBB, 0.025f);
  
  tick_count t1 = tick_count::now();
  t.stop();
  cout << "time for action = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
  
  //  save 0 level set object -> .off
  
  cout << "Please select the operation" << endl;
  cout << "0) quit" << endl;
  cout << "1) make original model (run original() function)" << endl;
  cout << "2) run computeoffset()" << endl;
  cout << "3) run useoffset()" << endl;
  cout << "4) run Rounding_computeoffset()" << endl;
  cout << "5) run Rounding_useoffset()" << endl;
  cout << "6) run Filleting_computeoffset()" << endl;
  cout << "7) run Filleting_useoffset()" << endl;
  cout << "8) run Smoothing_computeoffset()" << endl;
  cout << "9) run Smoothing_useoffset()" << endl;
  cout << "input number 0 ~ 9 -> ";
  cin >> n;

  switch(n){
  case 0:
    cout << "quit" << endl;
    break;
  case 1:
    f.original(grid, model);
    break;
  case 2:
    f.computeoffset(grid, offset, model);
    break;
  case 3:
    f.useoffset(grid, offset, model);
    break;
  case 4:
    f.Rounding_computeoffset(grid, offset, model);
    break;
  case 5:
    f.Rounding_useoffset(grid, offset, model);
    break;
  case 6:
    f.Filleting_computeoffset(grid, offset, model);
    break;
  case 7:
    f.Filleting_useoffset(grid, offset, model);
    break;
  case 8:
    f.Smoothing_computeoffset(grid, offset, model);
    break;
  case 9:
    f.Smoothing_useoffset(grid, offset, model);
    break;
  default:
    cout << "Please input number 0 ~ 9" << endl;
    break;
  }
  
  return 0;
}


