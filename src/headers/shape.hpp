#ifndef SHAPE_CLASS_H
#define SHAPE_CLASS_H

class Shape {
    private:
        int _width, _height;
        unsigned char* data;
    public:
        int x, y;
        Shape(int width, int height, int xOffset, int yOffset, unsigned char* bytes) {
            _width = width;
            _height = height;

            x = xOffset;
            y = yOffset;

            data = bytes;
        }
        unsigned char* getBytes() { return data; }
        int getWidth() { return _width;}
        int getHeight() { return _height; }
        void Delete() {
            delete[] data;
        }

};


#endif