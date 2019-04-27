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

        // GLFW�Ǘ��̃E�B���h�E�T�C�Y��ύX
        glfwSetWindowSize(window, WIN_WIDTH, WIN_HEIGHT);

        // ���ۂ̃E�B���h�E�T�C�Y (�s�N�Z����) ���擾
        int renderBufferWidth, renderBufferHeight;
        glfwGetFramebufferSize(window, &renderBufferWidth, &renderBufferHeight);

        // �r���[�|�[�g�ϊ��̍X�V
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

            // �o�ߎ��Ԃ� 1 / FPS �ȏ�Ȃ�`�悷��
            if (currentTime - prevTime >= 1.0 / fps) {
                // �^�C�g����FPS��\��
                double realFps = 1.0 / (currentTime - prevTime);
                char winTitle[256];
                sprintf_s(winTitle, "%s (%.3f)", WIN_TITLE, realFps);
                glfwSetWindowTitle(window, winTitle);

                // �`��
                drawFrame();

                // �A�j���[�V����
                animate();

                // �`��p�o�b�t�@�̐؂�ւ�
                glfwSwapBuffers(window);
                glfwPollEvents();

                // �O��X�V���Ԃ̍X�V
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
        // OpenGL������������
        if (glfwInit() == GL_FALSE) {
            fprintf(stderr, "Initialization failed!\n");
            return 1;
        }

        // Window�̍쐬
        GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, NULL, NULL);
        std::atexit(glfwTerminate);

        if (window == NULL) {
            fprintf(stderr, "Window creation failed!");
            glfwTerminate();
            return 1;
        }

        glfwMakeContextCurrent(window);

        // �E�B���h�E�̃��T�C�Y�������֐��̓o�^
        glfwSetWindowSizeCallback(window, resizeGL);


        initializeGL();

        draw(window);
    }
};

int RendererBase::WIN_WIDTH = 500;
int RendererBase::WIN_HEIGHT = 500;
const char* RendererBase::WIN_TITLE = "OpenGL Course";
// double RendererBase::FPS = 30.0f;