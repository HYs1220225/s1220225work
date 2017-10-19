CXX := g++
CXXFLAGS := -std=c++11 -O3 -DNDEBUG -isystem /usr/local/include

testvdb: sample_mechanical.cpp
	@echo "Building $@ because of $(list_deps)"
	$(CXX) $(CXXFLAGS) -o $@ sample_mechanical.cpp hfoperations.cpp hfprimitives.cpp mechanical.cpp \
	-Wl,-rpath,/usr/local/lib -L/usr/local/lib -lopenvdb \
	-ldl -lm -lz -Wl,-rpath,/usr/local -L/usr/local -lHalf \
	-Wl,-rpath,/usr/local -L/usr/local -ltbb \
	-Wl,-rpath,/usr/local/opt -L/usr/local/opt -lboost_iostreams -lboost_system  \
	-Wl,-rpath,/usr/local -L/usr/local -ljemalloc

