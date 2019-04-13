#pragma once
#include <cstdio>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "renderer_base.h"

class BufferSwapRenderer : public RendererBase {
protected:
    virtual void initializeGL() {
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    }

    virtual void drawFrame() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    virtual int draw(GLFWwindow* window) {

        bool is_front = false;

        while (glfwWindowShouldClose(window) == GL_FALSE) {
            if (is_front) {
                glDrawBuffer(GL_FRONT);
            }
            else {
                glDrawBuffer(GL_BACK);
            }

            is_front = !is_front;
            drawFrame();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        return 0;
    }

};