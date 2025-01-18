#pragma once

#include "../include/Shader.hpp"
#include "../Shapes/Sphere.hpp"

namespace workspace {

	class Toy {
	public:
		Sphere shape;
		GLuint texture;

		Toy() {}
		Toy(double radius, double stacks, double sectors, vector<vec3> offsets, GLuint texture) :
			shape(Sphere(radius,stacks, sectors, offsets)),
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