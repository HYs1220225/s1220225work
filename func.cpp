#include <iostream>
#include <fstream>
#include <string>
#include <openvdb/openvdb.h>
#include <openvdb/tools/SignedFloodFill.h>
#include <openvdb/tools/VolumeToMesh.h>
#include <openvdb/tools/LevelSetRebuild.h>
#include <openvdb/tools/LevelSetFilter.h>
#include <openvdb/util/CpuTimer.h>
// #include <vector>
#include "func.h"
// #include "mechanical.h"
// #include "boxes.h"

using namespace std;
using namespace openvdb;

openvdb::util::CpuTimer T;
using openvdb::tools::LevelSetFilter;

void Func::computeoffset(FloatGrid::Ptr grid, float offset, std::string model){
  vector<Vec3s> points;
  vector<Vec4I> quads;
  
  openvdb::FloatGrid::Ptr grid_dist = grid;
  
  T.start();
  
  openvdb::FloatGrid::Ptr grid_offset = openvdb::tools::levelSetRebuild(*grid_dist, 0.0, 3);
  
  T.stop();

  
  T.start();
  
  for(openvdb::FloatGrid::ValueAllIter iter = grid_offset->beginValueAll(); iter; ++iter) {
    float dist = iter.getValue();
    iter.setValue(dist + offset);
  }
  
  T.stop();
  
  T.start();
  
  openvdb::tools::volumeToMesh(*grid_offset, points, quads , 0.0);

  T.stop();
  
  /* save to off file */
  createOFFFile(model + "_computeoffset.off", points, quads);
}


void Func::useoffset(FloatGrid::Ptr grid, float offset, std::string model){
  //use OpenVDB's offset() function
  vector<Vec3s> points;
  vector<Vec4I> quads;
  
  grid->setGridClass(openvdb::GRID_LEVEL_SET);

  openvdb::FloatGrid::Ptr grid_offset = grid;  
  
  T.start();
  openvdb::tools::LevelSetFilter<openvdb::FloatGrid> use(*grid_offset);
  use.offset(offset);
  
  T.stop();

  
  T.start();
  
  openvdb::tools::volumeToMesh(*grid_offset, points, quads , 0.0);
  
  T.stop();

  // save to off file
  createOFFFile(model + "_useoffset.off", points, quads);
}

void Func::test(FloatGrid::Ptr grid, std::string model){
  vector<Vec3s> points;
  vector<Vec4I> quads;
  T.start();
  openvdb::tools::volumeToMesh(*grid, points, quads , 0.0);
  T.stop();
  // cout << "run test function" << endl;
  createOFFFile(model + ".off", points, quads);
}


void Func::createOFFFile(string out_file_name, vector<Vec3s> points, vector<Vec4I> quads){
  // cout << "run createOFFFile function" << endl;
  int i;
  ofstream f(out_file_name);
  f << "OFF" << endl;
  f << points.size() << " " << quads.size() << " 0" << endl;
  for(i = 0; i < points.size(); ++i){
    f << points[i].x() << "  " << points[i].y() << "  " << points[i].z() << endl;
  }

  for(i = 0; i < quads.size(); ++i){
    f << "4  " << quads[i].x() << " " << quads[i].y() << " " << quads[i].z() << " " << quads[i].w() << endl;
  }
  f << endl;
  f.close();
}


void Func::Rounding_computeoffset(FloatGrid::Ptr grid, float offset, std::string model){
  vector<Vec3s> points;
  vector<Vec4I> quads;
  
  openvdb::FloatGrid::Ptr grid_dist = grid;
  
  T.start();
  
  openvdb::FloatGrid::Ptr grid_offset = openvdb::tools::levelSetRebuild(*grid_dist, 0.0, 3);
  
  T.stop();

  
  T.start();
  
  for(openvdb::FloatGrid::ValueAllIter iter = grid_offset->beginValueAll(); iter; ++iter) {
    float dist = iter.getValue();
    iter.setValue(dist - offset);
  }  
  for(openvdb::FloatGrid::ValueAllIter iter = grid_offset->beginValueAll(); iter; ++iter) {
    float dist = iter.getValue();
    iter.setValue(dist + offset);
  }
  
  T.stop();
  
  T.start();
  
  openvdb::tools::volumeToMesh(*grid_offset, points, quads , 0.0);

  T.stop();
  
  /* save to off file */
  createOFFFile(model + "_Rounding_computeoffset.off", points, quads);
}

