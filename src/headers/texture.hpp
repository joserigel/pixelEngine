#ifndef TEXTURE_CLASS_HPP
#define TEXTURE_CLASS_HPP

#include <glad/glad.h>
#include <iostream>

class Texture {
    private:
        static unsigned int textureCount;
        GLuint handler;   
        GLuint unit;
        int resX, resY, ratio;

    public:
        Texture(int width, int height, int divisor) {
            //Init texture resolution
            ratio = divisor;
            resX = width / ratio;
            resY = height / ratio;

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

            unsigned char* bytes = new unsigned char[resX * resY * 4];
            for (int i=0; i<resX*resY*4; i+=4) {
                bytes[i] = 0;
                bytes[i + 1] = 0;
                bytes[i + 2] = 0;
                bytes[i + 3] = 255;
            }

            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, resX, resY,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

            delete[] bytes;

            textureCount++;
        }
        unsigned int GetUnit() { return unit; }
        void SetPixel(int x, int y, 
            unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
            unsigned char bytes[] = {r, g, b, a};
            glTexSubImage2D(GL_TEXTURE_2D, 0,
            x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
        }
        void SetArray(int x, int y, int width, int height, unsigned char* bytes) {
            for (int i=0; i<width; i++) {
                for (int j=0; j<height; j++) {
                    if (bytes[(i * 4) + (j * width * 4) + 3] == 255) {
                        unsigned char r = bytes[(i * 4) + (j * width * 4)];
                        unsigned char g = bytes[(i * 4) + (j * width * 4) + 1];
                        unsigned char b = bytes[(i * 4) + (j * width * 4) + 2];
                        SetPixel(x + i, y + j, r, g, b, 255);
                    } 
                }
            }
        }
        void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
            unsigned char* bytes = new unsigned char[resX * resY * 4];

            for (int i=0; i<resX*resY*4; i+=4) {
                bytes[i] = r;
                bytes[i + 1] = g;
                bytes[i + 2] = b;
                bytes[i + 3] = a;
            }

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resX, resY, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
            
            delete[] bytes;
        }
        void Bind() { glBindTexture(GL_TEXTURE_2D, handler); }
        void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
        void Delete() {
            glDeleteTextures(1, &handler);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
};



#endif