#include <iostream>
#include "lineAlgorithms.h"

/*
    TEST CASES: 
    lineDDA (0, 0, 200, 200, pixelBuffer); //dx = dy
    lineDDA (0, 200, 200, 0, pixelBuffer); //dx = -dy
    lineDDA (0, 0, 30, 299, pixelBuffer);  
    lineDDA (0, 0, 200, 20, pixelBuffer);
    lineDDA (0, 200, 200, 50, pixelBuffer); //Negative
    lineDDA (0, 200, 250, 190, pixelBuffer); //Negative Not Steep //FIXME
    lineDDA (0, 100, 250, 100, pixelBuffer); //Horizontal
    lineDDA (150, 0, 150, 299, pixelBuffer); //Vertical           //FIXME

    
    lineBresenham (0, 0, 300, 300, pixelBuffer); //m = 1
    lineBresenham (0, 0, 400, 30, pixelBuffer); //Positive Not Steep
    lineBresenham (0, 0, 50, 500, pixelBuffer); //Positive Steep 
    lineBresenham (0, 150, 400, 150, pixelBuffer); //Horizontal
    lineBresenham (400, 0, 400, 400, pixelBuffer); //Vertical  
    lineBresenham (400, 0, 0, 100, pixelBuffer); //FIXME 
    lineBresenham (0, 300, 400, 0, pixelBuffer); //Negative, dx = - dy
*/

inline int myRound (const float a) { return int (a + 0.5); }

//DDA line drawing algorithm from textbook
void lineDDA (int x0, int y0, int xEnd, int yEnd, PixelBuffer *pb) {
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;

    //If dx > dy -> For handling a slope of m > 1 (positive steep)
    if (fabs (dx) > fabs (dy))
        steps = fabs (dx);
    else 
        steps = fabs (dy);

    xIncrement = float (dx) / float (steps);
    yIncrement = float (dy) / float (steps);

    //std::cout << "xIncrement: " << xIncrement << std::endl;
    //std::cout << "yIncrement: " << yIncrement << std::endl;
        
    //setPixel (myRound (x), myRound (y), 0.5, 0.5, 0.5);
    pb->setPixel( myRound(x), myRound (y), 1.0, 1.0, 1.0);

    //Increment X one by one and for every x determine closest Y-value
    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        //setPixel (myRound (x), myRound (y), 0.5, 0.5, 0.5);
        pb->setPixel( myRound(x), myRound (y), 1.0, 1.0, 1.0);
    }
}

/* For drawing rotation axes */
void lineDDAExtended (int x0, int y0, int xEnd, int yEnd, PixelBuffer *pb) {
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;

    if (fabs (dx) > fabs(dy))
        steps = fabs (dx);
    else
        steps = fabs (dy);

    xIncrement = float (dx) / float (steps);
    yIncrement = float (dy) / float (steps);

    //Find right endpoint
    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;

        if (x >= pb->BUFFER_WIDTH - 1) {
            x = pb->BUFFER_WIDTH - 1;
        }
        if (x <= 0) {
            x = 0;
        }
        if (y >= pb->BUFFER_HEIGHT - 1) {
            y = pb->BUFFER_HEIGHT - 1;
        }
        if (y <= 0) {
            y = 0;
        }

        pb->setPixel( myRound(x), myRound(y), 1.0, 0, 0);
    }


}

/* Draw extended line that reaches the edges of the screen/pixel buffer */
void lineDDAClip (int x0, int y0, int xEnd, int yEnd, PixelBuffer *pb) {
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;

    if (fabs (dx) > fabs(dy))
        steps = fabs (dx);
    else
        steps = fabs (dy);

    xIncrement = float (dx) / float (steps);
    yIncrement = float (dy) / float (steps);

    //Find right endpoint
    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;

        if (x >= pb->BUFFER_WIDTH - 1) {
            continue;
        } 
        else if (x <= 0) {
            continue;
        }
        else if (y >= pb->BUFFER_HEIGHT - 1) {
            continue;
        }
        else if (y <= 0) {
            continue;
        }

        pb->setPixel( myRound(x), myRound(y), 0, 0.7, 0);
    }


}

//Bresenham line drawing algorithm
//TODO: Only handles positive slope |m| < 1.0
void lineBresenham (int x0, int y0, int xEnd, int yEnd, PixelBuffer *pb) {
    
    bool mGreater1 = false;
    bool negativeSlope = false;

    //Swap points if necessary
    if (x0 > xEnd) {
        int n = x0;
        x0 = xEnd;
        xEnd = n;
        n = y0;
        y0 = yEnd;
        yEnd = n;
    } 

    //Check if m is negative
    //if ( xEnd > x0 && yEnd < y0 ) {
    if ( yEnd < y0 ) {
        //td::cout << "NEGATIVE SLOPE" << std::endl;
        negativeSlope = true;
    } 
    
    //Check if abs(m) > 1 
    if ( (int) fabs (yEnd - y0) > (int) fabs (xEnd - x0) ) {
        //std::cout << "POSITIVE STEEP" << std::endl;
        int temp = x0;
        x0 = y0;
        y0 = temp;
        temp = xEnd;
        xEnd = yEnd;
        yEnd = temp;
        mGreater1 = true;
    } 

    int dx = fabs (xEnd - x0), dy = fabs (yEnd - y0);
    int p = 2 * dy - dx; //p0
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);
    int x, y;

    //Determine which endpoint to use as start position
    //Algorithm moves from left to right
    if (x0 > xEnd) {
        //swap x0 and xEnd
        x = xEnd;
        y = yEnd;
        xEnd = x0;
    } else {
        x = x0;
        y = y0;
    }
 
    //If there's a negative slope, we start drawing from the top
    if (negativeSlope) {
        y = y0;
    }

    //setPixel (x, y, 1.0, 0, 0);
    pb->setPixel(x, y, 1.0, 0, 0);
     
    if ( mGreater1 ) {
        
        while (x < xEnd) {
            x++;
            if (p < 0)
                p += twoDy;
            else {
                if (negativeSlope) 
                    y--;
                else 
                    y++;
                p += twoDyMinusDx;
            }
            pb->setPixel (y, x, 0, 1, 0);
        }
    } else { 
     
        while (x < xEnd) {
            x++;
            if (p < 0) 
                p += twoDy;
            else {
                if (negativeSlope)
                    y--;
                else
                    y++;
                p += twoDyMinusDx;
            }
            pb->setPixel (x, y, 1.0, 0, 0);
        }
    }
}