#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
// #include <math.h>

#include "shader.h"

GLuint preWidth = 800, preHeight = 600;

void key_callback(GLFWwindow *window, int key, int scanCode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    if (yoffset > 0 && preWidth < 1200)
    {
        preWidth += 40;
        preHeight += 30;
    }
    else if (yoffset < 0 && preWidth > 400)
    {
        preWidth -= 40;
        preHeight -= 30;
    }

    glfwSetWindowSize(window, preWidth, preHeight);
}

int main(int argc, char const *argv[])
{
    // init glfw
    glfwInit();
    // openGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(preWidth, preHeight, "window_name", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "fail to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // init glew
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "fail to init glew" << std::endl;
        return -1;
    }

    // set callback
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // glfwSetScrollCallback(window,)

    // init viewpoint
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);

    // init shader
    Shader ourShader("shader/shader.vs", "shader/shader.frag");

    // max vertex number
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "max nr of vertex attributes supported: " << nrAttributes << std::endl;

    GLfloat vertices[] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 左下角
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // 顶点
    };

    GLuint indices[] = {0, 1, 2};

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //bind vertex array object && vertex buffer object
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // bind vertices data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // location info
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // color info
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // unbind VAO && VBO && EBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // wireframe mode: only draw line
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // loop
    while (!glfwWindowShouldClose(window))
    {
        // check keyboard,mouse,...,events
        glfwPollEvents();

        // clear color buffer
        // sel color to clean
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // set buffer to clean
        glClear(GL_COLOR_BUFFER_BIT);

        // draw triangle
        ourShader.Use();

        // // get color && uniform loc
        // GLfloat timeValue = glfwGetTime();
        // GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        // GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
        // //set uniform value
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        // change to draw elements
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Double Buffer swap
        glfwSwapBuffers(window);
    }
    // delete resource
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
