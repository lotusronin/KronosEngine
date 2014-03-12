#include "Shader.h"
#include <string.h>
#include <GL/glew.h>
#include <GL/gl.h>

Shader::Shader(){
    vs =
    "#version 120\n"
	"attribute vec3 pos;\n"
	"attribute vec2 texCoord;\n"
	"varying vec2 vTexCoord;\n"
	"void main(){\n"
	"	vTexCoord = texCoord;\n"
	"	gl_Position = vec4(pos, 1.0);\n"
	"}";

	fs =
	"#version 120\n"
	"uniform sampler2D myTexture;\n"
	"varying vec2 vTexCoord;\n"
	"void main(){\n"
	"	gl_FragColor = texture2D(myTexture, vTexCoord);\n"
	"}";

	vert_src = vs.c_str();
	frag_src = fs.c_str();
}

Shader::~Shader()
{}

void Shader::disable(){
    glUseProgram(0);
}

void Shader::enable(){
    glUseProgram(shaderProgram);
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Shader::compile(){
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

    error = 0;
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &error);
    if(error == GL_FALSE)
    {
        GLchar e[1024];
        glGetShaderInfoLog(fShader, sizeof(e), NULL, e);
        std::cout << "Error compiling fragment shader!!!!\n";
        std::cout << e;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);

    glBindAttribLocation(shaderProgram, 0, "pos");
    glBindAttribLocation(shaderProgram, 1, "texCoord");

    glLinkProgram(shaderProgram);
}
