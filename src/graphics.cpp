#include "headers/graphics.hpp"
#include "headers/geometry.hpp"


//Initialization of variables for wrapper
bool Graphics::glInitialized = false;
unsigned int Texture::textureCount = 0;

unsigned char* bytes;
void Graphics::Start() {
    bytes = DrawLine(100, 120, true);
}

void Graphics::Draw() {
    texture->SetArray(0, 0, 100, 120, bytes);
}

void Graphics::Exit() {
    delete[] bytes;
}
