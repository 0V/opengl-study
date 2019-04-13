#pragma once
#include <cstdio>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "renderer_base.h"

class SingleTriangleRenderer : public RendererBase {
protected:
    float dc = 0.01;
    //    float colors[3] = { 0.1, 0.5, 0.8 };
    float colors[3] = { 0, 0, 0 };

    void normalize() {
        for (size_t i = 0; i < 3; i++) {
            if (colors[i] > 1) {
                colors[i] -= 1;
            }
        }
    }

    virtual void initializeGL() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }



    virtual void drawFrame() {
        // îwåiêFÇÃï`âÊ
        glClear(GL_COLOR_BUFFER_BIT);

        // å©ÇÈîÕàÕÇÃéwíË
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //glRotatef(180, 0, 0, 1);
        //glScalef(0.5, 0.5, 1);
        //glTranslatef(0.5, 0.5, 0);
//        glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);
        glOrtho(10, 20, 10, 20, -1.0f, 1.0f);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // ê‘
        glVertex2f(12,12);
        glColor3f(0.0f, 1.0f, 0.0f); // óŒ
        glVertex2f(12, 18);
        glColor3f(0.0f, 0.0f, 1.0f); // ê¬
        glVertex2f(18, 12);
        glEnd();


        //glBegin(GL_TRIANGLES);
        //glColor3f(1.0f, 0.0f, 0.0f); // ê‘
        //glVertex2f(-1.0f, -1.0f);
        //glVertex2f(12,12);
        //glColor3f(0.0f, 1.0f, 0.0f); // óŒ
        //glVertex2f(-1.0f, 1.0f);
        //glColor3f(0.0f, 0.0f, 1.0f); // ê¬
        //glVertex2f(1.0f, -1.0f);
        //glEnd();

        //// éOäpå`ÇÃï`âÊ
        //glBegin(GL_TRIANGLES);
        //glColor3f(1.0f, 1.0f, 0.0f); // ê‘
        //glVertex2f(-1.8f, -1.8f);
        //glColor3f(0.0f, 1.0f, 1.0f); // óŒ
        //glVertex2f(-1.8f, 1.8f);
        //glColor3f(1.0f, 0.0f, 1.0f); // ê¬
        //glVertex2f(1.0f, -1.0);

        //glColor3fv(colors);
        //glVertex2f(-1.0f, -1.0f);
        //glVertex2f(-1.0f, 1.0f);
        //glVertex2f(1.0f, -1.0f);

        //for (size_t i = 0; i < 3; i++) {
        //    colors[i] += dc;
        //}

        //normalize();

        glEnd();
    }
};