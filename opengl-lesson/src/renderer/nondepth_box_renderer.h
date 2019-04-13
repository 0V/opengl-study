#pragma once
#include <cstdio>
#include <cstdlib>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "renderer_base.h"

class NondepthBoxRenderer : public RendererBase {
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
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    virtual void drawFrame() { // �w�i�F�̕`��
        glClear(GL_COLOR_BUFFER_BIT);

        // �r���[�|�[�g�ϊ��̎w��
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

        // �ˉe�ϊ��s��
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

        // ���f���r���[�ϊ��s��
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(3.0f, 4.0f, 5.0f, // ���_�̈ʒu
            0.0f, 0.0f, 0.0f,       // ���Ă����
            0.0f, 1.0f, 0.0f);      // ���E�̏����

        // �����̂̕`��
        glBegin(GL_TRIANGLES);
        for (int face = 0; face < 6; face++) {
            // �ʂ̐F
            glColor3fv(colors[face]);

            // 1�̖�(�l�p�`)��2�̎O�p�`���琬��
            for (int i = 0; i < 3; i++) {
                glVertex3fv(positions[indices[face * 2 + 0][i]]);
            }

            for (int i = 0; i < 3; i++) {
                glVertex3fv(positions[indices[face * 2 + 1][i]]);
            }
        }
        glEnd();
    }
};
