#pragma once
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "renderer_base.h"


class BoxRenderer : public RendererBase {
protected:
    // 立方体の頂点位置
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

    // 立方体の面の色
    static constexpr float colors[6][3] = {
        { 1.0f, 0.0f, 0.0f }, // 赤
        { 0.0f, 1.0f, 0.0f }, // 緑
        { 0.0f, 0.0f, 1.0f }, // 青
        { 1.0f, 1.0f, 0.0f }, // イエロー
        { 0.0f, 1.0f, 1.0f }, // シアン
        { 1.0f, 0.0f, 1.0f }, // マゼンタ
    };

    // 立方体の面となる三角形の定義
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

    virtual void drawFrame() {
        // 背景色と深度値のクリア
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ビューポート変換の指定 (MacのLetinaディスプレイだと変になる)
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

        // 座標の変換
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(3.0f, 4.0f, 5.0f, // 視点の位置
            0.0f, 0.0f, 0.0f,       // 見ている先
            0.0f, 1.0f, 0.0f);      // 視界の上方向

        // 立方体の描画
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
