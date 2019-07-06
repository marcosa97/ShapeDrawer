
#include "polyhedron.h"

void PixelPoint2D::displayData() {
	std::cout << "Pixel Point: (" << x << "," << y << "," << z << ")" << std::endl;
}

PixelPoint2D convertWCtoPC(const Point3D &p, BoundingBox BBData) {
	PixelPoint2D pp;
	//int resolution = 360; //HARDCODED, 400 - 40, cuz 20 for margin on each side
	//int margin = 20;
	int resolution = BBData.boxResolution - 2 * BBData.boxMargin;
	int margin = BBData.boxMargin;
    float deltaX = BBData.xMax - BBData.xMin;
    float deltaY = BBData.yMax - BBData.yMin;
    float deltaZ = BBData.zMax - BBData.zMin;
    
    float maxDelta = deltaX;
    if (deltaY > maxDelta) 
    	maxDelta = deltaY;
    if (deltaZ > maxDelta)
    	maxDelta = deltaZ;

	//Transform to Normalized Device Coordinates (NDC)
	float xNDC = (p.x - BBData.xMin) / maxDelta;
	float yNDC = (p.y - BBData.yMin) / maxDelta;
	float zNDC = (p.z - BBData.zMin) / maxDelta;
    
    /*
    std::cout << "xNDC = " << xNDC << std::endl;
    std::cout << "yNDC = " << yNDC << std::endl;
    std::cout << "zNDC = " << zNDC << std::endl;
    */

    //Now tranform to pixel coordintates
    pp.x = roundf( (resolution - 1) * xNDC) + margin;
    pp.y = roundf( (resolution - 1) * yNDC) + margin;
    pp.z = roundf( (resolution - 1) * zNDC) + margin;

    return pp;
}

void drawXYaxes(PixelBuffer *xyBuffer, BoundingBox BBData) {
	glutSetWindow(2);
    Point3D x0(-1000, 0, 0);
    Point3D xEnd(1000, 0, 0);
    Point3D y0(0, -1000, 0);
    Point3D yEnd(0, 1000, 0);

    PixelPoint2D xAxis_0, xAxis_End, yAxis_0, yAxis_End;
    xAxis_0 = convertWCtoPC(x0, BBData);
    xAxis_End = convertWCtoPC(xEnd, BBData);
    yAxis_0 = convertWCtoPC(y0, BBData);
    yAxis_End = convertWCtoPC(yEnd, BBData);

    lineDDAClip( xAxis_0.x, xAxis_0.y, xAxis_End.x, xAxis_End.y, xyBuffer);
    lineDDAClip( yAxis_0.x, yAxis_0.y, yAxis_End.x, yAxis_End.y, xyBuffer);
    glutPostRedisplay();
}

void drawXZaxes(PixelBuffer *xzBuffer, BoundingBox BBData) {
	glutSetWindow(3);
    Point3D x0(-1000, 0, 0);
    Point3D xEnd(1000, 0, 0);
    Point3D z0(0, 0, -1000);
    Point3D zEnd(0, 0, 1000);

    PixelPoint2D xAxis_0, xAxis_End, zAxis_0, zAxis_End;
    xAxis_0 = convertWCtoPC(x0, BBData);
    xAxis_End = convertWCtoPC(xEnd, BBData);
    zAxis_0 = convertWCtoPC(z0, BBData);
    zAxis_End = convertWCtoPC(zEnd, BBData);

    lineDDAClip( xAxis_0.x, xAxis_0.z, xAxis_End.x, xAxis_End.z, xzBuffer);
    lineDDAClip( zAxis_0.x, zAxis_0.z, zAxis_End.x, zAxis_End.z, xzBuffer);
    glutPostRedisplay();
}

void drawYZaxes(PixelBuffer *yzBuffer, BoundingBox BBData) {
	glutSetWindow(4);
    Point3D y0(0, -1000, 0);
    Point3D yEnd(0, 1000, 0);
    Point3D z0(0, 0, -1000);
    Point3D zEnd(0, 0, 1000);

    PixelPoint2D yAxis_0, yAxis_End, zAxis_0, zAxis_End;
    yAxis_0 = convertWCtoPC(y0, BBData);
    yAxis_End = convertWCtoPC(yEnd, BBData);
    zAxis_0 = convertWCtoPC(z0, BBData);
    zAxis_End = convertWCtoPC(zEnd, BBData);

    lineDDAClip( yAxis_0.y, yAxis_0.z, yAxis_End.y, yAxis_End.z, yzBuffer);
    lineDDAClip( zAxis_0.y, zAxis_0.z, zAxis_End.y, zAxis_End.z, yzBuffer);
    glutPostRedisplay();
}

