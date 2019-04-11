#pragma once
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gl_shape.h"

class GLLoopShape : public GLShape {

public:
    GLLoopShape(const GLint& size, const GLsizei& vertex_count, const Vertex* vertex)
        : GLShape(size, vertex_count, vertex) {
    }

    virtual ~GLLoopShape() {
    }

    virtual void execute() const {
        glDrawArrays(GL_LINE_LOOP, 0, vertex_count_);
    }
};