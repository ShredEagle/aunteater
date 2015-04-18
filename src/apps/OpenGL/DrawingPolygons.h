//
//  DrawingPolygons.h
//
//  Created by Adrien David.
//
//

#ifndef tutorial_DrawingPolygons_h
#define tutorial_DrawingPolygons_h

#include "Globals.h"

#include <vector>

namespace tutorial {

class DrawingPolygons : public Section
{
    std::string vertexShaderSource = R"#(
        #version 150

        in vec2 position;

        void main()
        {
            gl_Position = vec4(position, 0., 1.);
        }
    )#";

    std::string fragmentShaderSource = R"#(
        #version 150

        out vec4 color;

        void main()
        {
            color = vec4(1, 0., 0., 1.);
        }
    )#";


    static const std::vector<float> vertices;


public:
    virtual void init() override
    {
        /* Setup the vertex data */
        GLuint vbo;
        glGenBuffers(1, &vbo); // request 1 buffer, put its 'name' in vbo
        glBindBuffer(GL_ARRAY_BUFFER, vbo); // binds a GL_ARRAY_BUFFER object to vertex buffer named by vbo, making it active
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW); // uploads the data to the current GL_ARRAY_BUFFER object

        /* Setup the program */
        GLuint vertexShader     = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
        GLuint fragmentShader   = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
        GLuint shaderProgram    = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        // Nota: glGetAttribLocation approach (after linking) has drawbacks compared to glBindAttribLocation
        // see: http://stackoverflow.com/a/4638906/1027706
        GLuint position = 0;
        glBindAttribLocation(shaderProgram, position, "position");

        glBindFragDataLocation(shaderProgram, 0, "color"); // not needed, this is already the default binding

        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        /* Setup the vertex array : the pointers to generic vertex attributes (position, color, ...) 
           are stored in the currently bound Vertex Array Object by calls to glVertexAttribPointer */
        // see: https://www.opengl.org/wiki/OpenGL_Object#Object_types for more details regarding the object types.
        GLuint vao;
        glGenVertexArrays(1, &vao); // request 1 vertex array object, put its 'name' in vao
        glBindVertexArray(vao); // binds the vertex array object named by vao

        /* Make the link between vertex data and shader attributes */
        glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 0, 0); // store in the current vertex array object the association
                                                                      // between the currently bound buffer object and the position attribute
        glEnableVertexAttribArray(position);

    }

    virtual void render(GLFWwindow *aWindow) override
    {
        glDrawArrays(GL_TRIANGLES, 0, 3); // draws based on the currently bound vertex array object
        glfwSwapBuffers(aWindow);
    }

};

//const float DrawingPolygons::vertices[6];
const std::vector<float> DrawingPolygons::vertices = {
        0.f,    1.f,
        -1.f,   -1.f,
        1.f,    -1.f
};

} // namespace tutorial

#endif
