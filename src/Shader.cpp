#include "Shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string Shader::get_file_contents(const char* filename) {

	std::ifstream file;
	// ensure ifstream objects can throw exceptions:
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		// open files
		file.open(filename);
		std::stringstream stream;
		// read file's buffer contents into streams
		stream << file.rdbuf();
		// close file handlers
		file.close();
		// convert stream into string
		return stream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;

	}
	return NULL;
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode = get_file_contents(vertexPath);
	std::string fragmentCode = get_file_contents(fragmentPath);
	
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}



// Activates the Shader Program
void Shader::Activate() {
	glUseProgram(ID);
}



int32_t Shader::getUniformLocation(const std::string &location) const {
  return glGetUniformLocation(ID, location.c_str());
}

void Shader::setInt(const std::string &location, int32_t value) const {
  glProgramUniform1i(ID, getUniformLocation(location), value);
}

void Shader::setFloat(const std::string &location, float value) const {
  glProgramUniform1f(ID, getUniformLocation(location), value);
}

void Shader::setVec2(const std::string &location, const glm::vec2 &value) const {
  glProgramUniform2fv(ID, getUniformLocation(location), 1, &value.x);
}

void Shader::setVec3(const std::string &location, const glm::vec3 &value) const {
  glProgramUniform3fv(ID, getUniformLocation(location), 1, &value.x);
}

void Shader::setMat4(const std::string &location, const glm::mat4 &value) const {
  glProgramUniformMatrix4fv(ID, getUniformLocation(location), 1, GL_FALSE, &value[0][0]);
}

// Deletes the Shader Program
void Shader::Delete() {
	glDeleteProgram(ID);
	std::cerr << "shader program is deleted :)" << std::endl;
}

Shader::~Shader() {
	this->Delete();
}
