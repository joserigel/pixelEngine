#ifndef TEXTURE_CLASS_HPP
#define TEXTURE_CLASS_HPP

#include <glad/glad.h>
#include <iostream>

class Texture {
    private:
        static unsigned int textureCount;
        GLuint handler;   
        GLuint unit;
    public:
        Texture() {
            //Offset for other texture instances
            unit = textureCount;

            //Gl define texture
            glGenTextures(1, &handler);
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, handler);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glBindTexture(GL_TEXTURE_2D, 0);

            textureCount++;
        }
        unsigned int GetUnit() { return unit; }
        void Define(int width, int height) {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, handler);

            unsigned char* bytes = new unsigned char[width * height * 4];
            for (int i=0; i<width*height*4; i+=4) {
                bytes[i] = 0;
                bytes[i + 1] = 0;
                bytes[i + 2] = 0;
                bytes[i + 3] = 255;
            }
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

            delete[] bytes;
        }
        void SetPixel(int x, int y) {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, handler);
            
            unsigned char bytes[] = {255, 255, 255, 255};
            glTexSubImage2D(GL_TEXTURE_2D, 0,
            x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
        }
};

unsigned int Texture::textureCount = 0;

#endif