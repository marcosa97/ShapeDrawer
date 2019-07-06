
#include "transformations3D.h"

using namespace std;

Point3D calculateCentroid(const Polyhedron &p) {
    Point3D centroid;

	//Calculate centroid of polygon
    for (int i = 0; i < p.vertices.size(); i++) {
    	centroid.x += p.vertices[i].x;
    	centroid.y += p.vertices[i].y;
    	centroid.z += p.vertices[i].z;
    }

    centroid.x = centroid.x / p.vertices.size();
    centroid.y = centroid.y / p.vertices.size();
    centroid.z = centroid.z / p.vertices.size();

    return centroid;
}

void displayPolyhedronsInfo(const vector<Polyhedron> &GPolyhedrons) {
    cout << "Current number of Polyhedron objects stored: " << GPolyhedrons.size() << endl; 
    for (int i = 0; i < GPolyhedrons.size(); i++) {
        cout << "Polyhedron Object #" << i + 1 << ":\n";
        int numVertices, numEdges;

        numVertices = GPolyhedrons[i].vertices.size();
        for (int j = 0; j < numVertices; j++) {
            cout << "    Point " << j+1 << ": x=" << GPolyhedrons[i].vertices[j].x;
            cout << " y=" << GPolyhedrons[i].vertices[j].y << " z=" << GPolyhedrons[i].vertices[j].z << endl;
        }

        numEdges = GPolyhedrons[i].edges.size();
        for (int j = 0; j < numEdges; j++) {
            cout << "    Edge from Point " << GPolyhedrons[i].edges[j].p1 << " to Point ";
            cout << GPolyhedrons[i].edges[j].p2 << endl;
        }
        cout << endl;
    }
}

