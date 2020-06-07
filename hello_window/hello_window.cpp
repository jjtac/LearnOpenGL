#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int preWidth = 800;
int preHeight = 600;

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

        // Double Buffer swap
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
