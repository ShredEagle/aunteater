#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <cmath>
#include <array>

#define POSITION_ATTRIB 0
#define COLOR_ATTRIB 1 //not used
#define TRANSFORM_ATTRIB 2
#define next_avail 4

GLfloat instance_pos[] = {
 .2, 0., 0.,
 0., .2, 0.,
 0.5, 0.5, 1.,
 
 .2, 0., 0.,
 0., .2, 0.,
 -0.5, -0.5, 1.,
 
 .2, 0., 0.,
 0., .2, 0.,
 0.5, -0.5, 1.
};

template <std::size_t N_vertice>
std::array<GLfloat, N_vertice*3> circle(GLfloat radius)
{
    typedef std::array<GLfloat, N_vertice*3> array;
    array vertices;
    vertices[0] = radius;
    vertices[1] = 0.;
    vertices[2] = 1.;
    for(size_t n = 1; n < N_vertice; ++n)
    {
        GLfloat const t = 2*M_PI*n / N_vertice;
        vertices[n*3] = cos(t)*radius;
        vertices[n*3 + 1] = sin(t)*radius;
        vertices[n*3 + 2] = 1.f;
    }

    return vertices;
}

const char* vert_shader = R"#(
    #version 150

    in vec3 position;
    out vec3 vcol;

    in mat3 instance_trans;

    void main(void)
    {
        vcol = vec3(1.0, 0., 1.0);
        gl_Position = vec4(instance_trans * position, 1.0);
    }
)#";
 
const char* frag_shader = R"#(
    #version 150

    in vec3 vcol;
    out vec4 fcol;

    void main(void)
    {
        fcol = vec4(vcol,1.0);
    }
)#";

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

#define SMOOTH 100

void init(void)
{
    GLuint vao;
    GLuint bufs[2];
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, bufs);
   
    glBindVertexArray(vao);
    glEnableVertexAttribArray(POSITION_ATTRIB);

    auto vertices = circle<SMOOTH>(1.);
    glBindBuffer(GL_ARRAY_BUFFER, bufs[0]);
    glBufferData(GL_ARRAY_BUFFER, std::tuple_size<decltype(vertices)>::value*3*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(POSITION_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint prog;
    prog = glCreateProgram();

    GLuint vert = compileShader(vert_shader, GL_VERTEX_SHADER);
    GLuint frag = compileShader(frag_shader, GL_FRAGMENT_SHADER);

    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
   
    glBindAttribLocation(prog, POSITION_ATTRIB, "position");
    glBindAttribLocation(prog, TRANSFORM_ATTRIB, "instance_trans");
   
    glLinkProgram(prog);
    glUseProgram(prog);

    GLuint transformBuffer;
    glGenBuffers(1, &transformBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3*9*sizeof(GLfloat), instance_pos, GL_STREAM_DRAW);
    for(std::size_t id : {0, 1, 2})
    {
        glEnableVertexAttribArray(TRANSFORM_ATTRIB+id);
        glVertexAttribPointer(TRANSFORM_ATTRIB+id, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3 * 3, (void*)(sizeof(GLfloat)* (3*id)));
        glVertexAttribDivisor(TRANSFORM_ATTRIB+id, 1);
    }

}
 
void render(GLFWwindow *window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, SMOOTH, 3);
    glfwSwapBuffers(window);
}
 
int main(int argc, char** argv)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // OS X crashes if this line is not present...
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "GLFW test", NULL, NULL);
    glfwMakeContextCurrent(window);

    init();

    while (!glfwWindowShouldClose(window))
    {
        render(window);
    }

    glfwTerminate();
}