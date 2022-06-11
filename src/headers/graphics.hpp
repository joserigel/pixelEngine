#ifndef GRAPHICS_CLASS_HPP
#define GRAPHICS_CLASS_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.hpp"
#include "texture.hpp"

class Graphics
{
    private:
        static bool glInitialized;
        GLFWwindow* window;

        int width, height;
        GLuint vao, vbo, ebo;
        Shader* shader;
        Texture* texture;


        void WindowResizeBehavior() {
            int x, y;
            glfwGetWindowSize(window, &x, &y);
            if (x != width || y != height) {
                width = x;
                height = y;
                glViewport(0, 0, width, height);
            }
        }
    public:
        Graphics() {
            //Init GLFW
            if (!glInitialized) {
                glfwInit();
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                glInitialized = true;
            }

            //Create Window
            width = 1280; height = 720;
            window = glfwCreateWindow(width, height, "DoomClone", NULL, NULL);
            if (window == NULL) glfwTerminate();
            else {
                glfwMakeContextCurrent(window);
                gladLoadGL();
                glViewport(0, 0, width, height);
            
                //Generate Objects
                glGenVertexArrays(1, &vao);
                glGenBuffers(1, &vbo);
                glGenBuffers(1, &ebo);

                //Datas
                float vertices[] = {
                    //Positions             //UV
                    -1.0f, -1.0f, 0.0f,     0.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,     1.0f, 0.0f,    
                    -1.0f,  1.0f, 0.0f,     0.0f, 1.0f,
                    1.0f,  1.0f, 0.0f,     1.0f, 1.0f,
                };
                unsigned int indices[] = {
                    0, 2, 3,
                    0, 3, 1,
                };
                
                //Define Objects
                glBindVertexArray(vao);

                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

                
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(1);

                //Create Texture
                texture = new Texture();
                texture->Define(width, height);

                //Use Shaders
                shader = new Shader("src/shaders/default.vert", "src/shaders/default.frag");
                shader->Use();
                shader->SetTexture("txtr", texture->GetUnit());
            }
        }
        bool ShouldClose() {
            return glfwWindowShouldClose(window);
        }
        void Input() {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            int cursorX = (int)round(x);
            int cursorY = (int)round(y);

            if (cursorX < width && cursorX >= 0 && 
                    cursorY < height && cursorY >= 0) {
                texture->SetPixel(cursorX, height - cursorY);
            }
            
        }
        void RenderLoop() {
            //Misc.
            WindowResizeBehavior();
            
            //Clear Buffers
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            Input();

            //User Defined
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
            //Swap Buffer + Poll
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        void Delete() {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
};

bool Graphics::glInitialized = false;

#endif