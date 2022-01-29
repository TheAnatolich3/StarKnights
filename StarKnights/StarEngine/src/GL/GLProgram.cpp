#include <iostream>
#include <GL/GLHeaders.hpp>
#include <fstream>
#include <string>
#include <string_view>
#include <glm/gtc/type_ptr.hpp>
#include <GL/GLTexture.hpp>
#include "GLProgram.hpp"

std::string read_shader(const std::string_view file_name)
{
    std::string line, text;
    std::ifstream in(file_name.data());

    if (in.is_open())
    {
        while (!in.eof())
        {
            getline(in, line);
            text += line;
            text += '\n';
        }
    }
    in.close();
    return text;
}

GLProgram::GLProgram(std::string_view vs_str, std::string_view ps_str)
{
    std::string v_str = read_shader(vs_str);
    std::string p_str = read_shader(ps_str);
    const char* vs = v_str.data();
    const char* ps = p_str.data();

    _vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertexShader, 1, &vs, nullptr);
    glCompileShader(_vertexShader);

    GLint success;
    GLchar infoLog[2048];
    glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(_vertexShader, 2048, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragmentShader, 1, &ps, nullptr);
    glCompileShader(_fragmentShader);

    glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(_fragmentShader, 2048, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    _program = glCreateProgram();

    glAttachShader(_program, _vertexShader);
    glAttachShader(_program, _fragmentShader);
    glLinkProgram(_program);

    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_program, 2048, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }

    GLint i, count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 16; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTES, &count);
    printf("Active Attributes: %d\n", count);

    for (i = 0; i < count; i++)
    {
        glGetActiveAttrib(_program, i, bufSize, &length, &size, &type, name);

        printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
    }

    glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &count);
    printf("Active Uniforms: %d\n", count);

    for (i = 0; i < count; i++)
    {
        glGetActiveUniform(_program, i, bufSize, &length, &size, &type, name);

        printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
    }
}

GLProgram::~GLProgram()
{
    glDeleteProgram(_program);
    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);
}


void GLProgram::activate()
{
    glUseProgram(_program);
}

std::shared_ptr<TextureUniform> GLProgram::createTextureUniform(std::string_view name)
{
    return std::make_shared<GLTextureUniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
}

std::shared_ptr<Mat3Uniform> GLProgram::createMat3Uniform(std::string_view name)
{
    return std::make_shared<GLMat3Uniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
}

std::shared_ptr<Vec2Uniform> GLProgram::createVec2Uniform(std::string_view name)
{
    return std::make_shared<GLVec2Uniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
}

std::shared_ptr<Vec3Uniform> GLProgram::createVec3Uniform(std::string_view name)
{
    return std::make_shared<GLVec3Uniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
}

std::shared_ptr<FloatUniform> GLProgram::createFloatUniform(std::string_view name)
{
    return std::make_shared<GLFloatUniform>(std::static_pointer_cast<GLProgram>(shared_from_this()), name);
}

void GLTextureUniform::activateWithSlot(size_t slot)
{
    Uniform::activate();
    auto glTexture = std::dynamic_pointer_cast<GLTexture>(texture);
    if (glTexture)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glTexture->active();
        glUniform1i(_location, slot);
    }
}

void GLTextureUniform::activate()
{
    activateWithSlot(0);
}

GLTextureUniform::GLTextureUniform(const std::shared_ptr<GLProgram>& program, std::string_view name)
{
    _location = glGetUniformLocation(program->getProgramId(), name.data());
}

GLMat3Uniform::GLMat3Uniform(const std::shared_ptr<GLProgram>& program, std::string_view name)
{
    _location = glGetUniformLocation(program->getProgramId(), name.data());
}

void GLMat3Uniform::activate()
{
    Uniform::activate();
    glUniformMatrix3fv(_location, 1, GL_FALSE, glm::value_ptr(value));
}

GLVec2Uniform::GLVec2Uniform(const std::shared_ptr<GLProgram>& program, std::string_view name)
{
    _location = glGetUniformLocation(program->getProgramId(), name.data());
}

void GLVec2Uniform::activate()
{
    Uniform::activate();
    glUniform2f(_location, value.x, value.y);
}

GLVec3Uniform::GLVec3Uniform(const std::shared_ptr<GLProgram>& program, std::string_view name)
{
    _location = glGetUniformLocation(program->getProgramId(), name.data());
}

void GLVec3Uniform::activate()
{
    Uniform::activate();
    glUniform3f(_location, value.x, value.y, value.z);
}

GLFloatUniform::GLFloatUniform(const std::shared_ptr<GLProgram>& program, std::string_view name)
{
    _location = glGetUniformLocation(program->getProgramId(), name.data());
}

void GLFloatUniform::activate()
{
    Uniform::activate();
    glUniform1f(_location, value);
}