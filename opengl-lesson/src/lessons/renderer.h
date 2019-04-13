#pragma once
#include <cstdio>
#include <GLFW/glfw3.h>



constexpr int WIN_WIDTH = 500;
constexpr  int WIN_HEIGHT = 500;
const char* WIN_TITLE = "OpenGL Course";

class Renderer {

public:
    Renderer() {
    }

    virtual ~Renderer() {
    }


    void initializeGL() {
        // �w�i�F�̐ݒ�
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    }

    // ���[�U��`��OpenGL�`��
    void paintGL() {
        // �w�i�F�̕`��
        glClear(GL_COLOR_BUFFER_BIT);
    }

    int render() {
        // OpenGL������������
        if (glfwInit() == GL_FALSE) {
            fprintf(stderr, "Initialization failed!\n");
            return 1;
        }

        // Window�̍쐬
        GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE,
            NULL, NULL);
        if (window == NULL) {
            fprintf(stderr, "Window creation failed!");
            glfwTerminate();
            return 1;
        }

        // OpenGL�̕`��Ώۂ�Window��ǉ�
        glfwMakeContextCurrent(window);

        // ������
        initializeGL();

        // ���C�����[�v
        while (glfwWindowShouldClose(window) == GL_FALSE) {
            // �`��
            paintGL();

            // �`��p�o�b�t�@�̐؂�ւ�
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
};