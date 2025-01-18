#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

using namespace glm;
using namespace std;


const float PI = radians(180.0f);

namespace workspace {

class Sphere {
private:
	GLuint VAO1, VBO1 , VAO2, VBO2, instance_VBO, instances_num;

	// Vertex Input
	vector<vec3> v, normals;
	vector<vec2> texCord;
	vector<GLuint> indices;
	vector<GLfloat> buffer, normals_buffer;




public:
	Sphere(){}
	Sphere(float r, int stacks, int sectors, vector<vec3> offsets = {vec3(0)}) {
		instances_num = offsets.size();

		int stack_lines = stacks;
		int sector_lines = sectors;

		float theta_offset = 2 * PI / stack_lines;
		float phi_offset = PI / sector_lines;


		float xy, x , y , z, phi, theta;
		int offset = stack_lines + 1, p;	// offset is between every sector line
		float s, t;

		for (int i = 0; i <= sector_lines; i++) {

			// Cordinantes
			phi = PI / 2 - i * phi_offset;					// From z=2 to z=-2
			xy = r * cos(phi);
			z = r * sin(phi);
			t = (float)i / sector_lines;

			for (float j = 0; j <= stack_lines; j++) {		// Add extra point for indices 0 . 360
				theta = j * theta_offset;					// From Right to Left
				x = xy * cos(theta);
				y = xy * sin(theta);
				v.push_back(vec3(x,y,z));
				s = (float)j / stack_lines;
				texCord.push_back(vec2(s,t));
			}


			// Indices

			// Up Triangle
			p = i * offset;
			if (i != 0)
				for (int j = 0; j < stack_lines; j++) {
					indices.push_back(p);
					indices.push_back(p + 1);
					indices.push_back(p - offset + 1);
					p++;
				}

			// Down Triangle
			p = i * (stack_lines + 1);
			if (i != sector_lines)
				for (int j = 0; j < stack_lines; j++) {
					indices.push_back(p);
					indices.push_back(p + offset);
					indices.push_back(p + 1);
					p++;
				}
		}


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
		int n=0 , index;
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
		for (int i = 0; i < buffer.size(); i += 8*sizeof(GLfloat)) {
			vec3 a = vec3(buffer.at(i), buffer.at(i+1), buffer.at(i+2));
			vec3 b = vec3(buffer.at(i+3), buffer.at(i + 4), buffer.at(i + 5));
			vec3 ab = a + b;
			normals_buffer.push_back(a.x);
			normals_buffer.push_back(a.y);
			normals_buffer.push_back(a.z);
			normals_buffer.push_back(ab.x);
			normals_buffer.push_back(ab.y);
			normals_buffer.push_back(ab.z);
		}





		// Buffers


		// Sphere VAO1
		glGenVertexArrays(1, &VAO1);
		glGenBuffers(1, &VBO1);
		glGenBuffers(1, &instance_VBO);
		glBindVertexArray(VAO1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(GLfloat), buffer.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
		glEnableVertexAttribArray(3);
		glBufferData(GL_ARRAY_BUFFER, offsets.size() * 3 * sizeof(GLfloat), offsets.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glVertexAttribDivisor(3, 1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);



		// Normals VAO2
		glGenVertexArrays(1, &VAO2);
		glGenBuffers(1, &VBO2);
		glBindVertexArray(VAO2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, normals_buffer.size() * sizeof(GLfloat), normals_buffer.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	void draw() {
		glBindVertexArray(VAO1);
		//glDrawArrays(GL_TRIANGLES,0,buffer.size());
		glDrawArraysInstanced(GL_TRIANGLES, 0, buffer.size(),instances_num);
		glBindVertexArray(0);
	}


	void drawNormals() {
		glBindVertexArray(VAO2);
		glDrawArrays(GL_LINES, 0, normals_buffer.size());
		glBindVertexArray(0);
	}


	void remove() {
		glDeleteVertexArrays(1, &VAO1);
		glDeleteBuffers(1, &VBO1);
		glDeleteVertexArrays(1, &VAO2);
		glDeleteBuffers(1, &VBO2);
	}

};


}








/*

class Sphere {
private:
	GLuint VAO, VBO;


	// Vertex Input
	vector<vec3> *v , *buffer;
	vector<GLuint> *indices , *lineIndices;
	int v_count, i_count;
	int stack_lines, sector_lines;
	float r;



public:

	Sphere() {
		v = new vector<vec3>;
		indices = new vector<GLuint>;
		lineIndices = new vector<GLuint>;
		buffer = new vector<vec3>;

		stack_lines = 36;
		sector_lines = 36;
		r = 2.0f;



		// Verticies
		float theta_offset = 2 * PI / stack_lines;
		float phi_offset = PI / sector_lines;
		float xy, x , y , z, phi, theta;

		for (int i = 0; i <= sector_lines; i++) {

			phi = PI / 2 - i * phi_offset;					// From z=2 to z=-2
			xy = r * cos(phi);
			z = r * sin(phi);

			for (float j = 0; j <= stack_lines; j++) {		// Add extra point for indices 0 . 360
				theta = j * theta_offset;					// From Right to Left
				x = xy * cos(theta);
				y = xy * sin(theta);
				v.push_back(vec3(x,y,z));
			}

		}


		// Indicies
		int k1, k2;
		for (int i = 0; i < sector_lines; i++) {

			k1 = i * (stack_lines + 1);     // beginning of current sector
			k2 = k1 + stack_lines + 1;      // beginning of next sector


			for (int j = 0; j < stack_lines; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding first and last stacks
				// k1 => k2 => k1+1
				if (i != 0)
				{
					indices.push_back(k1);
					indices.push_back(k2);
					indices.push_back(k1 + 1);
				}


				// k1+1 => k2 => k2+1
				if (i != (sector_lines - 1))
				{
					indices.push_back(k1 + 1);
					indices.push_back(k2);
					indices.push_back(k2 + 1);
				}


				// store indices for lines
				// vertical lines for all stacks, k1 => k2
				lineIndices.push_back(k1);
				lineIndices.push_back(k2);
				if (i != 0)  // horizontal lines except 1st stack, k1 => k+1
				{
					lineIndices.push_back(k1);
					lineIndices.push_back(k1 + 1);
				}


			}
		}

*/