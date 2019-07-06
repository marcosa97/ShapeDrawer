#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstdio>

#include "PixelBuffer.h"
#include "polyhedron.h"
#include "boundingBox.h"

/*
FILE FORMAT:
1             number of objects
              definition of 1st object:
4             number of points of 1st object
0.0 0.0 0.0   coordinates of 1st point
1.0 0.0 0.0   coordinates of 2nd point
0.0 1.0 0.0   coordinates of 3rd point
0.0 0.0 1.0   coordinates of 4th point
6             number of edges of 1st object
1 2           edge from point 1 to point 2
1 3           edge from point 1 to point 3
1 4           edge from point 1 to point 4
2 3           edge from point 2 to point 3
2 4           edge from point 2 to point 4
3 4           edge from point 3 to point 4
*/

std::vector<Polyhedron> readFile();

void handleFileInput(PixelBuffer *xy, PixelBuffer *xz, 
	                 PixelBuffer *yz, PixelBuffer *newView, 
	                 std::vector<Polyhedron> &polyhedrons, BoundingBox BBData);

void writeOutput(std::vector<Polyhedron> &polyhedrons);

#endif //FILE_HANDLING_H
