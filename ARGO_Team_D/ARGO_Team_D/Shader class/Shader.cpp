//#include "Shader.h"
//
//using namespace std;
//
//PFNGLCREATESHADERPROC glCreateShader;
//PFNGLSHADERSOURCEPROC glShaderSource;
//PFNGLCOMPILESHADERPROC glCompileShader;
//PFNGLGETSHADERIVPROC glGetShaderiv;
//PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
//PFNGLDELETESHADERPROC glDeleteShader;
//PFNGLATTACHSHADERPROC glAttachShader;
//PFNGLCREATEPROGRAMPROC glCreateProgram;
//PFNGLLINKPROGRAMPROC glLinkProgram;
//PFNGLVALIDATEPROGRAMPROC glValidateProgram;
//PFNGLGETPROGRAMIVPROC glGetProgramiv;
//PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
//PFNGLUSEPROGRAMPROC glUseProgram;
//PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
//PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
//PFNGLUNIFORM1FPROC glUniform1f;
//PFNGLUNIFORM1IPROC glUniform1i;
//PFNGLUNIFORM2IPROC glUniform2i;
//PFNGLUNIFORM3IPROC glUniform3i;
//PFNGLUNIFORM4IPROC glUniform4i;
//
//
//Shader::Shader(std::string newVertexFileName, std::string newFragmentFileName)
//{
//	if (setUpOpengl() < 0) {
//		fprintf(stderr, "Error Initializing %s\n", SDL_GetError());
//	}
//
//	ready = false;
//	vertexFileName = newVertexFileName;
//	fragmentFileName = newFragmentFileName;
//
//	if (load() < 1) {
//		cout << "Error loading shader source! " << endl;
//		return;
//	}
//
//	if (compile() < 1) {
//		cout << "Error compiling sources! " << endl;
//		return;
//	}
//
//	if (link() < 1) {
//		cout << "Error linking shader source! " << endl;
//		return;
//	}
//
//	ready = true;
//}
//
//bool Shader::use()
//{
//	if (ready) {
//		glUseProgram(shaderProgram);
//	}
//
//	return ready;
//}
//
//GLint Shader::getAttribute(std::string name)
//{
//	return glGetAttribLocation(shaderProgram, name.c_str());
//}
//
//
//int Shader::load() {
//	vertFile.open(vertexFileName, ios::in);
//	if (!vertFile) {
//		return -1;
//	}
//	vertexSourceStream << vertFile.rdbuf();
//
//	fragFile.open(fragmentFileName, ios::in);
//	if (!fragFile) {
//		return -2;
//	}
//	fragmentSourceStream << fragFile.rdbuf();
//
//	vertexSource = vertexSourceStream.str();
//	fragmentSource = fragmentSourceStream.str();
//
//	return 1;
//}
//
//int Shader::compile() {
//	const char* tempSource = vertexSource.c_str();
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &tempSource, 0);
//	glCompileShader(vertexShader);
//	GLint compiled;
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
//
//	if (compiled == false) {
//		unsigned int maxLength;
//		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
//		char* vertexCompileLog = (char*)malloc(maxLength);
//		glGetShaderInfoLog(vertexShader, maxLength, (GLsizei*)&maxLength, vertexCompileLog);
//		cout << "Vertex shader error: " << endl << vertexCompileLog << endl << endl;
//		free(vertexCompileLog);
//		return -1;
//	}
//
//	tempSource = fragmentSource.c_str();
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &tempSource, 0);
//	glCompileShader(fragmentShader);
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
//
//	if (compiled == false) {
//		unsigned int maxLength;
//		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
//		char* fragmentCompileLog = (char*)malloc(maxLength);
//		glGetShaderInfoLog(fragmentShader, maxLength, (GLsizei*)&maxLength, fragmentCompileLog);
//		cout << "Fragment shader error: " << endl << fragmentCompileLog << endl << endl;
//		free(fragmentCompileLog);
//		return -2;
//	}
//
//	return 1;
//}
//
//int Shader::link() {
//	shaderProgram = glCreateProgram();
//
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	GLint linked;
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
//
//	if (linked == false) {
//		unsigned int maxLength;
//		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
//		char* programLinkLog = (char*)malloc(maxLength);
//		glGetProgramInfoLog(shaderProgram, maxLength, (GLsizei*)&maxLength, programLinkLog);
//		cout << "Program link error: " << endl << endl;
//		free(programLinkLog);
//		return -1;
//	}
//
//	return 1;
//}
//
//GLint Shader::attrib(const GLchar* attribName) {
//	if (!attribName)
//		throw std::runtime_error("attribName was NULL");
//
//	GLint attrib = this->getAttribute(std::to_string(*attribName));
//	if (attrib == -1)
//		throw std::runtime_error(std::string("Program attribute not found: ") + attribName);
//
//	return attrib;
//}
//
//GLint Shader::uniform(const GLchar* uniformName) {
//	if (!uniformName)
//		throw std::runtime_error("uniformName was NULL");
//
//	GLint uniform = this->getAttribute(std::to_string(*uniformName));
//	if (uniform == -1)
//		throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);
//
//	return uniform;
//}
//
//int Shader::setUpOpengl()
//{
//	int result = 0;
//	glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
//	glShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
//	glCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
//	glGetShaderiv = (PFNGLGETSHADERIVPROC)SDL_GL_GetProcAddress("glGetShaderiv");
//	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog");
//	glDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
//	glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
//	glCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
//	glLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");
//	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)SDL_GL_GetProcAddress("glValidateProgram");
//	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv");
//	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");
//	glUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
//	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)SDL_GL_GetProcAddress("glGenFramebuffers");
//	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glGetAttribLocation");
//	glUniform1f = (PFNGLUNIFORM1FPROC)SDL_GL_GetProcAddress("glGetAttribLocation");
//	glUniform1i = (PFNGLUNIFORM1IPROC)SDL_GL_GetProcAddress("glGetAttribLocation");
//	glUniform2i = (PFNGLUNIFORM2IPROC)SDL_GL_GetProcAddress("glGetAttribLocation");
//	glUniform3i = (PFNGLUNIFORM3IPROC)SDL_GL_GetProcAddress("glGetAttribLocation");
//	glUniform4i = (PFNGLUNIFORM4IPROC)SDL_GL_GetProcAddress("glGetAttribLocation");
//
//	result = result && glCreateShader;
//	result = result && glShaderSource;
//	result = result && glCompileShader;
//	result = result && glGetShaderiv;
//	result = result && glGetShaderInfoLog;
//	result = result && glDeleteShader;
//	result = result && glAttachShader;
//	result = result && glCreateProgram;
//	result = result && glLinkProgram;
//	result = result && glValidateProgram;
//	result = result && glGetProgramiv;
//	result = result && glGetProgramInfoLog;
//	result = result && glUseProgram;
//	result = result && glGenFramebuffers;
//	result = result && glGetAttribLocation;
//	result = result && glUniform1f;
//	result = result && glUniform1i;
//	result = result && glUniform2i;
//	result = result && glUniform3i;
//	result = result && glUniform4i;
//
//	return result;
//}
//
//void Shader::setUniform(GLuint uniformName, float x) {
//	glUniform1f(uniformName, x);
//}
//
//void Shader::setUniform(GLuint uniformName, glm::vec2 v)
//{
//	GLint uniform = glGetAttribLocation(this->shaderProgram, (const GLchar*)uniformName);
//	if (uniform == -1)
//		std::cout << std::string("Program uniform not found: ") + to_string(uniformName);
//	glUniform2i(uniformName, v.x, v.y);
//}
//
//void Shader::setUniform(GLuint uniformName, glm::vec3 v) {
//	GLint uniform = glGetAttribLocation(this->shaderProgram, (const GLchar*)uniformName);
//	if (uniform == -1)
//		std::cout << std::string("Program uniform not found: ") + to_string(uniformName);
//	glUniform3i(uniformName, v.x, v.y, v.z);
//}
//
//void Shader::setUniform(GLuint uniformName, glm::vec4 v) {
//	GLint uniform = glGetAttribLocation(this->shaderProgram, (const GLchar*)uniformName);
//	if (uniform == -1)
//		std::cout << std::string("Program uniform not found: ") + to_string(uniformName);
//
//	glUniform4i(uniformName, v.r, v.g, v.b, v.a);
//}

