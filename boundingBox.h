#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <iostream>
#include <vector>

//Forward declare
class Polyhedron;

//Keeps track of data needed to calcualte bounding box
class BoundingBox {
public:
	int boxResolution; //in pixels
	int boxMargin; //margin in pixels
    float xMin, xMax;
    float yMin, yMax;
    float zMin, zMax;

    BoundingBox() {
    	boxResolution = 0;
    	boxMargin = 0;
    	xMin = 0;
    	xMax = 0;
    	yMin = 0;
    	yMax = 0;
    	zMin = 0;
    	zMax = 0;
    }

    void updateBoundingBox(std::vector<Polyhedron> p);
    void displayBBData(); //FOR DEBUGGING
};

#endif //BOUNDING_BOX_H
