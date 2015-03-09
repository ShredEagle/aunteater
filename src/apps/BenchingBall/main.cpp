#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
 
#define POSITION_ATTRIB 0
#define COLOR_ATTRIB 1

GLfloat vert_data[] = {
  -1.0, -1.0, 0.0,
  1.0, -1.0, 0.0,
  0.0, 1.0, 0.0,
};
 
GLfloat col_data[] = {
  1.0, 0.0, 0.0,
  0.0, 1.0, 0.0,
  0.0, 0.0, 1.0
};

const char* vert_shader = R"#(
    #version 150

    in vec3 position;
    in vec3 color;
    out vec3 vcol;

    void main(void)
    {
        vcol = color;
        gl_Position = vec4(position, 1.0);
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
 
void init(void)
{
    GLuint vao;
    GLuint bufs[2];
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, bufs);
   
    glBindVertexArray(vao);
    glEnableVertexAttribArray(POSITION_ATTRIB);
    glEnableVertexAttribArray(COLOR_ATTRIB);
   
    glBindBuffer(GL_ARRAY_BUFFER, bufs[0]);
    glBufferData(GL_ARRAY_BUFFER, 3*3*sizeof(GLfloat), vert_data, GL_STATIC_DRAW);
    glVertexAttribPointer(POSITION_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
    glBindBuffer(GL_ARRAY_BUFFER, bufs[1]);
    glBufferData(GL_ARRAY_BUFFER, 3*3*sizeof(GLfloat), col_data, GL_STATIC_DRAW);
    glVertexAttribPointer(COLOR_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
    GLuint prog;
    GLuint vert;
    GLuint frag;
   
    prog = glCreateProgram();
    vert = glCreateShader(GL_VERTEX_SHADER);
    frag = glCreateShader(GL_FRAGMENT_SHADER);
   
    glShaderSource(vert, 1, &vert_shader, 0);
    glShaderSource(frag, 1, &frag_shader, 0);
    glCompileShader(vert);
    glCompileShader(frag);
   
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
   
    glBindAttribLocation(prog, POSITION_ATTRIB, "position");
    glBindAttribLocation(prog, COLOR_ATTRIB, "color");
   
    glLinkProgram(prog);
    glUseProgram(prog);
}
 
void render(GLFWwindow *window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
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