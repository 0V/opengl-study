#pragma once
#include <cstdio>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "renderer_base.h"

class WindowRenderer : public RendererBase {
protected:
    virtual void initializeGL() {
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    }

    virtual void drawFrame() {
//        glClear(GL_COLOR_BUFFER_BIT);
    }
};