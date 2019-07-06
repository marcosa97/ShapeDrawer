#ifndef TRANSFORMATIONS_3D_H
#define TRANSFORMATIONS_3D_H

#include <cmath>
#include <iostream>
#include <limits>

#include "polyhedron.h"

#define PI 3.14159265

typedef float Matrix4x4 [4][4];

Point3D calculateCentroid(const Polyhedron &p);

void displayPolyhedronsInfo(const std::vector<Polyhedron> &GPolyhedrons);

void displayVertices(const std::vector<Polyhedron> &GPolyhedrons);

int getValidNumber(int min, int max);

void redrawScene(PixelBuffer *xy, PixelBuffer *xz, 
	             PixelBuffer *yz, PixelBuffer *newView, 
	             std::vector<Polyhedron> &polyhedrons, BoundingBox &BBData);

void handleTranslate(PixelBuffer *xy, PixelBuffer *xz, 
	                 PixelBuffer *yz, PixelBuffer *newView, 
	                 std::vector<Polyhedron> &polyhedrons, BoundingBox BBData);

void handleRotate(PixelBuffer *xy, PixelBuffer *xz, 
	                 PixelBuffer *yz, PixelBuffer *newView, 
	                 std::vector<Polyhedron> &polyhedrons, BoundingBox BBData);

void handleScale(PixelBuffer *xy, PixelBuffer *xz, 
	             PixelBuffer *yz, PixelBuffer *newView, 
	             std::vector<Polyhedron> &polyhedrons, BoundingBox BBData);

void handleRemoveObject(PixelBuffer *xy, PixelBuffer *xz, 
	             PixelBuffer *yz, PixelBuffer *newView, 
	             std::vector<Polyhedron> &polyhedrons, BoundingBox BBData);

#endif //TRANFORMATIONS_3D_H
