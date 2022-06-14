#include "headers/graphics.hpp"



//Initialization of variables for wrapper
bool Graphics::glInitialized = false;
unsigned int Texture::textureCount = 0;



unsigned char* DrawBox(int side) {
    unsigned char* bytes = new unsigned char[side * side * 4];
    for (int i=0; i<side*side*4; i+=4) {
        bytes[i] = 255;
        bytes[i + 1] = 0;
        bytes[i + 2] = 0;
        bytes[i + 3] = 255;
    }
    
    return bytes;
}

unsigned char* DrawLine(int x, int y) {
    unsigned char* bytes = new unsigned char[x * y * 4];

    for (int i=0; i<x*y*4; i+=4) {
        bytes[i] = 0;
        bytes[i + 1] = 0;
        bytes[i + 2] = 0;
        bytes[i + 3] = 255;
    }
     
    if (x>=y) {
        float m =  (float)y / (float)x;
        for (int i=0; i<x; i++) {
            int yIdx = (int)floor(i * m);
            if (yIdx >= y) yIdx = y - 1;

            bytes[(yIdx * x * 4) + (i * 4)] = 255;
            bytes[(yIdx * x * 4) + (i * 4) + 1] = 255;
            bytes[(yIdx * x * 4) + (i * 4) + 2] = 255;
        }
        
    } else {
        float m = (float)x / (float)y;
        for (int i=0; i<y; i++) {
            int xIdx = (int) floor(i * m);
            if (xIdx >= x) xIdx = x - 1;

            bytes[(i * x * 4) + (xIdx * 4)] = 255;
            bytes[(i * x * 4) + (xIdx * 4) + 1] = 255;
            bytes[(i * x * 4) + (xIdx * 4) + 2] = 255;
        }
    }
    return bytes;
}

int xTranslate;
void Graphics::Start() {
    xTranslate = 0;
}

unsigned char* bytes = DrawLine(20, 100);

void Graphics::Draw() {
    texture->SetColor(50, 50, 50, 255);
    texture->SetArray(xTranslate, 0, 20,100, bytes);
    if (xTranslate <= 50) xTranslate++;
}

void Graphics::Exit() {
    delete[] bytes;
}
