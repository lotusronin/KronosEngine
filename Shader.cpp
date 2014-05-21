#include "Shader.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>

Shader::Shader()
{

    vs ="";
	fs = "";
    //Load vertex shader
    vs = load("simpleshader.vert");
    //Load fragment shader
    fs = load("simpleshader.frag");

	vert_src = vs.c_str();
	frag_src = fs.c_str();
}

Shader::~Shader()
{}

void Shader::disable()
{
    glUseProgram(0);
}

void Shader::enable()
{
    glUseProgram(shaderProgram);
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Shader::compile()
{
    vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vShader, 1, &vert_src, 0);
	glShaderSource(fShader, 1, &frag_src, 0);

	glCompileShader(vShader);
	glCompileShader(fShader);

	//Error Check//
	GLint error = 0;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &error);
	if(error == GL_FALSE)
    {
        GLchar e[1024];
        glGetShaderInfoLog(vShader, sizeof(e), NULL, e);
        std::cout << "Error compiling vertex shader!!!!\n";
        std::cout << e;
    }
    else
    {
        std::cout << "vertex shader compiled successfully!\n";
    }

    error = 0;
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &error);
    if(error == GL_FALSE)
    {
        GLchar e[1024];
        glGetShaderInfoLog(fShader, sizeof(e), NULL, e);
        std::cout << "Error compiling fragment shader!!!!\n";
        std::cout << e;
    }
    else
    {
        std::cout << "fragment shader compiled successfully!\n";
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);

    glBindAttribLocation(shaderProgram, 0, "pos");
    glBindAttribLocation(shaderProgram, 1, "texCoord");

    glLinkProgram(shaderProgram);
}

std::string Shader::load(std::string filename)
{
    std::string s, temp;
    std::ifstream vsf (filename);
	if(vsf.is_open()){
		while(getline(vsf, temp))
		{
			s = s + temp + '\n';
		}
		vsf.close();
		std::cout << "Shader " << filename << " loaded...\n";
	}
	else{
		std::cout << "error opening shader file: " << filename << "\n";
	}
	return s;
}
