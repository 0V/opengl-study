#pragma once
#include <cstdio>
#include <GLFW/glfw3.h>
#include <cstdlib>

constexpr int WIN_WIDTH = 500;
constexpr  int WIN_HEIGHT = 500;
const char* WIN_TITLE = "OpenGL Course";

class RendererBase {
protected:
    virtual void initializeGL() {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    virtual void drawFrame() {
    }

    virtual int draw(GLFWwindow* window) {

        while (glfwWindowShouldClose(window) == GL_FALSE) {
            drawFrame();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        return 0;
    }

public:
    RendererBase() {
    }

    virtual ~RendererBase() {
    }

    virtual int render() {
        // OpenGLÇèâä˙âªÇ∑ÇÈ
        if (glfwInit() == GL_FALSE) {
            fprintf(stderr, "Initialization failed!\n");
            return 1;
        }

        // WindowÇÃçÏê¨
        GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, NULL, NULL);
        std::atexit(glfwTerminate);

        if (window == NULL) {
            fprintf(stderr, "Window creation failed!");
            glfwTerminate();
            return 1;
        }

        glfwMakeContextCurrent(window);

        initializeGL();

        draw(window);
    }
};