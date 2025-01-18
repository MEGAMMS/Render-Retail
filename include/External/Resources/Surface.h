#pragma once

#include "../include/Shader.hpp"
#include "../Shapes/Rectangular.hpp"


namespace workspace {

	class Surface {
	public:
		Rectangular shape;
		GLuint texture;

		Surface() {}
		Surface(float length, float height, bool inverseNormal, vector<vec3> offsets, GLuint texture) :
			shape(Rectangular(vec3(0), length, height, offsets, inverseNormal)),
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