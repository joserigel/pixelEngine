#ifndef SHADER_CLASS_HPP
#define SHADER_CLASS_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Shader {
    private:
        GLuint handler;
        static std::string ReadFile(const char* file) {
            std::ifstream ifBuffer;
            ifBuffer.open(file);

            std::stringstream strStream;
            strStream << ifBuffer.rdbuf();
            std::string str = strStream.str();

            return str;
        }
    public:
        Shader(const char* vertexShader, const char* fragmentShader) {
            std::string vertexShaderSource = ReadFile(vertexShader);
            std::string fragmentShaderSource = ReadFile(fragmentShader);

            const char* vertexSource = vertexShaderSource.c_str();
            const char* fragmentSource = fragmentShaderSource.c_str();
 
            //Create vertex shader
            GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vertexSource, NULL);
            glCompileShader(vertex);

            //Compile error logging for the vertex shader
            GLint vertexCompileStatus = 0;
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertexCompileStatus);
            if (vertexCompileStatus == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(vertex, maxLength, &maxLength, &errorLog[0]);

                for (int i=0; i<maxLength; i++) printf("%c", errorLog[i]);
            }

            //Create framgent shader
            GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fragmentSource, NULL);
            glCompileShader(fragment);

            //Compile error logging for the fragment shader
            GLint fragmentCompileStatus = 0;
            glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragmentCompileStatus);
            if (fragmentCompileStatus == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(fragment, maxLength, &maxLength, &errorLog[0]);
                
                for (int i=0; i<maxLength; i++) printf("%c", errorLog[i]);
            }

            //Attach shaders to the whole shader program
            handler = glCreateProgram();
            glAttachShader(handler, vertex);
            glAttachShader(handler, fragment);

            glLinkProgram(handler);

            //Delete individual shaders
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }
        void Use() { glUseProgram(handler); }
        void Delete() { 
            glUseProgram(handler);
            glDeleteProgram(handler); 
        }
        void SetTexture(const char* uniform, GLuint unit) {
            GLuint location = glGetUniformLocation(handler, uniform);
            glUniform1i(location, unit);
        }
};

#endif