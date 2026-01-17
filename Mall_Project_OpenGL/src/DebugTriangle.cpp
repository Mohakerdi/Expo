#include <glad/glad.h>
#include <iostream>
#include <vector>

namespace Debug {
static GLuint compileFromSource(GLenum type, const char* src) {
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    GLint ok = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> buf(len);
        glGetShaderInfoLog(id, len, nullptr, buf.data());
        std::cerr << "Shader compile error: " << buf.data() << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static GLuint makeProgram() {
    const char* vs =
        "#version 330 core\n"
        "layout(location=0) in vec3 aPos;\n"
        "void main() { gl_Position = vec4(aPos, 1.0); }\n";
    const char* fs =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() { FragColor = vec4(1.0, 0.25, 0.25, 1.0); }\n";
    GLuint v = compileFromSource(GL_VERTEX_SHADER, vs);
    GLuint f = compileFromSource(GL_FRAGMENT_SHADER, fs);
    if (!v || !f) return 0;
    GLuint prog = glCreateProgram();
    glAttachShader(prog, v);
    glAttachShader(prog, f);
    glLinkProgram(prog);
    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> buf(len);
        glGetProgramInfoLog(prog, len, nullptr, buf.data());
        std::cerr << "Program link error: " << buf.data() << std::endl;
        glDeleteProgram(prog);
        prog = 0;
    }
    glDeleteShader(v);
    glDeleteShader(f);
    return prog;
}

void DrawTestTriangle() {
    static bool initialized = false;
    static GLuint vao = 0, vbo = 0, prog = 0;
    if (!initialized) {
        float verts[] = {
            0.0f,  0.5f, 0.0f,
           -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glBindVertexArray(0);
        prog = makeProgram();
        if (!prog) std::cerr << "Debug triangle shader program failed to create." << std::endl;
        initialized = true;
    }

    if (!prog) return;
    glDisable(GL_DEPTH_TEST); // ensure it draws over anything
    glUseProgram(prog);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
    glEnable(GL_DEPTH_TEST);
}
} // namespace Debug