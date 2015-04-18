//
//  Globals.h
//
//  Created by Adrien David.
//
//

#ifndef tutorial_Globals_h
#define tutorial_Globals_h

#define GLFW_INCLUDE_GLCOREARB // will include the modern open gl header, exposing modern methods
                               // that should otherwise be retrieved (a-la GLEW)
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

namespace tutorial {

inline GLuint compileShader(const std::string &aSource, GLenum aShaderType)
{
    GLuint shader = glCreateShader(aShaderType);
    const char* src = aSource.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    //Error Handling
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        char logBuffer[logLength];
        glGetShaderInfoLog(shader, logLength, NULL, logBuffer);
        std::cerr << logBuffer;
    }

    return shader;
}

class Section
{
public:
    virtual void init() = 0;
    virtual void render(GLFWwindow *) = 0;
};

} // namespace tutorial

#endif
