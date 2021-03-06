#pragma once
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gl_object.h"

using GLObjectPtrConst = std::shared_ptr<const GLObject>;

class GLShape {
private:

protected:
    GLObjectPtrConst object;
    const GLsizei vertex_count_;

public:
    GLShape(const GLint& size, const GLsizei& vertex_count, const Vertex* vertex)
        : object(new GLObject(size, vertex_count, vertex)),
          vertex_count_(vertex_count) {
    }

    virtual ~GLShape() {
    }

    void draw() const {
        object->bind();
        execute();
    }

    virtual void execute() const = 0;
};