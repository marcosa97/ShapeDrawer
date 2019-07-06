
#include "boundingBox.h"

#include "polyhedron.h"

//Calculates bounding box based on current objects in the scene
void BoundingBox::updateBoundingBox(std::vector<Polyhedron> p) {
	if (p.size() > 0) {

	    //Find minimums and maximums
	    float _xMin = p[0].vertices[0].x;
	    float _xMax = p[0].vertices[0].x;
	    float _yMin = p[0].vertices[0].y;
	    float _yMax = p[0].vertices[0].y;
	    float _zMin = p[0].vertices[0].z;
	    float _zMax = p[0].vertices[0].z;
	    
	    for (int i = 0; i < p.size(); i++) {
	    	for (int j = 0; j < p[i].vertices.size(); j++) {
	    		//Find mins
	    		if (p[i].vertices[j].x < _xMin) {
	    			_xMin = p[i].vertices[j].x;
	    		}
	    		if (p[i].vertices[j].y < _yMin) {
	    			_yMin = p[i].vertices[j].y;
	    		}
	    		if (p[i].vertices[j].z < _zMin) {
	    			_zMin = p[i].vertices[j].z;
	    		}
                
                //Find maxs
                if (p[i].vertices[j].x > _xMax) {
                	_xMax = p[i].vertices[j].x;
                }
                if (p[i].vertices[j].y > _yMax) {
                	_yMax = p[i].vertices[j].y;
                }
                if (p[i].vertices[j].z > _zMax) {
                	_zMax = p[i].vertices[j].z;
                }
	    	} 
	    }

        //Update variables
        xMin = _xMin;
        xMax = _xMax;
        yMin = _yMin;
        yMax = _yMax;
        zMin = _zMin;
        zMax = _zMax;
    }
}

void BoundingBox::displayBBData() {
	std::cout << "CURRENT BOUNDING BOX:\n";
	std::cout << "xMin = " << xMin << std::endl;
	std::cout << "xMax = " << xMax << std::endl;
	std::cout << "yMin = " << yMin << std::endl;
	std::cout << "yMax = " << yMax << std::endl;
	std::cout << "zMin = " << zMin << std::endl;
	std::cout << "zMax = " << zMax << std::endl;
}
