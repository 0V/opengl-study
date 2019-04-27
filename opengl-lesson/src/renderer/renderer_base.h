#pragma once

#define GLFW_INCLUDE_GLU
#include <cstdio>
#include <GLFW/glfw3.h>
#include <cstdlib>

const float Pi = std::atan(1.0) * 4.0;

class RendererBase {
protected:
    static int WIN_WIDTH;
    static int WIN_HEIGHT;
    static const char* WIN_TITLE;
    double fps = 120;

    static void resizeGL(GLFWwindow* window, int width, int height) {
        WIN_WIDTH = width;
        WIN_HEIGHT = height;

        // GLFW管理のウィンドウサイズを変更
        glfwSetWindowSize(window, WIN_WIDTH, WIN_HEIGHT);

        // 実際のウィンドウサイズ (ピクセル数) を取得
        int renderBufferWidth, renderBufferHeight;
        glfwGetFramebufferSize(window, &renderBufferWidth, &renderBufferHeight);

        // ビューポート変換の更新
        glViewport(0, 0, renderBufferWidth, renderBufferHeight);
    }

    virtual void initializeGL() {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    virtual void drawFrame() {
    }

    virtual void animate() {
    }

    virtual int draw(GLFWwindow* window) {
        double prevTime = glfwGetTime();
        while (glfwWindowShouldClose(window) == GL_FALSE) {
            double currentTime = glfwGetTime();

            // 経過時間が 1 / FPS 以上なら描画する
            if (currentTime - prevTime >= 1.0 / fps) {
                // タイトルにFPSを表示
                double realFps = 1.0 / (currentTime - prevTime);
                char winTitle[256];
                sprintf_s(winTitle, "%s (%.3f)", WIN_TITLE, realFps);
                glfwSetWindowTitle(window, winTitle);

                // 描画
                drawFrame();

                // アニメーション
                animate();

                // 描画用バッファの切り替え
                glfwSwapBuffers(window);
                glfwPollEvents();

                // 前回更新時間の更新
                prevTime = currentTime;
            }
        }

        while (glfwWindowShouldClose(window) == GL_FALSE) {
            drawFrame();
            animate();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        return 0;
    }

public:
    RendererBase() {
    }

    virtual ~RendererBase() {
    }

    virtual int render() {
        // OpenGLを初期化する
        if (glfwInit() == GL_FALSE) {
            fprintf(stderr, "Initialization failed!\n");
            return 1;
        }

        // Windowの作成
        GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, NULL, NULL);
        std::atexit(glfwTerminate);

        if (window == NULL) {
            fprintf(stderr, "Window creation failed!");
            glfwTerminate();
            return 1;
        }

        glfwMakeContextCurrent(window);

        // ウィンドウのリサイズを扱う関数の登録
        glfwSetWindowSizeCallback(window, resizeGL);


        initializeGL();

        draw(window);
    }
};

int RendererBase::WIN_WIDTH = 500;
int RendererBase::WIN_HEIGHT = 500;
const char* RendererBase::WIN_TITLE = "OpenGL Course";
// double RendererBase::FPS = 30.0f;