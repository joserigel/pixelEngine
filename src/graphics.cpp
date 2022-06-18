#include "headers/graphics.hpp"
#include "headers/geometry.hpp"


//Initialization of variables for wrapper
bool Graphics::glInitialized = false;
unsigned int Texture::textureCount = 0;

Shape shape(40, 40, 0, 0, DrawCircle(20));
int xOffset;
void Graphics::Start() {
    xOffset = 0;
}

void Graphics::Draw() {
    texture->SetColor(50, 50, 50, 255);
    if (xOffset < texture->getWidth() - shape.getWidth()) xOffset++;
    shape.x = xOffset;
    texture->SetShape(shape);
}   

void Graphics::Exit() {
    shape.Delete();
}
