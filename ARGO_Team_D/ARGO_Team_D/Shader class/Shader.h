//#ifndef SHADER_H
//#define SHADER_H
//
//#include <string>
//#include <sstream>
//#include <iostream>
//#include <fstream>
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <SDL.h>
//#include <SDL_opengl.h>
//#include <SDL_opengl_glext.h>
//#include <glm/glm.hpp>
//
//class Shader {
//public:
//	Shader(std::string vertexFileName, std::string fragmentFileName);
//	bool use();
//	GLint getAttribute(std::string name);
//	GLint attrib(const GLchar * attribName);
//	GLint uniform(const GLchar * uniformName);
//	void setUniform(GLuint uniformName, float x);
//	void setUniform(GLuint uniformName, glm::vec2 v);
//	void setUniform(GLuint uniformName, glm::vec3 v);
//	void setUniform(GLuint uniformName, glm::vec4 v);
//
//private:
//	std::ifstream vertFile, fragFile;
//	std::string vertexFileName, fragmentFileName;
//	std::stringstream vertexSourceStream, fragmentSourceStream;
//	std::string vertexSource, fragmentSource;
//	GLuint vertexShader, fragmentShader, shaderProgram;
//	bool ready;
//	int load();
//	int compile();
//	int link();
//	int setUpOpengl();
//};
//#endif