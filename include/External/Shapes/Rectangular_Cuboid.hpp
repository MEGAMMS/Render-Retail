#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>


using namespace std;
using namespace glm;


class Rectangular_Cuboid {
private:
	GLuint VAO , VBO , instance_VBO , instances_num;
	vector<vec3> vertices, normals;
	vector<vec2> texCord;
	vector<GLuint> faces = {
		// Front
		0,1,2,
		3,2,1,

		// Back
		5,4,7,
		6,7,4,

		// Right
		1,5,3,
		7,3,5,

		// Left
		4,0,6,
		2,6,0,

		// Top
		3,7,2,
		6,2,7,

		// Bottom
		1,0,5,
		4,5,0
	};
	vector<GLuint> edges = {
			0,1,
			0,2,
			0,4,
			1,3,
			1,5,
			2,3,
			2,6,
			3,7,
			4,5,
			4,6,
			5,7,
			6,7
	};
	vector<GLfloat> buffer;


public:
	Rectangular_Cuboid() {}
	Rectangular_Cuboid(vec3 origin , float length , float height , float depth , vector<vec3> offsets) {
		instances_num = offsets.size();

		float xoffset = length / 2 , yoffset = height / 2 , zoffset = depth / 2;
		vertices = {
			{origin.x - xoffset , origin.y - yoffset , origin.z + zoffset},	//0
			{origin.x + xoffset , origin.y - yoffset , origin.z + zoffset},	//1
			{origin.x - xoffset , origin.y + yoffset , origin.z + zoffset},	//2
			{origin.x + xoffset , origin.y + yoffset , origin.z + zoffset},	//3
			{origin.x - xoffset , origin.y - yoffset , origin.z - zoffset},	//4
			{origin.x + xoffset , origin.y - yoffset , origin.z - zoffset},	//5
			{origin.x - xoffset , origin.y + yoffset , origin.z - zoffset},	//6
			{origin.x + xoffset , origin.y + yoffset , origin.z - zoffset},	//7
		};

		
		// Generate Normals
		for (int i = 0; i < faces.size(); i += 3) {
			vec3 a = vertices.at(faces.at(i));
			vec3 b = vertices.at(faces.at(i + 1));
			vec3 c = vertices.at(faces.at(i + 2));
			vec3 ab = b - a, ac = c - a;
			vec3 n = cross(ab, ac);
			normals.push_back(n);
		}



		// Generate Texture Cordinantes
		for (int i = 0; i < faces.size() / 6; i++) {
			texCord.push_back(vec2(0.0, 0.0));
			texCord.push_back(vec2(1.0, 0.0));
			texCord.push_back(vec2(0.0, 1.0));
			texCord.push_back(vec2(1.0, 1.0));
			texCord.push_back(vec2(0.0, 1.0));
			texCord.push_back(vec2(1.0, 0.0));
		}



		// Generate Buffer
		vec3 p, n;
		vec2 t;
		for (int i = 0; i < faces.size(); i += 3) {
			n = normals.at(i / 3);
			for (int j = 0; j < 3; j++) {
				p = vertices.at(faces.at(i + j));
				t = texCord.at(i + j);
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
		glGenBuffers(1, &instance_VBO);
		glBindVertexArray(VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(GLfloat), buffer.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		
		glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
		glEnableVertexAttribArray(3);
		glBufferData(GL_ARRAY_BUFFER, offsets.size() * 3 * sizeof(GLfloat), offsets.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glVertexAttribDivisor(3,1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	void draw() {
		glBindVertexArray(VAO);
		glDrawArraysInstanced(GL_TRIANGLES,0,36,instances_num);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}


	void drawFace(int i) {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,i*6,i*6+5);
		glBindVertexArray(0);
	}


	void remove() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

};