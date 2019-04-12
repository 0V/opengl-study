#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLWindow {
private:
    GLFWwindow* const window_;
    GLfloat size_[2];
    GLfloat scale_;
    GLfloat mouse_location_[2];

    static void resize(GLFWwindow* const window, int width, int height) {
        glViewport(0, 0, width, height);

        GLWindow* const instance(static_cast<GLWindow*>(glfwGetWindowUserPointer(window)));
        if (instance != NULL) {
            instance->size_[0] = static_cast<GLfloat>(width);
            instance->size_[1] = static_cast<GLfloat>(height);
        }
    }

public:
    GLWindow(const int width = 640, const int height = 480, const char* title = "Main Window")
        : window_(glfwCreateWindow(width, height, title, NULL, NULL)),
          scale_(100.0f), mouse_location_{ 0, 0 } {

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
        glfwSetWindowSizeCallback(window_, resize);

        resize(window_, width, height);
    }

    virtual ~GLWindow() {
        glfwDestroyWindow(window_);
    }

    GLfloat aspect() const { return size_[0] / size_[1]; }
    GLfloat scale() const { return scale_; }
    const GLfloat* size() const { return size_; }
    const GLfloat* mouse_location() const { return mouse_location_; }
    GLFWwindow* data() const { return window_; }

    int should_close() const {
        return glfwWindowShouldClose(window_);
    }

    void swap_buffers() {
        glfwSwapBuffers(window_);
        glfwWaitEvents();

        double x, y;
        glfwGetCursorPos(window_, &x, &y);

        mouse_location_[0] = static_cast<GLfloat>(x) * 2.0f / size_[0] - 1.0f;
        mouse_location_[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / size_[1];
    }
};