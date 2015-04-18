//
//  Textures.h
//
//  Created by Adrien David.
//
//

#ifndef tutorial_Textures_h
#define tutorial_Textures_h

#include "Globals.h"
#include "ImageReader.h"

#include <vector>

namespace tutorial {
class Textures : public Section
{
    std::string vertexShaderSource = R"#(
        #version 150

        in vec2 position;
        in vec2 texcoord;

        out vec2 oTexcoord;

        void main()
        {
            gl_Position = vec4(position, 0., 1.);
            oTexcoord = texcoord;
        }
    )#";

    std::string fragmentShaderSource = R"#(
        #version 150

        in vec2 oTexcoord;

        out vec4 color;
        uniform sampler2D tex;

        void main()
        {
            //color = vec4(1, 0., 0., 1.);
            color = texture(tex, oTexcoord);
        }
    )#";


    static const std::vector<GLfloat> vertices;
    static const std::vector<GLuint> indices;

public:
    virtual void init() override
    {
        /* Setup the vertex data */
        GLuint vbo;
        glGenBuffers(1, &vbo); // request 1 buffer, put its 'name' in vbo
        glBindBuffer(GL_ARRAY_BUFFER, vbo); // binds a GL_ARRAY_BUFFER object to vertex buffer named by vbo, making it active
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertices.size(), vertices.data(), GL_STATIC_DRAW); // uploads the data to the current GL_ARRAY_BUFFER object

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

        GLuint texcoord = 1;
        glBindAttribLocation(shaderProgram, texcoord, "texcoord");

        glBindFragDataLocation(shaderProgram, 0, "color"); // not needed, this is already the default binding

        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        //*** This section is usefull only if several textures unit are used ***//
        glActiveTexture(GL_TEXTURE1); // OPTIONAL if there is only one texture (texture0 active by default)
        glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 1); // linking "tex" to the texture unit "1"
        //GLuint texunit = 2;
        //glBindAttribLocation(shaderProgram, texunit, "tex"); // no equivalent for uniforms
        // *** ***//

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        ImageReader image("../resources/halal_texture.jpg");
        //GLfloat checkerboard[] = {
        //    0., 0., 0.,     1., 1., 1.,
        //    1., 1., 1.,     0., 0., 0.,
        //};
        //Image image{checkerboard, 2, 2};

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.mWidth, image.mHeight, 0, GL_RGB, GL_FLOAT, image.mData);

        /* Setup the vertex array : the pointers to generic vertex attributes (position, color, ...)
           are stored in the currently bound Vertex Array Object by calls to glVertexAttribPointer */
        // see: https://www.opengl.org/wiki/OpenGL_Object#Object_types for more details regarding the object types.
        GLuint vao;
        glGenVertexArrays(1, &vao); // request 1 vertex array object, put its 'name' in vao
        glBindVertexArray(vao); // binds the vertex array object named by vao

        // Unlike the ARRAY_BUFFER, the ELEMENT_ARRAY_BUFFER is part of the VAO state.
        GLuint vboIndices;
        glGenBuffers(1, &vboIndices); // request 1 buffer, put its 'name' in vbo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices); // binds a GL_ARRAY_BUFFER object to vertex buffer named by vbo, making it active
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices.size(), indices.data(), GL_STATIC_DRAW); // uploads the data to the current GL_ARRAY_BUFFER object

        /* Make the link between vertex data and shader attributes */
        glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0); // store in the current vertex array object the association
                                                                      // between the currently bound buffer object and the position attribute
        glEnableVertexAttribArray(position);

        glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), static_cast<char *>(nullptr) + (2*sizeof(GLfloat)));
        glEnableVertexAttribArray(texcoord);

    }

    virtual void render(GLFWwindow *aWindow) override
    {
        //glDrawArrays(GL_TRIANGLES, 0, 3); // draws based on the currently bound vertex array object
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(aWindow);
    }

};

const std::vector<GLfloat> Textures::vertices = {
    -0.5f, -0.5f,   0., 0.,
    +0.5f, -0.5f,   1., 0.,
    +0.5f, +0.5f,   1., 1.,
    -0.5f, +0.5f,   0., 1.
};

const std::vector<GLuint> Textures::indices = {
    0, 1, 2,
    2, 3, 0
};

}; // namespace tutorial

#endif
