#pragma once
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gl_shape.h"

class GLTriangleShape : public GLShape {

public:
    GLTriangleShape(const GLint& size, const GLsizei& vertex_count, const Vertex* vertex)
        : GLShape(size, vertex_count, vertex) {
    }

    virtual ~GLTriangleShape() {
    }

    virtual void execute() const {
        glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
    }
};