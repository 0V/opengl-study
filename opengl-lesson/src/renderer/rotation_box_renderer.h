#pragma once
#include <cstdio>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <cmath>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "box_renderer.h"


class RotationBoxRenderer : public BoxRenderer {
protected:
    double theta = 10;

    virtual void initializeGL() {
        glfwSwapInterval(0);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
    }
    
    virtual void animate() {
        theta += 2.0f * Pi / 10.0f; // 10分の1回転
    }

    // キューブの描画
    void drawCube() {
        glBegin(GL_TRIANGLES);
        for (int face = 0; face < 6; face++) {
            glColor3fv(colors[face]);
            for (int i = 0; i < 3; i++) {
                glVertex3fv(positions[indices[face * 2 + 0][i]]);
            }

            for (int i = 0; i < 3; i++) {
                glVertex3fv(positions[indices[face * 2 + 1][i]]);
            }
        }
        glEnd();
    }

    virtual void drawFrame() {
        // 背景色と深度値のクリア
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // ビューポート変換の指定 (MacのLetinaディスプレイだと変になる)
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

        setView();

        
    // 1つ目のキューブ
        glPushMatrix();
        glTranslatef(1.0f, 0.0f, 0.0f);
        glRotatef(theta, 0.0f, 1.0f, 0.0f);
        glScalef(0.5f, 0.5f, 0.5f);

        drawCube();
        glPopMatrix();

        // 2つ目のキューブ
        glPushMatrix();
        glTranslatef(-1.0f, 0.0f, 0.0f);
        glRotated(- 2.0f * theta, 0.0f, 1.0f, 0.0f);
        glScalef(0.5f, 0.5f, 0.5f);
        drawCube();
        glPopMatrix();
    }
};
