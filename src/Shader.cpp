/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 15:33:25 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/04 15:04:06 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

Shader::Shader() {
	programId = glCreateProgram();
}

void	Shader::link(std::string path, GLenum type) {
	std::string	code;
	GLuint		id;
	GLint		status;

	code = readFile(path);
	id = compile(code, type);

	glAttachShader(programId, id);
	glLinkProgram(programId);
	
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
		throw std::runtime_error("Shader program link failed: " + path);
	else 
		std::cout << "Shader program successfully linked: " << path << std::endl; 
	glDeleteShader(id);
}

std::string	Shader::readFile(std::string path) {
	std::stringstream	stream;
	std::ifstream		file(path.c_str());

	if (!file.good())
		throw std::runtime_error("Failed to open file :" + path);
	stream << file.rdbuf();
	file.close();
	return stream.str();
}

GLuint		Shader::compile(std::string source, GLenum type) {
	GLuint			shaderID;
	const GLchar	*charSource;
	GLint			status = GL_TRUE;

	shaderID = glCreateShader(type);
	if (shaderID == 0)
		throw std::runtime_error("Could not create shader");
	charSource = source.c_str();

	glShaderSource(shaderID, 1, &charSource, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
		throw std::runtime_error("Shader compilation failed");
	return shaderID;
}

void		Shader::addUniform(std::string name) {
	_uniform[name] = glGetUniformLocation(programId, name.c_str());
	if (_uniform[name] == -1)
		throw std::runtime_error("Could not create uniform " + name);
}

GLint		Shader::uniform(std::string name) {
	static std::map<std::string, int>::const_iterator uniformIter;

	uniformIter = _uniform.find(name);
	if (uniformIter == _uniform.end())
		throw std::runtime_error("Could not find uniform in shader program: " + name);
	return _uniform[name];
}

void		Shader::setUniformMatrix (glm::mat4 mat, std::string name) {
	glUniformMatrix4fv(uniform(name), 1, GL_FALSE, glm::value_ptr(mat));
}

Shader::~Shader() {
}

