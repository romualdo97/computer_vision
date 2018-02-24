#include "Shader.h"



Shader::Shader()
{
	// do anything...
}

Shader::Shader(GLchar const *vertexPath, GLchar const *fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream ssVertexCode, ssFragmentCode;
		ssVertexCode << vShaderFile.rdbuf();
		ssFragmentCode << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = ssVertexCode.str();
		fragmentCode = ssFragmentCode.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR TRYING TO READ SHADER FILES\n";
	}
	// convert from string to c-like string
	char const *vertexCode_cstr = vertexCode.c_str();
	char const *fragmentCode_cstr = vertexCode.c_str();
}

Shader::Shader(GLchar const *shaderName)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::stringstream ssVertexPath, ssFragmentPath;
	ssVertexPath << shaderName << ".vert";
	ssFragmentPath << shaderName  << ".frag";
	std::string vertexPath = ssVertexPath.str();
	std::string fragmentPath = ssFragmentPath.str();

	std::cout << "Shader instanced will find source files at:\n\t";
	char const *vertexPath_cstr = vertexPath.c_str();
	char const *fragmentPath_cstr = fragmentPath.c_str();	
	std::cout << vertexPath_cstr << " and " << fragmentPath_cstr << "\n";

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		vShaderFile.open(vertexPath_cstr);
		fShaderFile.open(fragmentPath_cstr);
		std::stringstream ssVertexCode, ssFragmentCode;
		ssVertexCode << vShaderFile.rdbuf();
		ssFragmentCode << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = ssVertexCode.str();
		fragmentCode = ssFragmentCode.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR TRYING TO READ SHADER FILES\n";
	}
	// convert from string to c-like string
	char const *vertexCode_cstr = vertexCode.c_str();
	char const *fragmentCode_cstr = fragmentCode.c_str();
	
	// =====================================================
	// 2. compile shaders
	compileShader(vertexCode_cstr, fragmentCode_cstr);	
}

void Shader::compileShader(char const *vertex_src, char const *fragment_src)
{
	unsigned int vertexShader, fragmentShader;
	
	// compile vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_src, NULL);
	glCompileShader(vertexShader);
	checkCompileError(vertexShader, GL_VERTEX_SHADER, GL_COMPILE_STATUS);

	// compile fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_src, NULL);
	glCompileShader(fragmentShader);
	checkCompileError(fragmentShader, GL_FRAGMENT_SHADER, GL_COMPILE_STATUS);

	// link shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	checkCompileError(ID, NULL, GL_LINK_STATUS);

	/*std::cout << "\n================================================================\n";
	std::cout << "// VERTEX SHADER\n";
	std::cout << "\n" << vertex_src << std::endl;
	std::cout << "\n================================================================\n";
	std::cout << "// FRAGMENT SHADER\n";
	std::cout << "\n" << fragment_src << std::endl;*/

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::checkCompileError(unsigned int shader, unsigned int stage, unsigned int const status)
{
	char infolog[512];
	int succes;

	if (status == GL_COMPILE_STATUS && stage == GL_FRAGMENT_SHADER)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			glGetShaderInfoLog(shader, sizeof(infolog), NULL, infolog);
			std::cout << "ERROR WHILE COMPILING FRAGMENT SHADER\n";
			std::cout << infolog << std::endl;
		}
	}

	if (status == GL_COMPILE_STATUS && stage == GL_VERTEX_SHADER)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			glGetShaderInfoLog(shader, sizeof(infolog), NULL, infolog);
			std::cout << "ERROR WHILE COMPILING VERTEX SHADER\n";
			std::cout << infolog << std::endl;
		}
	}

	if (status == GL_LINK_STATUS)
	{
		glGetShaderiv(shader, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			glGetShaderInfoLog(shader, sizeof(infolog), NULL, infolog);
			std::cout << "ERROR WHILE LINKING SHADER PROGRAM\n";
			std::cout << infolog << std::endl;
		}
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(std::string const &name, bool value)
{
	unsigned int uniformLoc = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uniformLoc, value);
}

void Shader::setInt(std::string const &name, int value)
{
	unsigned int uniformLoc = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uniformLoc, value);
}

void Shader::setFloat(std::string const &name, float value)
{
	unsigned int uniformLoc = glGetUniformLocation(ID, name.c_str());
	glUniform1f(uniformLoc, value);
}

void Shader::setVec2(std::string const &name, float v0, float v1)
{
	unsigned int uniformLoc = glGetUniformLocation(ID, name.c_str());
	glUniform2f(uniformLoc, v0, v1);
}

Shader::~Shader()
{
}
