#pragma once
#include <GL/glew.h>

struct Vertex
{
    GLfloat position[2];
};

class GLObject
{
private:
    GLuint vao;
    GLuint vbo;
    GLObject(const GLObject& o) = delete;
    GLObject& operator=(const GLObject& o) = delete;

public:
    GLObject(GLint size, GLsizei vertexcount, const Vertex* vertex)
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexcount * sizeof(Vertex), vertex, GL_STATIC_DRAW);
        glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
    }

    virtual ~GLObject()
    {
        glDeleteBuffers(1, &vao);
        glDeleteBuffers(1, &vbo);
    }

    void bind() const
    {
        glBindVertexArray(vao);
    }

};