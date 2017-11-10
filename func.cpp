#include <iostream>
#include <fstream>
#include <string>
#include <openvdb/openvdb.h>
#include <openvdb/tools/SignedFloodFill.h>
#include <openvdb/tools/VolumeToMesh.h>
#include <openvdb/tools/LevelSetRebuild.h>
#include <openvdb/tools/LevelSetFilter.h>
#include <openvdb/util/CpuTimer.h>
#include <vector>
#include "func.h"
#include "mechanical.h"
#include "boxes.h"

using namespace std;
using namespace openvdb;

openvdb::util::CpuTimer t;
using openvdb::tools::LevelSetFilter;

void computeoffset(FloatGrid::Ptr grid, float offset, int n){
  vector<Vec3s> points;
  vector<Vec4I> quads;
  
  openvdb::FloatGrid::Ptr grid_dist = grid;
  
  t.start();
  
  openvdb::FloatGrid::Ptr grid_offset = openvdb::tools::levelSetRebuild(*grid_dist, 0.0, 3);
  
  t.stop();

  
  t.start();
  
  for(openvdb::FloatGrid::ValueAllIter iter = grid_offset->beginValueAll(); iter; ++iter) {
    float dist = iter.getValue();
    iter.setValue(dist + offset);
  }
  
  t.stop();
  
  t.start();
  
  openvdb::tools::volumeToMesh(*grid_offset, points, quads , 0.0);

  t.stop();
  
  /* save to off file */
  if(n == 0)
    createOFFFile("mechanical_computeoffset.off", points, quads);
  else if(n == 1)
    createOFFFile("box_computeoffset.off", points, quads);
}


void useoffset(FloatGrid::Ptr grid, float offset, int n){
  //use OpenVDB's offset() function
  vector<Vec3s> points;
  vector<Vec4I> quads;
  
  grid->setGridClass(openvdb::GRID_LEVEL_SET);

  openvdb::FloatGrid::Ptr grid_offset = grid;  
  
  t.start();
  openvdb::tools::LevelSetFilter<openvdb::FloatGrid> use(*grid_offset);
  use.offset(offset);
  
  t.stop();

  
  t.start();
  
  openvdb::tools::volumeToMesh(*grid_offset, points, quads , 0.0);
  
  t.stop();

  // save to off file
  if(n == 0)
    createOFFFile("mechanical_useoffset.off", points, quads);
  else if(n == 1)
    createOFFFile("box_useoffset.off", points, quads);
}

void test(FloatGrid::Ptr grid, int n){
  vector<Vec3s> points;
  vector<Vec4I> quads;
  t.start();
  openvdb::tools::volumeToMesh(*grid, points, quads , 0.0);
  t.stop();
  if(n == 0)
    createOFFFile("mechanical.off", points, quads);
  else if(n == 1)
    createOFFFile("box.off", points, quads);
}


void create(FloatGrid::Ptr grid, const CoordBBox& indexBB, float h, int n){
  typename FloatGrid::Accessor accessor = grid->getAccessor();
  
  for (Int32 i = indexBB.min().x(); i <= indexBB.max().x(); ++i) {
    for (Int32 j = indexBB.min().y(); j <= indexBB.max().y(); ++j) {
      for (Int32 k = indexBB.min().z(); k <= indexBB.max().z(); ++k) {
	// transform point (i,j,k) of index space into world space
	// assume that hx=hy=hz=h (each cell is a cube)
	Vec3f p(i*h, j*h, k*h);

	// compute level set function value
	// note the convention: negative inside / positive outside
	if(n == 0) //mechanical
	  float distance = -eval(p.x(), p.y(), p.z());
	else if(n == 1){ //box
	  boxes_3d_is box;
	  float distance = -box.eval(p.x(), p.y(), p.z());
	}
	// set the value in the grid
	accessor.setValue(Coord(i,j,k), distance);
      }
    }
  }

  // In order to use the grid further, we need to associate a scaling transform
  // to this grid from voxel in index space to voxel in world space
  grid->setTransform(openvdb::math::Transform::createLinearTransform(h));
}


void createOFFFile(string out_file_name, vector<Vec3s> points, vector<Vec4I> quads){
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
