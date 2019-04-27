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
        theta += 2.0f * Pi / 10.0f; // 10����1��]
    }

    // �L���[�u�̕`��
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
        // �w�i�F�Ɛ[�x�l�̃N���A
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // �r���[�|�[�g�ϊ��̎w�� (Mac��Letina�f�B�X�v���C���ƕςɂȂ�)
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

        setView();

        
    // 1�ڂ̃L���[�u
        glPushMatrix();
        glTranslatef(1.0f, 0.0f, 0.0f);
        glRotatef(theta, 0.0f, 1.0f, 0.0f);
        glScalef(0.5f, 0.5f, 0.5f);

        drawCube();
        glPopMatrix();

        // 2�ڂ̃L���[�u
        glPushMatrix();
        glTranslatef(-1.0f, 0.0f, 0.0f);
        glRotated(- 2.0f * theta, 0.0f, 1.0f, 0.0f);
        glScalef(0.5f, 0.5f, 0.5f);
        drawCube();
        glPopMatrix();
    }
};
