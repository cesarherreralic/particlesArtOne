#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\type_ptr.hpp>

class Shader
{
private:
	GLuint id;

	std::string loadShaderSource(char* fileName)
	{
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;

		//Vertex
		in_file.open(fileName);

		if (in_file.is_open()) {
			while (std::getline(in_file, temp)) {
				src += temp + "\n";
			}
		}
		else std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << fileName << "\n";

		in_file.close();

		return src;
	}

	GLuint loadShader(GLenum type, char* fileName)
	{
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << "\n";
			std::cout << infoLog << "\n";
		}

		return shader;
	}

	GLuint loadComputeShader(char* fileName)
	{
		char infoLog[512];
		GLint success;

		GLuint computeShaderID = glCreateShader(GL_COMPUTE_SHADER);
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(computeShaderID, 1, &src, NULL);
		glCompileShader(computeShaderID);

		glGetShaderiv(computeShaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(computeShaderID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << "\n";
			std::cout << infoLog << "\n";
		}

		return computeShaderID;
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader, const GLchar* feedbackVaryings[] = 0, const GLuint feedbackVaryingsLength = 0)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();
		glUseProgram(this->id);

		glAttachShader(this->id, vertexShader);

		if (geometryShader)
		{
			glAttachShader(this->id, geometryShader);
		}

		glAttachShader(this->id, fragmentShader);

		// Definir los nombres de las variables de salida en el shader
		//const GLchar* feedbackVaryings[] = { "outPosition", "outVelocity" };
		if (feedbackVaryings != 0) {
			// Vincular las variables de feedback antes de enlazar el shader program
			glTransformFeedbackVaryings(this->id, feedbackVaryingsLength, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
		}

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM: " << "\n";
			std::cout << infoLog << "\n";
		}
		glUseProgram(0);
	}

	void linkComputeProgram(GLuint computeShader)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();
		glUseProgram(this->id);

		glAttachShader(this->id, computeShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR::COMPUTE_SHADER::COULD_NOT_LINK_PROGRAM: " << "\n";
			std::cout << infoLog << "\n";
		}
		glUseProgram(0);
	}

public:

	Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile = "", const GLchar* feedbackVaryings[] = 0, const GLuint feedbackVaryingsLength = 0)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, (char*)vertexFile);

		if (geometryFile != "")
			geometryShader = loadShader(GL_GEOMETRY_SHADER, (char*)geometryFile);

		fragmentShader = loadShader(GL_FRAGMENT_SHADER, (char*)fragmentFile);

		this->linkProgram(vertexShader, geometryShader, fragmentShader, feedbackVaryings, feedbackVaryingsLength);

		// End
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteShader(geometryShader);
	}

	Shader(const char* computeFile)
	{
		GLuint computeShader = 0;

		computeShader = loadComputeShader((char*)computeFile);

		this->linkComputeProgram(computeShader);

		// End
		glDeleteShader(computeShader);
	}


	~Shader()
	{
		glDeleteProgram(this->id);
	}

	//Set uniform functions
	void use()
	{
		glUseProgram(this->id);
	}

	void unuse()
	{
		glUseProgram(0);
	}

	void set1i(GLint value, const GLchar* name)
	{
		this->use();

		glUniform1i(glGetUniformLocation(this->id, name), value);

		this->unuse();
	}

	void set1f(GLfloat value, const GLchar* name)
	{
		this->use();

		glUniform1f(glGetUniformLocation(this->id, name), value);

		this->unuse();
	}

	void setVec2f(glm::fvec2 value, const GLchar* name)
	{
		this->use();

		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setVec3f(glm::fvec3 value, const GLchar* name)
	{
		this->use();

		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setVec4f(glm::fvec4 value, const GLchar* name)
	{
		this->use();

		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use();

		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuse();
	}

	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use();

		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuse();
	}

	GLuint getId()
	{
		return this->id;
	}
};
