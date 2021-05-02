#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader() {
}

Shader::~Shader() {
    glDeleteShader(m_id);
}

[[nodiscard]] Shader Shader::from_string(const Type t, const std::string &text) {
    Shader s;

    switch (t) {
        case Type::Vertex:
            s.m_id = glCreateShader(GL_VERTEX_SHADER);
            break;
        case Type::Fragment:
            s.m_id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            std::exit(1);
    }

    const char *source = text.c_str();
    const int length = text.size();
    s.m_type = t;
    glShaderSource(s.id(), 1, &source, &length);
    glCompileShader(s.id());

    if (!s.valid()) {
        std::cerr << "Shader compile error" << std::endl;
        std::exit(1);
    }

    return s;
}

[[nodiscard]] Shader Shader::from_file(const Type t, const std::string &path) {
    std::ifstream f(path);

    if (!f.is_open()) {
        throw std::invalid_argument("Can't open file " + path);
    }

    std::stringstream buffer;
    buffer << f.rdbuf();

    return from_string(t, buffer.str());
}

GLuint Shader::id() const noexcept {
    return m_id;
}

bool Shader::valid() const noexcept {
    GLint status;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
    return status == GL_TRUE;
}

Shader::Type Shader::type() const noexcept {
    return m_type;
}
