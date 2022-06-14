#ifndef GEOMETRY_CLASS_H
#define GEOMETRY_CLASS_H

#include <math.h>

unsigned char* DrawBox(int width, int height) {
    unsigned char* bytes = new unsigned char[width * height * 4];
    for (int i=0; i<width*height*4; i+=4) {
        bytes[i] = 255;
        bytes[i + 1] = 255;
        bytes[i + 2] = 255;
        bytes[i + 3] = 255;
    }
    
    return bytes;
}

unsigned char* DrawLine(int x, int y, bool reversed) {
    //Declaration and initialization of array
    unsigned char* bytes = new unsigned char[x * y * 4];
    for (int i=3; i<x * y * 4; i+=4)  bytes[i] = 0;
    

    if (x>=y) {
        //gradient calculation
        float m =  (float)y / (float)x;
        for (int i=0; i<x; i++) {
            //y Offset for each x calculation
            int yIdx = (int)floor(i * m);
            if (yIdx >= y) yIdx = y - 1;
            if (reversed) yIdx = y - 1 - yIdx;

            //setting pixels to white
            bytes[(yIdx * x * 4) + (i * 4)] = 255;
            bytes[(yIdx * x * 4) + (i * 4) + 1] = 255;
            bytes[(yIdx * x * 4) + (i * 4) + 2] = 255;
            bytes[(yIdx * x * 4) + (i * 4) + 3] = 255;
        }
        
    } else {
        //gradient calculation
        float m = (float)x / (float)y;
        for (int i=0; i<y; i++) {
            //x offset for each y calculation
            int xIdx = (int) floor(i * m);
            if (xIdx >= x) xIdx = x - 1;
            if (reversed) xIdx = x - 1 - xIdx;

            //setting pixels to white
            bytes[(i * x * 4) + (xIdx * 4)] = 255;
            bytes[(i * x * 4) + (xIdx * 4) + 1] = 255;
            bytes[(i * x * 4) + (xIdx * 4) + 2] = 255;
            bytes[(i * x * 4) + (xIdx * 4) + 3] = 255;
        }
    }
    return bytes;
}

#endif