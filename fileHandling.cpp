
#include "fileHandling.h"

/* 
 * Gets file name and reads info into a Polyhedron object
 */
std::vector<Polyhedron> readFile() {
    std::vector<Polyhedron> phs;
    std::string fileName;
    std::string temp;
    int numPolyhedrons;

    //Get file name
    std::cout << "|******** File Read-In Mode ********|\n\n";
    //std::cout << "NOTE: Please make sure the file's coordinate points are within\n";
    //std::cout << "      the window's dimensions: " << pb->BUFFER_WIDTH << " x " << pb->BUFFER_HEIGHT << std::endl;
    std::cout << "Please enter the name of the file you wish to read in from: ";
    std::cin >> fileName;

    std::ifstream inputFile(fileName);
    if ( inputFile.fail() ) {
        std::cout << "ERROR: The file " << fileName << " does not exist.\n\n";
        return phs; //will be empy
    }  
     
    //First read in number of polyhedrons
    getline(inputFile, temp);
    std::stringstream(temp) >> numPolyhedrons;

    //Read in info for each polyhedron   
    for (int i = 0; i < numPolyhedrons; i++) {
        phs.push_back( Polyhedron() );

        //Ignore first line cuz it's blank
        getline(inputFile, temp);

        //First number is number of vertices
        int numVertices;
        getline(inputFile, temp);
        std::stringstream(temp) >> numVertices;
        //std::cout << numVertices << std::endl;

        //Read in vertices coordinates
        for (int j = 0; j < numVertices; j++) {
            float num;
            getline(inputFile, temp);
            phs[i].vertices.push_back( Point3D() );

            //Split string "temp" into tokens
            std::istringstream iss(temp);
            std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                            std::istream_iterator<std::string>{} };
            
            //x-coordinate
            std::stringstream(tokens[0]) >> num;
            phs[i].vertices[j].x = num;
            //std::cout << phs[i].vertices[j].x << " ";

            //y-coordinate
            std::stringstream(tokens[1]) >> num;
            phs[i].vertices[j].y = num;
            //std::cout << phs[i].vertices[j].y << " ";

            //z-coordinate
            std::stringstream(tokens[2]) >> num;
            phs[i].vertices[j].z = num;
            //std::cout << phs[i].vertices[j].z << std::endl;
        }

        //Next is number of edges
        int numEdges;
        getline(inputFile, temp);
        std::stringstream(temp) >> numEdges;
        //std::cout << numEdges << std::endl;

        for (int k = 0; k < numEdges; k++) {
            int p;
            getline(inputFile, temp);
            phs[i].edges.push_back( Edge() );

            std::istringstream iss(temp);
            std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                       std::istream_iterator<std::string>{} };
            
            //point 1
            std::stringstream(tokens[0]) >> p;
            phs[i].edges[k].p1 = p;
            //std::cout << phs[i].edges[k].p1 << " ";

            //point 2
            std::stringstream(tokens[1]) >> p;
            phs[i].edges[k].p2 = p;
            //std::cout << phs[i].edges[k].p2 << std::endl;
        } 
        
    }

    //Close file
    inputFile.close();

    return phs;
}

void handleFileInput(PixelBuffer *xy, PixelBuffer *xz, 
	                 PixelBuffer *yz, PixelBuffer *newView, std::vector<Polyhedron> &polyhedrons, BoundingBox BBData) {
    std::vector<Polyhedron> phs = readFile();

    for (int i = 0; i < phs.size(); i++) {
    	polyhedrons.push_back( phs[i] );
    }

    xy->clearBuffer();
    xz->clearBuffer();
    yz->clearBuffer();
    newView->clearBuffer();

    //Update Bounding Box Data
    BBData.updateBoundingBox(polyhedrons);
    //BBData.displayBBData();

    drawXYaxes(xy, BBData);
    drawXZaxes(xz, BBData);
    drawYZaxes(yz, BBData);

    //Update buffers for each view/projection
    for (int i = 0; i < polyhedrons.size(); i++) {
    	/*
    	phs[i].drawPolyhedronXY(xy, BBData);
        phs[i].drawPolyhedronXZ(xz, BBData);
        phs[i].drawPolyhedronYZ(yz, BBData);
        */
        polyhedrons[i].drawPolyhedronXY(xy, BBData);
        polyhedrons[i].drawPolyhedronXZ(xz, BBData);
        polyhedrons[i].drawPolyhedronYZ(yz, BBData);
        polyhedrons[i].drawPolyhedronCabinet(newView, BBData);
    }

}

void writeOutput(std::vector<Polyhedron> &polyhedrons) {
	std::ofstream outputFile("output.txt");

	outputFile << polyhedrons.size() << std::endl;

	for (int i = 0; i < polyhedrons.size(); i++) {
		outputFile << "\n";
		outputFile << polyhedrons[i].vertices.size() << std::endl;
		//write vertices
		for (int j = 0; j < polyhedrons[i].vertices.size(); j++) {
			outputFile << polyhedrons[i].vertices[j].x << " " << polyhedrons[i].vertices[j].y << " ";
			outputFile << polyhedrons[i].vertices[j].z << std::endl;
		}

		//Number of edges
		outputFile << polyhedrons[i].edges.size() << std::endl;
		//Write edges
		for (int k = 0; k < polyhedrons[i].edges.size(); k++) {
			outputFile << polyhedrons[i].edges[k].p1 << " " << polyhedrons[i].edges[k].p2 << std::endl;
		}
	}
}
