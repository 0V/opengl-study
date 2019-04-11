#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Vertex {
    GLfloat position[2];
};

class GLObject {
private:
    GLuint vertex_array;
    GLuint vertex_buffer;
    GLObject(const GLObject& o) = delete;
    GLObject& operator=(const GLObject& o) = delete;

public:
    GLObject(GLint size, GLsizei vertex_count, const Vertex* vertex) {
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertex, GL_STATIC_DRAW);
        glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
    }

    virtual ~GLObject() {
        glDeleteBuffers(1, &vertex_array);
        glDeleteBuffers(1, &vertex_buffer);
    }

    void bind() const {
        glBindVertexArray(vertex_array);
    }
};