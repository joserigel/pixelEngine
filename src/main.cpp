#include <iostream>

#include "headers/graphics.hpp"

int main() {
    Graphics graphics;

    while (!graphics.ShouldClose()) {
        graphics.RenderLoop();
    }

    

    return 0;
}