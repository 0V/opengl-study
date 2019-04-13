#pragma once
#include <cstdio>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "renderer_base.h"

class SingleTriangleRenderer : public RendererBase {
protected:
    virtual void initializeGL() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    virtual void drawFrame() {
        // �w�i�F�̕`��
        glClear(GL_COLOR_BUFFER_BIT);

        // ����͈͂̎w��
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);

        // �O�p�`�̕`��
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // ��
        glVertex2f(-1.0f, -1.0f);
        glColor3f(0.0f, 1.0f, 0.0f); // ��
        glVertex2f(-1.0f, 1.0f);
        glColor3f(0.0f, 0.0f, 1.0f); // ��
        glVertex2f(1.0f, -1.0f);
        glEnd();
    }
};