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
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"

using namespace std;
using namespace openvdb;
using namespace tbb;

openvdb::util::CpuTimer t;

int main(){
  string model("mechanical");
  int n;
  Fmecha f;
  int nthreads = 1;      // task_scheduler_init::default_num_threads();
  cout << "nthreads = "<< nthreads << endl;
  task_scheduler_init schedulerInit((nthreads == 0) ? task_scheduler_init::automatic : nthreads);
  
  openvdb::initialize();

  float backgroundValue = 1000.0f; // 1000.0f
  float offset = -0.3; // -0.15 -> -0.30
  float cellsize = 0.1;
  
  // Create an empty floating-point grid
  
  t.start();
  tick_count t0 = tick_count::now();
  
  openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create(backgroundValue);
  CoordBBox indexBB(Coord(-70,-80,-20), Coord(300,80,70));
  f.create(grid, indexBB, cellsize/*0.1f*/);
  
  tick_count t1 = tick_count::now();
  t.stop();
  cout << "time for action (create grid) = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
  
  
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
    t.start();
    t0 = tick_count::now();
    f.original(grid, model);
    t1 = tick_count::now();
    t.stop();
    cout << "time for action (TOTAL) = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
    break;
  case 2:
    t.start();
    t0 = tick_count::now();
    f.computeoffset(grid, offset, cellsize, model);
    t1 = tick_count::now();
    t.stop();
    cout << "time for action (TOTAL) = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
    break;
  case 3:
    t.start();
    t0 = tick_count::now();
    f.useoffset(grid, offset, model);
    t1 = tick_count::now();
    t.stop();
    cout << "time for action (TOTAL) = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
    break;
  case 4:
    t.start();
    t0 = tick_count::now();
    f.Rounding_computeoffset(grid, offset, cellsize, model);
    t1 = tick_count::now();
    t.stop();
    cout << "time for action (TOTAL) = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
    break;
  case 5:
    t.start();
    t0 = tick_count::now();
    f.Rounding_useoffset(grid, offset, model);
    t1 = tick_count::now();
    t.stop();
    cout << "time for action (TOTAL) = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
    break;
  case 6:
    t.start();
    t0 = tick_count::now();
    f.Filleting_computeoffset(grid, offset, cellsize, model);
    t1 = tick_count::now();
    t.stop();
    cout << "time for action (TOTAL) = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
    break;
  case 7:
    t.start();
    t0 = tick_count::now();
    f.Filleting_useoffset(grid, offset, model);
    t1 = tick_count::now();
    t.stop();
    cout << "time for action (TOTAL) = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
    break;
  case 8:
    t.start();
    t0 = tick_count::now();
    f.Smoothing_computeoffset(grid, offset, cellsize, model);
    t1 = tick_count::now();
    t.stop();
    cout << "time for action (TOTAL) = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
    break;
  case 9:
    t.start();
    t0 = tick_count::now();
    f.Smoothing_useoffset(grid, offset, model);
    t1 = tick_count::now();
    t.stop();
    cout << "time for action (TOTAL) = " << (t1-t0).seconds() << " seconds (using tbb)" << endl;
    break;
  default:
    cout << "Please input number 0 ~ 9" << endl;
    break;
  }
  
  return 0;
}