int getValidNumber(int min, int max) {
    int num;

    //Get first point
    while (!(cin >> num) || !(num >= min && num < max ) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    
    return num;
}

void displayVertices(const std::vector<Polyhedron> &GPolyhedrons) {
	cout << "Current number of Polyhedron objects stored: " << GPolyhedrons.size() << endl;

	//If there's no polygons on screen, do nothing
    if (GPolyhedrons.size() == 0) {
        cout << "There are no polyhedron objects on screen. Read in a file to draw polyhedrons.\n\n";
        return;
    }

	cout << "Which Polyhedron's vertices do you want to print?\n";
	cout << "Enter Polyhedron Object's ID #, or 0 for all of them: ";
	int choice = getValidNumber(0, GPolyhedrons.size() + 1);

    if (choice == 0) {
    	for (int i = 0; i < GPolyhedrons.size(); i++) {
	        cout << "Polyhedron Object #" << i + 1 << ":\n";
	        int numVertices;

	        numVertices = GPolyhedrons[i].vertices.size();
	        for (int j = 0; j < numVertices; j++) {
	            cout << "    Point " << j+1 << ": x=" << GPolyhedrons[i].vertices[j].x;
	            cout << " y=" << GPolyhedrons[i].vertices[j].y << " z=" << GPolyhedrons[i].vertices[j].z << endl;
	        }
	        cout << endl;
        }
    } else {
        cout << "Polyhedron Object #" << choice << ":\n";
	    int numVertices;

	    numVertices = GPolyhedrons[choice - 1].vertices.size();
	    for (int j = 0; j < numVertices; j++) {
	        cout << "    Point " << j+1 << ": x=" << GPolyhedrons[choice-1].vertices[j].x;
	        cout << " y=" << GPolyhedrons[choice-1].vertices[j].y << " z=" << GPolyhedrons[choice-1].vertices[j].z << endl;
	    }
	    cout << endl;
    }
}

void redrawScene(PixelBuffer *xy, PixelBuffer *xz, 
	             PixelBuffer *yz, PixelBuffer *newView, 
	             std::vector<Polyhedron> &polyhedrons, BoundingBox &BBData) {

	//Clear screen buffers
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

void handleTranslate(PixelBuffer *xy, PixelBuffer *xz, 
	                 PixelBuffer *yz, PixelBuffer *newView, 
	                 std::vector<Polyhedron> &polyhedrons, BoundingBox BBData) {

    int objectID, choice;
    cout << "|******** Polyhedron Translation Mode ********|\n\n";

    //If there's no polygons on screen, do nothing
    if (polyhedrons.size() == 0) {
        cout << "There are no polyhedron objects on screen. Read in a file to draw polyhedrons to perform transformations\n\n";
        return;
    }

    displayPolyhedronsInfo(polyhedrons);

    //Get polygon choice
    cout << "Please enter the polyhedron object's ID number for which you wish to transform: ";
    objectID = getValidNumber(1, polyhedrons.size() + 1);
    objectID--; //index

    //Get translation vector
    float tx, ty, tz;
    cout << "Enter the x-component of the translation vector: ";
    //Get x component of vector
    while (!(cin >> tx) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    cout << "Enter the y-component of the translation vector: ";
    //Get y component of vector
    while (!(cin >> ty) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    cout << "Enter the z-component of the translation vector: ";
    //Get z component of vector
    while (!(cin >> tz) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }

    //Perform transformation
    for (int i = 0; i < polyhedrons[objectID].vertices.size(); i++) {
        polyhedrons[objectID].vertices[i].x += tx;
        polyhedrons[objectID].vertices[i].y += ty;
        polyhedrons[objectID].vertices[i].z += tz;
    }

    //Redraw scene
    redrawScene(xy, xz, yz, newView, polyhedrons, BBData);
    
}

/**********************************************/
/*** ROTATION FUNCTIONS: CODE FROM TEXTBOOK ***/
/**********************************************/

/* Constructs the 4 x 4 identity matrix. */
void matrix4x4SetIdentity (Matrix4x4 &matIdent4x4) {
	GLint row, col;

	for (row = 0; row < 4; row++) {
		for (col = 0; col < 4; col++) {
			matIdent4x4 [row][col] = (row == col);
		}
	}
}

/* Preultiply matrix m1 by matrix m2 and store result in m2 */
void matrix4x4PreMultiply (Matrix4x4 m1, Matrix4x4 &m2) {
	GLint row, col;
	Matrix4x4 matTemp;

	for (row = 0; row < 4; row++) {
		for (col = 0; col < 4; col++) {
			matTemp [row][col] = m1 [row][0] * m2 [0][col] + m1 [row][1] *
			                   m2 [1][col] + m1 [row][2] * m2 [2][col] +
			                   m1 [row][3] * m2 [3][col];
		}
	}

	for (row = 0; row < 4; row++) {
		for (col = 0; col < 4; col++) {
			m2[row][col] = matTemp [row][col];
		}
	}
}

void translate3D (GLfloat tx, GLfloat ty, GLfloat tz, Matrix4x4 &matRot) {
	Matrix4x4 matTransl3D;

	/* Initialize translation matrix to identity. */
	matrix4x4SetIdentity (matTransl3D);

	matTransl3D [0][3] = tx;
	matTransl3D [1][3] = ty;
	matTransl3D [2][3] = tz;

	/* Concatenate translation matrix with matRot */
	matrix4x4PreMultiply (matTransl3D, matRot);
}

/* Constructs a 3D rotation matrix */
void rotate3D (const Point3D &p1, const Point3D &p2, GLfloat radianAngle, Matrix4x4 &matRot) {
	Matrix4x4 matQuaternionRot;

	GLfloat axisVectLength = sqrt ( (p2.x - p1.x) * (p2.x - p1.x) + 
	                       (p2.y - p1.y) * (p2.y - p1.y) + 
	                       (p2.z - p1.z) * (p2.z - p1.z) );
	GLfloat cosA = cos (radianAngle);
	GLfloat oneC = 1 - cosA;
	GLfloat sinA = sin (radianAngle);
	GLfloat ux = (p2.x - p1.x) / axisVectLength;
	GLfloat uy = (p2.y - p1.y) / axisVectLength;
	GLfloat uz = (p2.z - p1.z) / axisVectLength;

	/* Set up translation matrix for moving p1 to origin. */
	translate3D (-p1.x, -p1.y, -p1.z, matRot);

	/* Initialize matQuaternionRot and matRot to identity matrix. */
	matrix4x4SetIdentity (matQuaternionRot);

	matQuaternionRot [0][0] = ux*ux*oneC + cosA;
	matQuaternionRot [0][1] = ux*uy*oneC - uz*sinA;
	matQuaternionRot [0][2] = ux*uz*oneC + uy*sinA;
	matQuaternionRot [1][0] = uy*ux*oneC + uz*sinA;
	matQuaternionRot [1][1] = uy*uy*oneC + cosA;
	matQuaternionRot [1][2] = uy*uz*oneC - ux*sinA;
	matQuaternionRot [2][0] = uz*ux*oneC - uy*sinA;
	matQuaternionRot [2][1] = uz*uy*oneC + ux*sinA;
	matQuaternionRot [2][2] = uz*uz*oneC + cosA;

	/* Combine matQuaternionRot with translation matrix */
	matrix4x4PreMultiply (matQuaternionRot, matRot); 

	/* Set up inverse matTransl3D and concatenate with
	 * product of previous two matrices.
	 */
	translate3D (p1.x, p1.y, p1.z, matRot);
}

void handleRotate(PixelBuffer *xy, PixelBuffer *xz, 
	                 PixelBuffer *yz, PixelBuffer *newView, 
	                 std::vector<Polyhedron> &polyhedrons, BoundingBox BBData) {

	int objectID, choice;
    cout << "|******** Polyhedron Rotation Mode ********|\n\n";

    //If there's no polygons on screen, do nothing
    if (polyhedrons.size() == 0) {
        cout << "There are no polyhedron objects on screen. Read in a file to draw polyhedrons to perform transformations\n\n";
        return;
    }

    displayPolyhedronsInfo(polyhedrons);

    //Get polygon choice
    cout << "Please enter the polyhedron object's ID number for which you wish to transform: ";
    objectID = getValidNumber(1, polyhedrons.size() + 1);
    objectID--; //index

    Point3D p1, p2;
    cout << "Enter the two points that will define the axis of rotation:" << endl;
    cout << "NOTE: Direction of axis is from point 1 to point 2." << endl;
    cout << "    Enter point 1's x-value: ";
    while (!(cin >> p1.x) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    cout << "    Enter point 1's y-value: ";
    while (!(cin >> p1.y) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    cout << "    Enter point 1's z-value: ";
    while (!(cin >> p1.z) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    cout << "    Enter point 2's x-value: ";
    while (!(cin >> p2.x) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    cout << "    Enter point 2's y-value: ";
    while (!(cin >> p2.y) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    cout << "    Enter point 2's z-value: ";
    while (!(cin >> p2.z) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }

    float rotationAngle;
    cout << "Enter the rotation angle in degrees: ";
    //Get rotation angle
    while (!(cin >> rotationAngle) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }

    //Create rotation matrix
    Matrix4x4 rotMat;
    matrix4x4SetIdentity (rotMat);
    rotate3D(p1, p2, rotationAngle * PI / 180.0, rotMat);

    //Rotate points by multiplying its vector by the rotation matrix
    for (int i = 0; i < polyhedrons[objectID].vertices.size(); i++) {
        float x, y, z;
        x = polyhedrons[objectID].vertices[i].x;
        y = polyhedrons[objectID].vertices[i].y;
        z = polyhedrons[objectID].vertices[i].z;

        polyhedrons[objectID].vertices[i].x = x*rotMat[0][0] + y*rotMat[0][1] + z*rotMat[0][2] + rotMat[0][3];
        polyhedrons[objectID].vertices[i].y = x*rotMat[1][0] + y*rotMat[1][1] + z*rotMat[1][2] + rotMat[1][3];
        polyhedrons[objectID].vertices[i].z = x*rotMat[2][0] + y*rotMat[2][1] + z*rotMat[2][2] + rotMat[2][3];

    }

    //Redraw scene
    redrawScene(xy, xz, yz, newView, polyhedrons, BBData);

    //line coordinatews converted to pixel coordinates
    PixelPoint2D p1pc = convertWCtoPC(p1, BBData);
    PixelPoint2D p2pc = convertWCtoPC(p2, BBData);

    //Clamp rotation axis line
    //p1pc.displayData();
    //p2pc.displayData();

    //Draw the rotation axis in each plane

    //Top left subwindow, XY plane
    glutSetWindow(2);
    lineDDAExtended(p1pc.x, p1pc.y, p2pc.x, p2pc.y, xy);
    //Top right subwindow, XZ plane
    glutSetWindow(3);
    lineDDAExtended(p1pc.x, p1pc.z, p2pc.x, p2pc.z, xz);
    //Bottom left subwindow, YZ plane
    glutSetWindow(4);
    lineDDAExtended(p1pc.y, p1pc.z, p2pc.y, p2pc.z, yz);

    glutPostRedisplay();
    
}

/**********************************************/
/***         SCALING FUNCTIONS              ***/
/**********************************************/

void handleScale(PixelBuffer *xy, PixelBuffer *xz, 
	             PixelBuffer *yz, PixelBuffer *newView, 
	             std::vector<Polyhedron> &polyhedrons, BoundingBox BBData) {

	int objectID, choice;
    cout << "|******** Polyhedron Uniform Scaling Mode ********|\n\n";

    //If there's no polygons on screen, do nothing
    if (polyhedrons.size() == 0) {
        cout << "There are no polyhedron objects on screen. Read in a file to draw polyhedrons to perform transformations\n\n";
        return;
    }

    displayPolyhedronsInfo(polyhedrons);

    //Get polygon choice
    cout << "Please enter the polyhedron object's ID number for which you wish to transform: ";
    objectID = getValidNumber(1, polyhedrons.size() + 1);
    objectID--; //index

    //Get scaling factor
    float scaleFactor;
    cout << "Please enter the scaling factor: ";
    while (!(cin >> scaleFactor) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    
    //Calculate centroid of object
    Point3D fixedPt = calculateCentroid( polyhedrons[objectID] );

    //Scale object vertices
    for (int i = 0; i < polyhedrons[objectID].vertices.size(); i++) {
    	polyhedrons[objectID].vertices[i].x = polyhedrons[objectID].vertices[i].x * scaleFactor + fixedPt.x * (1 - scaleFactor);
    	polyhedrons[objectID].vertices[i].y = polyhedrons[objectID].vertices[i].y * scaleFactor + fixedPt.y * (1 - scaleFactor);
    	polyhedrons[objectID].vertices[i].z = polyhedrons[objectID].vertices[i].z * scaleFactor + fixedPt.z * (1 - scaleFactor);
    }

    //Redraw scene
    redrawScene(xy, xz, yz, newView, polyhedrons, BBData);
}

void handleRemoveObject(PixelBuffer *xy, PixelBuffer *xz, 
	             PixelBuffer *yz, PixelBuffer *newView, 
	             std::vector<Polyhedron> &polyhedrons, BoundingBox BBData) {

    int objectID, choice;
    cout << "|******** Object Removal Mode ********|\n\n";

    //If there's no polygons on screen, do nothing
    if (polyhedrons.size() == 0) {
        cout << "There are no polyhedron objects on screen.\n\n";
        return;
    }

    displayPolyhedronsInfo(polyhedrons);

    //Get polygon choice
    cout << "Please enter the polyhedron object's ID number for which you wish to remove: ";
    objectID = getValidNumber(1, polyhedrons.size() + 1);
    objectID--; //index
    
    //Remove object
    polyhedrons.erase(polyhedrons.begin() + objectID);

    redrawScene(xy, xz, yz, newView, polyhedrons, BBData);
    cout << "Polyhedron object #" << objectID + 1 << " deleted.\n\n";
}