void Func::Filleting_computeoffset(FloatGrid::Ptr grid, float offset, std::string model){
  vector<Vec3s> points;
  vector<Vec4I> quads;
  
  openvdb::FloatGrid::Ptr grid_dist = grid;
  
  T.start();
  
  openvdb::FloatGrid::Ptr grid_offset = openvdb::tools::levelSetRebuild(*grid_dist, 0.0, 3);
  
  T.stop();

  
  T.start();
  
  for(openvdb::FloatGrid::ValueAllIter iter = grid_offset->beginValueAll(); iter; ++iter) {
    float dist = iter.getValue();
    iter.setValue(dist + offset);
  }  
  for(openvdb::FloatGrid::ValueAllIter iter = grid_offset->beginValueAll(); iter; ++iter) {
    float dist = iter.getValue();
    iter.setValue(dist - offset);
  }
  
  T.stop();
  
  T.start();
  
  openvdb::tools::volumeToMesh(*grid_offset, points, quads , 0.0);

  T.stop();
  
  /* save to off file */
  createOFFFile(model + "_Filleting_computeoffset.off", points, quads);
}

void Func::Smoothing_computeoffset(FloatGrid::Ptr grid, float offset, std::string model){
  vector<Vec3s> points;
  vector<Vec4I> quads;
  
  openvdb::FloatGrid::Ptr grid_dist = grid;
  
  T.start();
  
  openvdb::FloatGrid::Ptr grid_offset = openvdb::tools::levelSetRebuild(*grid_dist, 0.0, 3);
  
  T.stop();

  
  T.start();
  
  for(openvdb::FloatGrid::ValueAllIter iter = grid_offset->beginValueAll(); iter; ++iter) {
    float dist = iter.getValue();
    iter.setValue(dist - offset);
  }  
  for(openvdb::FloatGrid::ValueAllIter iter = grid_offset->beginValueAll(); iter; ++iter) {
    float dist = iter.getValue();
    iter.setValue(dist + (2*offset));
  }  
  for(openvdb::FloatGrid::ValueAllIter iter = grid_offset->beginValueAll(); iter; ++iter) {
    float dist = iter.getValue();
    iter.setValue(dist - offset);
  }
  
  T.stop();
  
  T.start();
  
  openvdb::tools::volumeToMesh(*grid_offset, points, quads , 0.0);

  T.stop();
  
  /* save to off file */
  createOFFFile(model + "_Smoothing_computeoffset_test.off", points, quads);
}

void Func::Rounding_useoffset(FloatGrid::Ptr grid, float offset, std::string model){
  //use OpenVDB's offset() function
  vector<Vec3s> points;
  vector<Vec4I> quads;
  
  grid->setGridClass(openvdb::GRID_LEVEL_SET);

  openvdb::FloatGrid::Ptr grid_offset = grid;  
  
  T.start();
  openvdb::tools::LevelSetFilter<openvdb::FloatGrid> use(*grid_offset);
  use.offset((-1)*offset);
  use.offset(offset);
  
  T.stop();

  
  T.start();
  
  openvdb::tools::volumeToMesh(*grid_offset, points, quads , 0.0);
  
  T.stop();

  // save to off file
  createOFFFile(model + "_Rounding_useoffset.off", points, quads);
}

void Func::Filleting_useoffset(FloatGrid::Ptr grid, float offset, std::string model){
  //use OpenVDB's offset() function
  vector<Vec3s> points;
  vector<Vec4I> quads;
  
  grid->setGridClass(openvdb::GRID_LEVEL_SET);

  openvdb::FloatGrid::Ptr grid_offset = grid;  
  
  T.start();
  openvdb::tools::LevelSetFilter<openvdb::FloatGrid> use(*grid_offset);
  use.offset(offset);
  use.offset((-1)*offset);
  
  T.stop();

  
  T.start();
  
  openvdb::tools::volumeToMesh(*grid_offset, points, quads , 0.0);
  
  T.stop();

  // save to off file
  createOFFFile(model + "_Filleting_useoffset.off", points, quads);
}

void Func::Smoothing_useoffset(FloatGrid::Ptr grid, float offset, std::string model){
  //use OpenVDB's offset() function
  vector<Vec3s> points;
  vector<Vec4I> quads;
  
  grid->setGridClass(openvdb::GRID_LEVEL_SET);

  openvdb::FloatGrid::Ptr grid_offset = grid;  
  
  T.start();
  openvdb::tools::LevelSetFilter<openvdb::FloatGrid> use(*grid_offset);
  //rounding and filleting
  use.offset((-1)*offset);
  use.offset(2*offset);
  use.offset((-1)*offset);
  T.stop();

  
  T.start();
  
  openvdb::tools::volumeToMesh(*grid_offset, points, quads , 0.0);
  
  T.stop();

  // save to off file
  createOFFFile(model + "_Smoothing_useoffset.off", points, quads);
}
