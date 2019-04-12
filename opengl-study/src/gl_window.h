#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLWindow {
private:
    GLFWwindow* const window_;
    GLfloat aspect_;

    static void resize(GLFWwindow* const window, int width, int height) {
        glViewport(0, 0, width, height);

        GLWindow* const instance(static_cast<GLWindow*>(glfwGetWindowUserPointer(window)));
        if (instance != NULL) {
            instance->aspect_ = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
        }
    }

public:

    GLWindow(const int width = 640, const int height = 480, const char* title = "Main Window")
        : window_(glfwCreateWindow(width, height, title, NULL, NULL)) {
        if (window_ == NULL) {
            std::cerr << "Cant create GLFW window." << std::endl;
            exit(1);
        }

        glfwMakeContextCurrent(window_);

        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK) {
            std::cerr << "Can't initialize GLEW" << std::endl;
        }

        glfwSwapInterval(1);
        glfwSetWindowUserPointer(window_, this);
        glfwSetWindowPosCallback(window_, resize);

        resize(window_, width, height);
    }

    virtual ~GLWindow() {
        glfwDestroyWindow(window_);
    }

    GLfloat aspect() const { return aspect_; }

    int should_close() const {
        return glfwWindowShouldClose(window_);
    }

    void swap_buffers() {
        glfwSwapBuffers(window_);
        glfwWaitEvents();
    }
};