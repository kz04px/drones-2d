#include "program.hpp"
#include <algorithm>
#include "shader.hpp"

Program::Program() : m_linked{false} {
    m_id = glCreateProgram();
}

Program::~Program() {
    glDeleteProgram(m_id);
}

void Program::link() {
    glLinkProgram(m_id);
    m_linked = true;
}

bool Program::valid() const {
    GLint status;
    glGetProgramiv(m_id, GL_LINK_STATUS, &status);
    return status == GL_TRUE;
}

void Program::attach(const Shader &shader) {
    auto it = find(m_shaders.begin(), m_shaders.end(), shader.id());
    if (it == m_shaders.end()) {
        m_shaders.push_back(shader.id());
        glAttachShader(m_id, shader.id());
    }
}

void Program::detach(const Shader &shader) {
    auto it = find(m_shaders.begin(), m_shaders.end(), shader.id());
    if (it != m_shaders.end()) {
        m_shaders.erase(it);
        glDetachShader(m_id, shader.id());
    }
}

void Program::use() const {
    if (m_linked) {
        glUseProgram(m_id);
    }
}

GLuint Program::id() const {
    return m_id;
}
