#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Circle.hpp"


using namespace std;
using namespace glm;


extern const float PI;


class CylinderBorder {

private:
	GLuint VAO, VBO;
	vector<vec3> vertices, normals;
	vector<vec2> texCord;
	vector<GLuint> faces;
	vector<GLfloat> buffer;


public:
	CylinderBorder() {}
	CylinderBorder(vec3 origin, float radius, float height, int points) {

		float theta_offset = 2 * PI / points;
		float tex_offset = 1 / points;
		float x, z, theta; 

		// Generate Vertices
		for (int i = 0; i <= points; i++) {
			theta = i * theta_offset;
			x = radius * cos(theta);
			z = radius * sin(theta);
			vertices.push_back(vec3(x + origin.x, origin.y - height / 2, z + origin.z));
			texCord.push_back(vec2(tex_offset * i, 0));
		}

		for (int i = 0; i <= points; i++) {
			theta = i * theta_offset;
			x = radius * cos(theta);
			z = radius * sin(theta);
			vertices.push_back(vec3(x + origin.x, origin.y + height / 2, z + origin.z));
			texCord.push_back(vec2(tex_offset * i, 1));
		}


		// Generate Indices
		for (int i = 0; i <= points; i++) {
			faces.push_back(i);
			faces.push_back(i + 1);
			faces.push_back(i + points);

			faces.push_back(i + 1);
			faces.push_back(i + 1 + points);
			faces.push_back(i + points);
		}


		// Generate Normals
		for (int i = 0; i < faces.size(); i+=3) {
			vec3 a = vertices.at(faces.at(i));
			vec3 b = vertices.at(faces.at(i + 1));
			vec3 c = vertices.at(faces.at(i + 2));
			vec3 ab = b - a, ac = c - a;
			vec3 n = cross(ab, ac);
			normals.push_back(n);
		}


		// Generate Buffer
		vec3 p, n;
		vec2 t;
		for (int i = 0; i < faces.size(); i += 3) {
			n = normals.at(i / 3);
			for (int j = 0; j < 3; j++) {
				p = vertices.at(faces.at(i + j));
				t = texCord.at(faces.at(i + j));
				buffer.push_back(p.x);
				buffer.push_back(p.y);
				buffer.push_back(p.z);
				buffer.push_back(n.x);
				buffer.push_back(n.y);
				buffer.push_back(n.z);
				buffer.push_back(t.x);
				buffer.push_back(t.y);
			}
		}


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
	}

};



class Cylinder {
private:
	Circle c1, c2;
	CylinderBorder cb;


public:
	Cylinder(){}
	Cylinder(vec3 origin, float radius, float height,int c_points = 36){
		c1 = Circle(vec3(origin.x,origin.y - height / 2,origin.z),radius,c_points);
		c2 = Circle(vec3(origin.x, origin.y + height / 2, origin.z), radius, c_points);
		cb = CylinderBorder(origin,radius,height,c_points);
	}


	void draw() {
		c1.draw();
		cb.draw();
		c2.draw();
	}

};