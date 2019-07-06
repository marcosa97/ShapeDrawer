#include <GL/glut.h>
#include <iostream>
#include <limits>
#include <utility>

#include "PixelBuffer.h"
#include "polyhedron.h"
#include "fileHandling.h"
#include "boundingBox.h"
#include "transformations3D.h"

using namespace std;

//Global pixel buffers for each subwindow
PixelBuffer *pixelBuffer;
PixelBuffer *pbTopLeft;
PixelBuffer *pbTopRight;
PixelBuffer *pbBottomLeft;
PixelBuffer *pbBottomRight;

//Keeps track of data needed to calculate bounding box
BoundingBox BBData;

// winMain = 1
// winTopLeft = 2
// winTopRight = 3
// winBottomLeft = 4
// winBottomRight = 5
int winTopLeft, winTopRight, winBottomLeft, winBottomRight, winMain;

//Global polyhedron objects
vector<Polyhedron> GPolyhedrons;

//Font style
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

//For drawing text on screen
void drawstr(GLfloat x, GLfloat y, const char* format, size_t length) {
    glRasterPos3f(x,y,0);
    for (int i = 0; i < length; ++i)
        glutBitmapCharacter(font_style, format[i]);
    glEnd();
}

void update() {
    //Draw XY plane text
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0 , 800, -1, 1);
    string str = "xy plane";
    drawstr(160, 780, str.c_str(), str.length());

    //Draw YZ plane text
    str = "yz plane";
    drawstr(160, 380, str.c_str(), str.length());

    //Draw XZ plane text
    str = "xz plane";
    drawstr(560, 780, str.c_str(), str.length());

    glDrawPixels( pixelBuffer->BUFFER_WIDTH, pixelBuffer->BUFFER_HEIGHT, GL_RGB, GL_FLOAT, pixelBuffer->pixelBuffer );
    glFlush();
}

void updateTL() {
    //Draw Border:
    //Vertical line
    for (int i = 0; i < pbTopLeft->BUFFER_HEIGHT; i++) {
        pbTopLeft->setPixel(pbTopLeft->BUFFER_WIDTH - 1, i, 252, 252, 252);
        pbTopLeft->setPixel(0, i, 252, 252, 252);
    }
    //Horizontal line
    for (int i = 0; i < pbTopLeft->BUFFER_WIDTH; i++) {
        pbTopLeft->setPixel(i, 0, 252, 252, 252);
        pbTopLeft->setPixel(i, pbTopLeft->BUFFER_HEIGHT - 1, 252, 252, 252);
    }

    glDrawPixels( pbTopLeft->BUFFER_WIDTH, pbTopLeft->BUFFER_HEIGHT, GL_RGB, GL_FLOAT, pbTopLeft->pixelBuffer );
    glFlush();
}

void updateTR() {
    //Draw Border:
    //Vertical line
    for (int i = 0; i < pbTopRight->BUFFER_HEIGHT; i++) {
        pbTopRight->setPixel(pbTopRight->BUFFER_WIDTH - 1, i, 252, 252, 252);
        pbTopRight->setPixel(0, i, 252, 252, 252);
    }
    //Horizontal line
    for (int i = 0; i < pbTopRight->BUFFER_WIDTH; i++) {
        pbTopRight->setPixel(i, 0, 252, 252, 252);
        pbTopRight->setPixel(i, pbTopRight->BUFFER_HEIGHT - 1, 252, 252, 252);
    }
    glDrawPixels( pbTopRight->BUFFER_WIDTH, pbTopRight->BUFFER_HEIGHT, GL_RGB, GL_FLOAT, pbTopRight->pixelBuffer );
    glFlush();
}

void updateBL() {
    //Draw Border:
    //Vertical line
    for (int i = 0; i < pbBottomLeft->BUFFER_HEIGHT; i++) {
        pbBottomLeft->setPixel(pbBottomLeft->BUFFER_WIDTH - 1, i, 252, 252, 252);
        pbBottomLeft->setPixel(0, i, 252, 252, 252);
    }
    //Horizontal line
    for (int i = 0; i < pbBottomLeft->BUFFER_WIDTH; i++) {
        pbBottomLeft->setPixel(i, 0, 252, 252, 252);
        pbBottomLeft->setPixel(i, pbBottomLeft->BUFFER_HEIGHT - 1, 252, 252, 252);
    }
    glDrawPixels( pbBottomLeft->BUFFER_WIDTH, pbBottomLeft->BUFFER_HEIGHT, GL_RGB, GL_FLOAT, pbBottomLeft->pixelBuffer );
    glFlush();
}

void updateBR() {
    //Draw Border:
    //Vertical line
    for (int i = 0; i < pbBottomRight->BUFFER_HEIGHT; i++) {
        pbBottomRight->setPixel(pbBottomRight->BUFFER_WIDTH - 1, i, 252, 252, 252);
        pbBottomRight->setPixel(0, i, 252, 252, 252);
    }
    //Horizontal line
    for (int i = 0; i < pbBottomRight->BUFFER_WIDTH; i++) {
        pbBottomRight->setPixel(i, 0, 252, 252, 252);
        pbBottomRight->setPixel(i, pbBottomRight->BUFFER_HEIGHT - 1, 252, 252, 252);
    }
    glDrawPixels( pbBottomRight->BUFFER_WIDTH, pbBottomRight->BUFFER_HEIGHT, GL_RGB, GL_FLOAT, pbBottomRight->pixelBuffer );
    glFlush();
}

