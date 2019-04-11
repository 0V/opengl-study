#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <string_view>
#include <fstream>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "objects/objects.h"
#include "value_sampler.h"

constexpr std::string_view VertexShader = "vertex shader";
constexpr std::string_view FragmentShader = "fragment shader";


class GLRender {

private:
    const char* ShaderParamPosition = "position";
    const char* ShaderParamFragment = "fragment";

    ValueSampler<double> sampler = ValueSampler<double>(-1, 1);
    ValueSampler<double> sampler01 = ValueSampler<double>(0, 1);

    void display_random() {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3d(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        for (size_t i = 0; i < 100; i++) {
            glColor3d(sampler01.sample(), sampler01.sample(), sampler01.sample());
            glVertex3d(sampler.sample(), sampler.sample(), sampler.sample());
        }
        glEnd();
        glFlush();
    }

    void display() {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POLYGON);
        glColor3d(1.0, 0.0, 0.0); /* 赤 */
        glVertex3d(-0.9, -0.9, -1);
        glColor3d(0.0, 1.0, 0.0); /* 緑 */
        glVertex3d(0.9, -0.9, -1);
        glColor3d(0.0, 0.0, 1.0); /* 青 */
        glVertex3d(0.9, 0.9, -1);
        glColor3d(1.0, 1.0, 0.0); /* 黄 */
        glVertex3d(-0.9, 0.9, -1);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3d(1.0, 0.0, 0.0); /* 赤 */
        glVertex2d(-0.5, -0.5);
        glColor3d(0.0, 1.0, 0.0); /* 緑 */
        glVertex2d(0.5, -0.5);
        glColor3d(0.0, 0.0, 1.0); /* 青 */
        glVertex2d(0.5, 0.5);
        glColor3d(1.0, 1.0, 0.0); /* 黄 */
        glVertex2d(-0.5, 0.5);
        glEnd();
        glFlush();
    }

    GLboolean print_shader_info(const GLuint& shader, const std::string_view& str) {

        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            std::cerr << "Compile Error in " << str << std::endl;
        }

        GLsizei buf_size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buf_size);

        if (buf_size > 1) {
            std::vector<GLchar> info_log(buf_size);
            GLsizei length;
            glGetShaderInfoLog(shader, buf_size, &length, &info_log[0]);
            std::cerr << &info_log[0] << std::endl;
        }

        return static_cast<GLboolean>(status);
    }

    GLboolean print_program_info(const GLuint& program) {
        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
            std::cerr << "Link Error." << std::endl;
        GLsizei bufSize;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
        if (bufSize > 1) {
            std::vector<GLchar> infoLog(bufSize);
            GLsizei length;
            glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
            std::cerr << &infoLog[0] << std::endl;
        }
        return static_cast<GLboolean>(status);
    }

    bool read_shader_file(const std::string& file_name, std::string& dist) {

        if (file_name.empty())
            return false;

        std::ifstream ifs(file_name);

        if (ifs.fail()) {
            return false;
        }
        std::string str();
        dist = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
        return true;
    }

    GLuint create_program(const std::string& vsrc, const std::string& fsrc) {

        const GLuint program(glCreateProgram());

        if (!vsrc.empty()) {
            const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
            const char* c_str = vsrc.data();
            glShaderSource(vobj, 1, &c_str, NULL);
            glCompileShader(vobj);

            if (print_shader_info(vobj, VertexShader)) {
                glAttachShader(program, vobj);
            }

            glDeleteShader(vobj);
        }

        if (!vsrc.empty()) {
            const GLuint vobj(glCreateShader(GL_FRAGMENT_SHADER));
            const char* c_str = fsrc.data();
            glShaderSource(vobj, 1, &c_str, NULL);
            glCompileShader(vobj);

            if (print_shader_info(vobj, FragmentShader)) {
                glAttachShader(program, vobj);
            }

            glDeleteShader(vobj);
        }

        glBindAttribLocation(program, 0, ShaderParamPosition);
        glBindFragDataLocation(program, 0, ShaderParamFragment);
        glLinkProgram(program);

        if (print_program_info(program)) {
            return program;
        }
        else {
            glDeleteProgram(program);
            return NULL;
        }
    }

    GLuint load_program(const std::string& vert, const std::string& frag) {
        std::string vsrc, fsrc;
        const bool vstat(read_shader_file(vert, vsrc));
        const bool fstat(read_shader_file(frag, fsrc));

        return (vstat && fstat) ? create_program(vsrc, fsrc) : 0;
    }

    void init() {
        glClearColor(1.0, 1.0, 1.0, 1.0);
    }

    void resize(int w, int h) {
        glViewport(0, 0, w, h);
        glLoadIdentity();
        glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
        //	glOrtho(-1, 1, -1, 1, -1.0, 1.0);
    }

    static GLuint create_object(GLuint vertices, const GLfloat (*position)[2]) {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * vertices, position, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return vao;
    }

public:
    GLRender() {
    }
    ~GLRender() {
    }

    int render() {
        if (glfwInit() == GL_FALSE) {
            std::cerr << "Can't initialize GLFW" << std::endl;
            return 1;
        }

        std::atexit(glfwTerminate);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* const window(glfwCreateWindow(640, 480, "Hello!", NULL, NULL));

        if (window == NULL) {
            std::cerr << "Can't create GLFW window." << std::endl;
            return 1;
        }

        glfwMakeContextCurrent(window);

        // GLEW initialization
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            std::cerr << "Can't initialize GLEW" << std::endl;
            return 1;
        }

        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

        const GLuint program(load_program("src/shaders/point.vert", "src/shaders/point.frag"));


        // 図形データ
        static constexpr Vertex vertex[] = {
            { -0.5f, -0.5f },
            { 0.5f, -0.5f },
            { 0.5f, 0.5f },
            { -0.5f, 0.5f }
        };

        std::unique_ptr<const GLShape> shape(new GLTriangleShape(2, 4, vertex));

        while (glfwWindowShouldClose(window) == GL_FALSE) {
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(program);

            shape->draw();

            glfwSwapBuffers(window);
            glfwWaitEventsTimeout(1);
        }

        return 0;
    }
};
