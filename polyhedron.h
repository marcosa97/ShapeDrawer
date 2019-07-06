#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "PixelBuffer.h"
#include "lineAlgorithms.h"
#include "boundingBox.h"

class PixelPoint2D {
public:
    int x, y, z;
    PixelPoint2D() {
        x = 0;
        y = 0;
        z = 0;
    }
    PixelPoint2D(int ix, int iy, int iz) {
        x = ix;
        y = iy;
        z = iz;
    }
    PixelPoint2D(const PixelPoint2D &p) {
        x = p.x;
        y = p.y;
        z = p.z;
    }

    void displayData();
};

//Point in World Coordinates
class Point3D {
public:
    float x, y, z;
    Point3D() {
        x = 0;
        y = 0;
        z = 0;
    }
    Point3D(float ix, float iy, float iz) {
        x = ix;
        y = iy;
        z = iz;
    }
    Point3D(const Point3D &p) {
        x = p.x;
        y = p.y;
        z = p.z;
    }
};

class Edge {
public:
    int p1, p2;
    Edge() {
        p1 = 0;
        p2 = 0;
    }
    Edge(int _p1, int _p2) {
        p1 = _p1;
        p2 = _p2;
    }
    Edge(const Edge &e) {
        p1 = e.p1;
        p2 = e.p2;
    }
};

class Polyhedron {
public:
    std::vector<Point3D> vertices;
    std::vector<Edge> edges;

    Polyhedron() {

    }

    Polyhedron(const Polyhedron &p) {
        vertices = p.vertices;
        edges = p.edges;
    }

    ~Polyhedron() {
        
    }
    //For converting from World Coordinates (Point3D) -> NDC -> Pixel Coordinates
    //PixelPoint2D convertWCtoPC(const Point3D &p, BoundingBox BBData);

    //For projecting polyhedron in corresponding orthographic plane
    void drawPolyhedronXY(PixelBuffer *xyBuffer, BoundingBox BBData);
    void drawPolyhedronXZ(PixelBuffer *xzBuffer, BoundingBox BBData);
    void drawPolyhedronYZ(PixelBuffer *yzBuffer, BoundingBox BBData);
    void drawPolyhedronCabinet(PixelBuffer *newView, BoundingBox BBData);
};

//For converting from World Coordinates (Point3D) -> NDC -> Pixel Coordinates
PixelPoint2D convertWCtoPC(const Point3D &p, BoundingBox BBData);

void drawXYaxes(PixelBuffer *xyBuffer, BoundingBox BBData);
void drawXZaxes(PixelBuffer *xzBuffer, BoundingBox BBData);
void drawYZaxes(PixelBuffer *yzBuffer, BoundingBox BBData);

#endif //POLYHEDRON_H
