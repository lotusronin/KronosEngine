#ifndef __SHADER_H__
#define __SHADER_H__

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

class Shader{
public:
    Shader();
    ~Shader();
    const char* vert_src;
    const char* frag_src;
    std::string vs;
    std::string fs;
    //const unsigned int shaderAttribute = 0;
    void enable();
    void disable();
    void compile();
    GLuint vShader, fShader, shaderProgram;
};


#endif // __SHADER_H__
