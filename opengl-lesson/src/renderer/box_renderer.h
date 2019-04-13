#pragma once
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "renderer_base.h"


class BoxRenderer : public RendererBase {
protected:
    // �����̂̒��_�ʒu
    static constexpr float positions[8][3] = {
        { -1.0f, -1.0f, -1.0f },
        { 1.0f, -1.0f, -1.0f },
        { -1.0f, 1.0f, -1.0f },
        { -1.0f, -1.0f, 1.0f },
        { 1.0f, 1.0f, -1.0f },
        { -1.0f, 1.0f, 1.0f },
        { 1.0f, -1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f }
    };

    // �����̖̂ʂ̐F
    static constexpr float colors[6][3] = {
        { 1.0f, 0.0f, 0.0f }, // ��
        { 0.0f, 1.0f, 0.0f }, // ��
        { 0.0f, 0.0f, 1.0f }, // ��
        { 1.0f, 1.0f, 0.0f }, // �C�G���[
        { 0.0f, 1.0f, 1.0f }, // �V�A��
        { 1.0f, 0.0f, 1.0f }, // �}�[���^
    };

    // �����̖̂ʂƂȂ�O�p�`�̒�`
    static constexpr unsigned int indices[12][3] = {
        { 1, 6, 7 }, { 1, 7, 4 },
        { 2, 5, 7 }, { 2, 7, 4 },
        { 3, 5, 7 }, { 3, 7, 6 },
        { 0, 1, 4 }, { 0, 4, 2 },
        { 0, 1, 6 }, { 0, 6, 3 },
        { 0, 2, 5 }, { 0, 5, 3 }
    };

    virtual void initializeGL() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
    }

    void setView() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //*
        float fov = 45.0f;
        float tant = std::tan(Pi / 180.0f * (fov * 0.5));
        float aspect = (float)WIN_WIDTH / (float)WIN_HEIGHT;
        float z_near = 0.1f;
        float z_far = 1000.0f;
        float mat[16] = { 0 };
        mat[0] = 1.0f / (tant * aspect);
        mat[5] = 1.0f / tant;
        mat[10] = (z_near + z_far) / (z_near - z_far);
        mat[14] = (2.0f * z_near * z_far) / (z_near - z_far);
        mat[11] = -1.0f;

        glMultMatrixf(mat);

        /*/
        gluPerspective(45.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
        //        gluPerspective(45.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 6.7f);
        //*/

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(3.0f, 4.0f, 5.0f, // ���_�̈ʒu
            0.0f, 0.0f, 0.0f,       // ���Ă����
            0.0f, 1.0f, 0.0f);      // ���E�̏����

    }

    virtual void drawFrame() {
        // �w�i�F�Ɛ[�x�l�̃N���A
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // �r���[�|�[�g�ϊ��̎w�� (Mac��Letina�f�B�X�v���C���ƕςɂȂ�)
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

        setView();

        // �����̂̕`��
        glBegin(GL_TRIANGLES);
        for (int face = 0; face < 6; face++) {
            //glColor3fv(colors[face]);
            for (int i = 0; i < 3; i++) {
                glColor3fv(colors[face]);
                glVertex3fv(positions[indices[face * 2 + 0][i]]);
            }

            for (int i = 0; i < 3; i++) {
                glColor3fv(colors[face]);
                glVertex3fv(positions[indices[face * 2 + 1][i]]);
            }
        }
        glEnd();
    }
};
