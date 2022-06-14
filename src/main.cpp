#include <iostream>

#include "headers/graphics.hpp"

int main() {
    Graphics graphics;

    while (!graphics.ShouldClose()) {
        graphics.Render();
    }
    graphics.Exit();
    graphics.Delete();

    

    return 0;
}