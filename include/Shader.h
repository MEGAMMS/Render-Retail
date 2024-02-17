#pragma once

#include "core.h"

class Shader {
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void Activate();

	int32_t getUniformLocation(const std::string& location) const;
	void setInt(const std::string& location, int32_t value) const;
	void setFloat(const std::string& location, float value) const;
	void setVec2(const std::string& location, const glm::vec2& value) const;
	void setVec3(const std::string& location, const glm::vec3& value) const;
	void setMat4(const std::string& location, const glm::mat4& value) const;

private:
	
	void Delete();
	void checkCompileErrors(unsigned int shader, std::string type);
	std::string get_file_contents(const char* filename);
};
