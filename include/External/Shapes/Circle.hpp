#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

using namespace glm;
using namespace std;


extern const float PI;


class Circle {
private:
	GLuint VAO, VBO;


public:
	// Vertex Input
	vector<vec3> v, normals;
	vector<vec2> texCord;
	vector<GLuint> indices;
	vector<GLfloat> buffer, normals_buffer;

	Circle() {}
	Circle(vec3 origin,float radius,int points) {
		float theta_offset = 2 * PI / points;

		float x,z,theta;
		float s, t;

		for (float i = 0; i <= points ; i++) {		// Add extra point for indices 0 . 360
			theta = i * theta_offset;					// From Right to Left
			x = radius * cos(theta);
			z = radius * sin(theta);
			v.push_back(vec3(x+origin.x,origin.y,z+origin.z));
			indices.push_back(i);
			indices.push_back(i+1);
			indices.push_back(points);
			texCord.push_back(vec2(cos(theta),sin(theta)));
		}
		v.push_back(vec3(origin.x, origin.y, origin.z));
		texCord.push_back(vec2(0.5,0.5));


		// Generate Normals
		for (int i = 0; i < indices.size(); i += 3) {
			vec3 a = v.at(indices.at(i));
			vec3 b = v.at(indices.at(i + 1));
			vec3 c = v.at(indices.at(i + 2));
			vec3 ab = b - a, ac = c - a;
			vec3 n = cross(ab, ac);
			normals.push_back(n);
		}


		// Buffer
		int n = 0, index;
		for (int i = 0; i < indices.size(); i += 3) {
			vec3 nor = normals.at(n);
			for (int j = 0; j < 3; j++) {
				index = indices.at(i + j);
				vec3 p = v.at(index);
				vec2 tex = texCord.at(index);
				buffer.push_back(p.x);
				buffer.push_back(p.y);
				buffer.push_back(p.z);
				buffer.push_back(nor.x);
				buffer.push_back(nor.y);
				buffer.push_back(nor.z);
				buffer.push_back(tex.x);
				buffer.push_back(tex.y);
			}
			n++;
		}



		// Normals Buffer
		for (int i = 0; i < buffer.size(); i += 8 * sizeof(GLfloat)) {
			vec3 a = vec3(buffer.at(i), buffer.at(i + 1), buffer.at(i + 2));
			vec3 b = vec3(buffer.at(i + 3), buffer.at(i + 4), buffer.at(i + 5));
			vec3 ab = a + b;
			normals_buffer.push_back(a.x);
			normals_buffer.push_back(a.y);
			normals_buffer.push_back(a.z);
			normals_buffer.push_back(ab.x);
			normals_buffer.push_back(ab.y);
			normals_buffer.push_back(ab.z);
		}





		// Buffers


		// Circle VAO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(GLfloat), buffer.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	void draw() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, buffer.size());
		glBindVertexArray(0);
	}



	void remove() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

};