void clearBuffersAndObjects() {
    GPolyhedrons.clear();

    glutSetWindow(2);
    pbTopLeft->clearBuffer();
    glutPostRedisplay();

    glutSetWindow(3);
    pbTopRight->clearBuffer();
    glutPostRedisplay();

    glutSetWindow(4);
    pbBottomLeft->clearBuffer();
    glutPostRedisplay();

    glutSetWindow(5);
    pbBottomRight->clearBuffer();
    glutPostRedisplay();
}

//For debugging
void displayPolyhedronsInfo() {
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

void myIdleFunction() {
    //Get input
    cout << "Please enter the number for which operation you wish to perform: " << endl;
    cout << "    1) Read in 3D polyhedra objects from a .txt file." << endl;
    cout << "    2) Perform a 3D translation on an object." << endl; 
    cout << "    3) Perform a 3D rotation about a specified axis on an object." << endl;
    cout << "    4) Perform a 3D scaling on an object." << endl;
    cout << "    5) Remove an object from the scene." << endl;
    cout << "    6) Remove all objects (clear screen)." << endl;
    cout << "    7) Print out polyhedra vertex coordinates." << endl;
    cout << "    8) Exit Program (and write current objects to file 'output.txt')." << endl;
    cout << ">> ";

    //while input is invalid, get valid input
    int choice = 0;
    while (!(cin >> choice) || !(choice > 0 && choice < 9) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }

    cout << endl;

    //switch 
    switch (choice) {
        case 1: handleFileInput(pbTopLeft, pbTopRight, pbBottomLeft, pbBottomRight, GPolyhedrons, BBData); displayPolyhedronsInfo(); break;
        case 2: handleTranslate(pbTopLeft, pbTopRight, pbBottomLeft, pbBottomRight, GPolyhedrons, BBData); break;
        case 3: handleRotate(pbTopLeft, pbTopRight, pbBottomLeft, pbBottomRight, GPolyhedrons, BBData); break;
        case 4: handleScale(pbTopLeft, pbTopRight, pbBottomLeft, pbBottomRight, GPolyhedrons, BBData); break;
        case 5: handleRemoveObject(pbTopLeft, pbTopRight, pbBottomLeft, pbBottomRight, GPolyhedrons, BBData); break;
        case 6: clearBuffersAndObjects(); break;
        case 7: displayVertices(GPolyhedrons); break;
        case 8: writeOutput(GPolyhedrons); delete pixelBuffer; delete pbTopLeft; delete pbTopRight; delete pbBottomLeft; delete pbBottomRight; exit(0); return;
    }
    
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 800;
    int SUBWINDOW_MARGIN = 30;

    //Intro
    cout << "==============================================" << endl;
    cout << "|**  ECS175 Project 2, by Marcos Alcantar  **|" << endl;
    cout << "==============================================" << endl << endl;

    //Initialize glut   
    glutInit(&argc, argv);
  
    glutInitDisplayMode (GLUT_SINGLE);
    
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    winMain = glutCreateWindow("ECS175: Program 2");
    glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    glutDisplayFunc(update);
    glutIdleFunc(myIdleFunction);

    int subwindowWidth = WINDOW_WIDTH/2 - 2* SUBWINDOW_MARGIN;
    int subwindowHeight = WINDOW_HEIGHT/2 - 2* SUBWINDOW_MARGIN;

    //Top left subwindow = 2
    winTopLeft = glutCreateSubWindow(winMain, SUBWINDOW_MARGIN, SUBWINDOW_MARGIN, 
                                     subwindowWidth, subwindowHeight);
    glutDisplayFunc(updateTL);

    //Top right subwindow = 3
    winTopRight = glutCreateSubWindow(winMain, WINDOW_WIDTH/2 + SUBWINDOW_MARGIN, SUBWINDOW_MARGIN,
                                      subwindowWidth, subwindowHeight);
    glutDisplayFunc(updateTR);

    //Bottom left subwindow = 4 
    winBottomLeft = glutCreateSubWindow(winMain, SUBWINDOW_MARGIN, WINDOW_HEIGHT/2 + SUBWINDOW_MARGIN, 
                                        subwindowWidth, subwindowHeight);
    glutDisplayFunc(updateBL);
    
    //Bottom right subwindow
    winBottomRight = glutCreateSubWindow(winMain, WINDOW_WIDTH/2 + SUBWINDOW_MARGIN, WINDOW_WIDTH/2 + SUBWINDOW_MARGIN,
                                         subwindowWidth, subwindowHeight);
    glutDisplayFunc(updateBR);

    //Create pixel buffer dynamically
    //This 1D array specifies colors for each pixel in the pixel buffer
    pixelBuffer = new PixelBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

    pbTopLeft = new PixelBuffer(subwindowWidth, subwindowHeight);
    pbTopRight = new PixelBuffer(subwindowWidth, subwindowHeight);
    pbBottomLeft = new PixelBuffer(subwindowWidth, subwindowHeight);
    pbBottomRight = new PixelBuffer(subwindowWidth, subwindowHeight);

    BBData.boxResolution = WINDOW_WIDTH/2 - 2*SUBWINDOW_MARGIN;
    BBData.boxMargin = 20; //hardcoded

    glutMainLoop();
 
    return 0;
}
