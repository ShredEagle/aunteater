//
//  Globals.h
//
//  Created by Adrien David.
//
//

#ifndef tutorial_Globals_h
#define tutorial_Globals_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <string>


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
        std::unique_ptr<char[]> logBuffer{new char[logLength]};
        glGetShaderInfoLog(shader, logLength, NULL, logBuffer.get());
        std::cerr << logBuffer.get();
    }

    return shader;
}

class Section
{
public:
    virtual void init() = 0;
    virtual void render(GLFWwindow *) = 0;

    virtual ~Section() = default;
};

} // namespace tutorial

#endif
