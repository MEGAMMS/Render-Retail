#pragma once

#include "../include/Shader.hpp"
#include "../Shapes/Cylinder.hpp"

using namespace workspace;


namespace workspace {

	class Can {
	public:
		Cylinder shape;
		GLuint body_texture;
		GLuint base_texture;

		Can() {}
		Can(double radius, double height, int points_num, vector<vec3> offsets, GLuint body_texture, GLuint base_texture) :
			shape(Cylinder(vec3(0), radius, height, points_num, offsets)),
			body_texture(body_texture),
			base_texture(base_texture) {}


		void draw(Shader& shader, mat4 model) {
			glActiveTexture(GL_TEXTURE0);
			shader.setInt("tex", 0);

			shader.setMat4("model", model);
			
			glBindTexture(GL_TEXTURE_2D, base_texture);
			shape.drawBase();

			glBindTexture(GL_TEXTURE_2D, body_texture);
			shape.drawBody();
		}

	};

}