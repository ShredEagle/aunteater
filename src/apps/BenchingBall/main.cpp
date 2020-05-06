#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ComponentPosition.h"
#include "ComponentVelocity.h"

#include "SystemMove.h"
#include "SystemRender.h"

#include "globals.h"

#include <aunteater/UpdateTiming.h>

#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

#ifdef _WIN32
#define M_PI 3.14159265358979323846
#endif

using namespace BenchingBall;

#define POSITION_ATTRIB 0
#define COLOR_ATTRIB 1 //not used
#define TRANSFORM_ATTRIB 2
#define next_avail 4

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
        std::unique_ptr<char[]> logBuffer{new char[logLength]};
        glGetShaderInfoLog(shader, logLength, NULL, logBuffer.get());
        std::cerr << logBuffer.get();
    }

    return shader;
}

void init(void)
{
    GLuint vao;
    GLuint bufs[2];
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, bufs);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(POSITION_ATTRIB);

    auto vertices = circle<SMOOTH>(RADIUS);
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
    // Now done directly by the SystemRender instance
    //glBufferData(GL_ARRAY_BUFFER, 3*9*sizeof(GLfloat), instance_pos, GL_STREAM_DRAW);
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

class FpsDisplay
{
public:
    FpsDisplay(double aPeriod) :
            mPeriod(aPeriod),
            mCurrentPeriod(mPeriod)
    {}

    void tick(double aDeltaTime, GLFWwindow *window)
    {
        ++mFrameCount;
        mCurrentPeriod -= aDeltaTime;

        if(mCurrentPeriod <= 0)
        {
            std::ostringstream fpsCount;
            fpsCount << "BenchingBall: " /*<< std::setw(5) << std::setfill('0') */
                     << std::round(mFrameCount/(mPeriod-mCurrentPeriod)) << " fps";
            glfwSetWindowTitle(window, fpsCount.str().c_str());

            mCurrentPeriod = mPeriod;
            mFrameCount = 0;
        }
    }
private:
    const double mPeriod;
    double mCurrentPeriod;
    unsigned int mFrameCount = 0;
};

static void error_callback(int error, const char* description)
{
    std::cerr <<  "Error: " << description << "\n";
}

int main(int argc, char** argv)
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // OS X crashes if this line is not present...
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "GLFW test", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glfwSwapInterval(1);

    init();
    aunteater::Engine engine;
    // System can be added already instantiated
    engine.addSystem(std::make_shared<SystemMove>(engine));
    // Or can be instantiated by add(), implicitly providing engine as first argument to ctor
    engine.addSystem<SystemRender>(window);

    engine.addEntity(aunteater::Entity().add<ComponentPosition>(.5, .5)
                                        .add<ComponentVelocity>(1., .1));
    engine.addEntity(aunteater::Entity().add<ComponentPosition>(-.5, -.5)
                                        .add<ComponentVelocity>(-.3, 2.));
    engine.addEntity(aunteater::Entity().add<ComponentPosition>(-.5, .5)
                                        .add<ComponentVelocity>(.8, .8));
    engine.addEntity(aunteater::Entity().add<ComponentPosition>(.5, -.5)
                                        .add<ComponentVelocity>(.8, .8));

    FpsDisplay fps(.5);
    aunteater::Timer timer{glfwGetTime()};
    while (!glfwWindowShouldClose(window))
    {
        //render(window);
        timer.mark(glfwGetTime());

        aunteater::UpdateTiming updater;
        engine.update(timer, updater);

        updater.outputTimings(std::cout);

        fps.tick(timer.delta(), window);

        glfwPollEvents();
    }

    glfwTerminate();
}
