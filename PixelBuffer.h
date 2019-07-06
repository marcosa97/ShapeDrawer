#ifndef PIXEL_BUFFER_H
#define PIXEL_BUFFER_H

#include <GL/glut.h>

//The RGB struct contains the r,g,b components of one color
typedef struct RGB {
    GLfloat r, g, b;
} RGB;

//Class for Pixel Buffer
class PixelBuffer {
//private:
	//RGB *pixelBuffer;
public:
	RGB *pixelBuffer;
	int BUFFER_WIDTH, BUFFER_HEIGHT;

	PixelBuffer(int windowWidth, int windowHeight) { 
		BUFFER_WIDTH = windowWidth;
		BUFFER_HEIGHT = windowHeight;
		pixelBuffer = new RGB[BUFFER_WIDTH * BUFFER_HEIGHT]; 
	}
	~PixelBuffer() {
		delete pixelBuffer;
	}
	//Destructor needed
	void setPixel(int x, int y, float r, float g,  float b) {
        pixelBuffer[BUFFER_WIDTH * y + x].r = r;
        pixelBuffer[BUFFER_WIDTH * y + x].g = g;
        pixelBuffer[BUFFER_WIDTH * y + x].b = b;
    }

    void clearBuffer() {
    	for (int i =0; i < BUFFER_WIDTH * BUFFER_HEIGHT; i++) {
    		pixelBuffer[i].r = 0;
    		pixelBuffer[i].g = 0;
    		pixelBuffer[i].b = 0;
    	}
    }
};

#endif //PIXEL_BUFFER_H
