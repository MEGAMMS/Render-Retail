#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>


using namespace glm;
using namespace std;


class Light {
public:
	vec3 ambient;
	vec3 diffuse;
	vec3 speculer;

	Light(){};

	Light(vec3 ambient, vec3 diffuse, vec3 speculer) :
		ambient(ambient) ,
		diffuse(diffuse) ,
		speculer(speculer) {}


	void updateUniforms(int shaderId , string prefix) {
		string a = prefix + ".ambient", d = prefix + ".diffuse", s = prefix + ".speculer";
		glUniform3fv(glGetUniformLocation(shaderId, a.c_str()), 1, &this->ambient[0]);
		glUniform3fv(glGetUniformLocation(shaderId, d.c_str()), 1, &this->diffuse[0]);
		glUniform3fv(glGetUniformLocation(shaderId, s.c_str()), 1, &this->speculer[0]);
	}

};



class DirectionalLight : public Light {
public:
	vec3 direction;

	DirectionalLight(){}
	DirectionalLight(vec3 direction, vec3 ambient, vec3 diffuse, vec3 speculer) :
		direction(direction) ,
		Light(ambient,diffuse,speculer) {}


	void updateUniforms(string prefix) {
		string d = prefix + ".direction";
		GLint shaderId;
		glGetIntegerv(GL_CURRENT_PROGRAM, &shaderId);
		glUniform3fv(glGetUniformLocation(shaderId, d.c_str()), 1, &this->direction[0]);
		Light::updateUniforms(shaderId,prefix);
	}

};



class PointLight : public Light {
public:
	float constant;
	float linear;
	float quadratic;
	vec3 position;
	

	PointLight(){}
	PointLight(float constant , float linear , float quadratic , vec3 position, vec3 ambient, vec3 diffuse, vec3 speculer) :
	constant(constant) ,
	linear(linear) ,
	quadratic(quadratic) ,
	position(position),
	Light(ambient, diffuse, speculer) {}


	void updateUniforms(string prefix) {
		string c = prefix + ".constant", l = prefix + ".linear", q = prefix + ".quadratic", p = prefix + ".position";
		GLint shaderId;
		glGetIntegerv(GL_CURRENT_PROGRAM, &shaderId);
		glUniform1f(glGetUniformLocation(shaderId, c.c_str()), this->constant);
		glUniform1f(glGetUniformLocation(shaderId, l.c_str()), this->linear);
		glUniform1f(glGetUniformLocation(shaderId, q.c_str()) ,this->quadratic);
		glUniform3fv(glGetUniformLocation(shaderId, p.c_str()), 1, value_ptr(this->position));
		Light::updateUniforms(shaderId,prefix);
	}

};



class SpotLight : public Light {
public:
	float innerCutOff;
	float outerCutOff;
	vec3 position;
	vec3 direction;


	SpotLight(){}
	SpotLight(float innerCutOff , float outerCutOff, vec3 position , vec3 direction , vec3 ambient, vec3 diffuse, vec3 speculer) :
		innerCutOff(innerCutOff),		// cosine of cutOff angle
		outerCutOff(outerCutOff),
		position(position),
		direction(direction),
		Light(ambient, diffuse, speculer) {}


	void updateUniforms(string prefix) {
		string i = prefix + ".innerCutOff", o = prefix + ".outerCutOff", p = prefix + ".position", d = prefix + ".direction";
		GLint shaderId;
		glGetIntegerv(GL_CURRENT_PROGRAM, &shaderId);
		glUniform1f(glGetUniformLocation(shaderId, i.c_str()),this->innerCutOff);
		glUniform1f(glGetUniformLocation(shaderId, o.c_str()), this->outerCutOff);
		glUniform3fv(glGetUniformLocation(shaderId, p.c_str()), 1, value_ptr(this->position));
		glUniform3fv(glGetUniformLocation(shaderId, d.c_str()), 1, value_ptr(this->direction));
		Light::updateUniforms(shaderId,prefix);
	}

};