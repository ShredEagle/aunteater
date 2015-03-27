#define GLFW_INCLUDE_GLCOREARB // will include the modern open gl header, exposing modern methods
                               // that should otherwise be retrieved (a-la GLEW)
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

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


float vertices[] = {
    0.f,    1.f,
    -1.f,   -1.f,
    1.f,    -1.f
};

GLuint compileShader(const std::string &aSource, GLenum aShaderType)
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

void init()
{
    /* Setup the vertex data */
    GLuint vbo;
    glGenBuffers(1, &vbo); // request 1 buffer, put its 'name' in vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // binds a GL_ARRAY_BUFFER object to vertex buffer named by vbo, making it active
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // uploads the data to the current GL_ARRAY_BUFFER object

    /* Setup the program */
    GLuint vertexShader     = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader   = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    GLuint shaderProgram    = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

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
    GLint position = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 0, 0); // store in the current vertex array object the association
                                                                  // between the currently bound buffer object and the position attribute
    glEnableVertexAttribArray(position);

}

void render(GLFWwindow *aWindow)
{
    glDrawArrays(GL_TRIANGLES, 0, 3); // draws based on the currently bound vertex array object
    glfwSwapBuffers(aWindow);
}

int main(int argc, char** argv)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // OS X crashes if this line is not present...
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW test", NULL, NULL);
    glfwMakeContextCurrent(window);

    init();

    while (!glfwWindowShouldClose(window))
    {
        render(window);
    }

    glfwTerminate();
}