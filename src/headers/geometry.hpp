#ifndef GEOMETRY_CLASS_H
#define GEOMETRY_CLASS_H

#include <math.h>

unsigned char* DrawBox(int width, int height) {
    //Init array
    unsigned char* bytes = new unsigned char[width * height * 4];
    //Set all to white, with alpha 255
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
            int yIdx = (int)ceil(i * m);
            if (yIdx >= y) yIdx = y - 1;
            if (reversed) yIdx = y - 1 - yIdx;

            //setting pixels to whiteg
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

unsigned char* DrawCircle (int radius) {
    //Declaration and initialization of array
    unsigned char* bytes = new unsigned char[radius * radius * 16];
    for (int i=3; i<radius * radius * 16; i+=4) bytes[i] = 0;
    
    //Calculate to draw pixels only in the circle area
    for (int i=-radius; i<radius; i++) {
        for (int j=-radius; j<radius; j++) {
             int length = (int) round(sqrt((i*i) + (j*j)));

             if (length <= radius) {
                int x = radius + i;
                int y = radius + j;
                int idx = (y * radius * 8) + (x * 4);

                bytes[idx] = 255;
                bytes[idx + 1] = 255;
                bytes[idx + 2] = 255;
                bytes[idx + 3] = 255;
             }
        }
    }
    return bytes;
}


#endif