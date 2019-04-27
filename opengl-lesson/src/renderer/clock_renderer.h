#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <stdlib.h>


#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "renderer_base.h"


class ClockRenderer : public RendererBase {
protected:
    double radius = 10;
    float dc = 0.01;
    double colors[3] = { 0.1, 0.5, 0.8 };

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

    void drawClockHand(double angle, double scale, double* cols) {

        glPushMatrix();
        glRotatef(angle, 0.0f, 0.0f, -1.0f);

        glBegin(GL_TRIANGLES);
        glColor3dv(cols);
        glVertex2f(0, scale * 0.98);
        glVertex2f(0.02, 0);
        glVertex2f(-0.02, 0);
        glEnd();

        glPopMatrix();
    }

    virtual void drawFrame() {
        time_t t = time(nullptr);
        tm timeInf;
        localtime_s(&timeInf, &t);

        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(-1, 1, -1, 1, -0.01f, 10.0f);

        drawClockHand((double)timeInf.tm_hour * 30, 0.8, colors);
        drawClockHand((double)timeInf.tm_min * 6, 1, colors);
        drawClockHand((double)timeInf.tm_sec * 6, 0.6, colors);

        std::cout << "local:     " << std::put_time(&timeInf, "%c %Z") << '\n';

        //// ŽOŠpŒ`‚Ì•`‰æ
        //glBegin(GL_TRIANGLES);
        //glColor3f(1.0f, 1.0f, 0.0f); // Ô
        //glVertex2f(-1.8f, -1.8f);
        //glColor3f(0.0f, 1.0f, 1.0f); // —Î
        //glVertex2f(-1.8f, 1.8f);
        //glColor3f(1.0f, 0.0f, 1.0f); // Â
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
