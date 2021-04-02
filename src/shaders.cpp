#include "headers/shaders.hpp"
#include <iostream>
#include <map>

std::map <GLenum, std::string> shaderTokens =
{
    {GL_VERTEX_SHADER, "vertex shader"}, 
    {GL_FRAGMENT_SHADER, "fragment shader"},
    {GL_GEOMETRY_SHADER, "geometry shader"}
};

Shader::Shader(const std::string& _verShaderPath, const std::string& _fragShaderPath, const std::string& _geomShaderPath)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    

    vertexShader = this->CompileShader(vertexShader, _verShaderPath, GL_VERTEX_SHADER);
    fragmentShader = this->CompileShader(fragmentShader, _fragShaderPath, GL_FRAGMENT_SHADER);
    geometryShader = this->CompileShader(geometryShader, _geomShaderPath, GL_GEOMETRY_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glAttachShader(program, geometryShader);

    glBindAttribLocation(program, 0, "vPosition");

    glLinkProgram(program);

    GLint isProgramLinked;
    glGetProgramiv(program, GL_LINK_STATUS, &isProgramLinked);

    if(isProgramLinked == GL_FALSE)
    {
        GLsizei length;
        char errMess[1024];

        glGetProgramInfoLog(program, 1024, &length, errMess);

        std::cerr << "Error of program linking \n error message::" << errMess;
    }
}

std::stringstream Shader::ParseShader(const std::string& _shaderPath)
{
    std::ifstream stream(_shaderPath);
    std::string line;
    std::stringstream shaderCode;

    while(getline(stream, line))
        shaderCode << "\n" << line;

    return shaderCode;
}

GLuint Shader::CompileShader(GLuint _shader, const std::string& _path, GLuint _shType)
{
    std::string shSource = this->ParseShader(_path).str();
    
    const char* src = shSource.c_str();
    GLint length = shSource.length();

    glShaderSource(_shader, 1, &src, &length);
    glCompileShader(_shader);

    GLint isShaderCompiled;

    glGetShaderiv(_shader, GL_COMPILE_STATUS, &isShaderCompiled);

    if(isShaderCompiled == GL_FALSE)
    {
        GLsizei length;
        char errorMess[1024];

        glGetShaderInfoLog(_shader, 1024, &length, errorMess);

        std::cerr << "Error of " << shaderTokens[_shType]
                    << " compilation. \n error message::" << errorMess;

        return 0;
    }

    return _shader;
}

void Shader::Bind()
{
    ASSERT(glUseProgram(program));
}

void Shader::Unbind()
{
    ASSERT(glUseProgram(0));
}