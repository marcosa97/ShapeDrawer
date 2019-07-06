#ifndef LINE_DDA_H
#define LINE_DDA_H

#include <math.h>
#include "PixelBuffer.h"

void lineDDA (int x0, int y0, int xEnd, int yEnd, PixelBuffer *pb) ;

void lineDDAClip (int x0, int y0, int xEnd, int yEnd, PixelBuffer *pb) ;

void lineDDAExtended (int x0, int y0, int xEnd, int yEnd, PixelBuffer *pb);

void lineBresenham (int x0, int y0, int xEnd, int yEnd, PixelBuffer *pb) ;

#endif //LINE_DDA_H