/* XY = top left subwindow
 * WindowID = 2
 */
void Polyhedron::drawPolyhedronXY(PixelBuffer *xyBuffer, BoundingBox BBData) {
	glutSetWindow(2);

    /* Now draw polyhedron */
    PixelPoint2D pp[ vertices.size() ];

    //Convert vertices to pixel coordinates
    for (int i = 0; i < vertices.size(); i++) {
        pp[i] = convertWCtoPC(vertices[i], BBData);
        //pp[i].displayData();
        //xyBuffer->setPixel(pp[i].x, pp[i].y, 252, 252, 252);
    }

    //Draw polyhedron edges in XY projection
    for (int i = 0; i < edges.size(); i++) {
    	lineDDA( pp[ edges[i].p1 - 1 ].x, pp[ edges[i].p1 - 1 ].y, pp[ edges[i].p2 - 1 ].x, pp[ edges[i].p2 - 1 ].y, xyBuffer);
    }

    glutPostRedisplay(); 
}

/* XZ = top right subwindow
 * WindowID = 3
 */
void Polyhedron::drawPolyhedronXZ(PixelBuffer *xzBuffer, BoundingBox BBData) {
	glutSetWindow(3);
	//lineDDA(20, 20, 100, 100, xzBuffer);

	PixelPoint2D pp[ vertices.size() ];

    //Convert vertices to pixel coordinates
    for (int i = 0; i < vertices.size(); i++) {
    	pp[i] = convertWCtoPC(vertices[i], BBData);
    }

    for (int i = 0; i < edges.size(); i++) {
    	lineDDA( pp[ edges[i].p1 - 1 ].x, pp[ edges[i].p1 - 1 ].z, pp[ edges[i].p2 - 1 ].x, pp[ edges[i].p2 - 1 ].z, xzBuffer);
    }

	//Draw polyhedron in XZ projection
    glutPostRedisplay();
}

/* YZ = bottom left subwindow
 * WindowID = 4
 */
void Polyhedron::drawPolyhedronYZ(PixelBuffer *yzBuffer, BoundingBox BBData) {
    glutSetWindow(4);
    //lineDDA(50, 50, 150, 50, yzBuffer);

    PixelPoint2D pp[ vertices.size() ];

    //Draw polyhedron in YZ projection
    for (int i = 0; i < vertices.size(); i++) {
    	pp[i] = convertWCtoPC(vertices[i], BBData);
    }

    for (int i = 0; i < edges.size(); i++) {
    	lineDDA( pp[ edges[i].p1 - 1 ].y, pp[ edges[i].p1 - 1 ].z, pp[ edges[i].p2 - 1 ].y, pp[ edges[i].p2 - 1 ].z, yzBuffer);
    }
    
    glutPostRedisplay();
}

void Polyhedron::drawPolyhedronCabinet(PixelBuffer *newView, BoundingBox BBData) {
	glutSetWindow(5);

	float pi = 3.14159265;

	PixelPoint2D pp[ vertices.size() ];

	/* Projection Matrix for Cabinet into XY plane:

       P = [ [1, 0, .5*z*cos(A)] 
             [0, 1, .5*z*sin(A)]
             [0, 0, 0        ]
           ]
	*/

	//Apply transofmration matrix
    std::vector<Point3D> wc = vertices;
	for (int i = 0; i < vertices.size(); i++) {
		wc[i].x = wc[i].x + ( 0.5 * wc[i].z * cos(45 * pi / 180.0) );
		wc[i].y = wc[i].y + ( 0.5 * wc[i].z * sin(45 * pi / 180.0) );
		wc[i].z = 0;
	}

	//Convert vertices to pixel coordinates
    for (int i = 0; i < wc.size(); i++) {
        pp[i] = convertWCtoPC(wc[i], BBData);
    }

    //Draw polyhedron edges in XY projection
    for (int i = 0; i < edges.size(); i++) {
    	lineDDAClip( pp[ edges[i].p1 - 1 ].x, pp[ edges[i].p1 - 1 ].y, pp[ edges[i].p2 - 1 ].x, pp[ edges[i].p2 - 1 ].y, newView);
    }

    glutPostRedisplay(); 
}