#pragma once

#include "../Shapes/Rectangular_Cuboid.hpp"
#include "../include/Shader.hpp"


namespace workspace {

	class Blocks {
	public:
		Rectangular_Cuboid shape;
		GLuint texture;

		Blocks() {}
		Blocks(double length, double height, double depth, vector<vec3> offsets, GLuint texture) :
			shape(Rectangular_Cuboid(vec3(0), length, height, depth, offsets)),
			texture(texture) {}


		void draw(Shader& shader, mat4 model) {
			shader.setMat4("model", model);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			shader.setInt("tex", 0);
			shape.draw();
		}

	};

}