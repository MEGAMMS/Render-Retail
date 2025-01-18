#pragma once

#include "../Shapes/Rectangular_Cuboid.hpp"
#include "../include/Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace workspace;


namespace workspace {

	class Desk {
	public:
		Rectangular_Cuboid front;
		Rectangular_Cuboid side;
		Rectangular_Cuboid base;
		Rectangular_Cuboid layer;
		double length, height, depth;
		GLuint texture;


		Desk() {}
		Desk(double length, double height, double depth, GLuint texture) :
			length(length), height(height) , depth(depth),
			texture(texture) {
			front = Rectangular_Cuboid(vec3(0), length*0.8, height, depth * 0.1, {vec3(0)});
			side = Rectangular_Cuboid(vec3(0), length * 0.1, height, depth * 0.9, { vec3(0) });
			base = Rectangular_Cuboid(vec3(0), length * 0.8, height*0.2, depth * 0.9, { vec3(0) });
			layer = Rectangular_Cuboid(vec3(0), length * 0.8, height * 0.05, depth * 0.9, { vec3(0) });
		}


		void draw(Shader& shader, mat4 model) {
			glActiveTexture(GL_TEXTURE0);
			shader.setInt("tex", 0);

			glBindTexture(GL_TEXTURE_2D, texture);

			shader.setMat4("model", translate(model,vec3(0,0,-depth/2+ depth * 0.049)));
			front.draw();

			shader.setMat4("model", translate(model, vec3(length/2-length*0.05, 0, -depth*0.049)));
			side.draw();

			shader.setMat4("model", translate(model, vec3(-length/2 + length * 0.05, 0, -depth * 0.049)));
			side.draw();

			shader.setMat4("model", translate(model, vec3(0, -height/2+height*0.1+ 0.01, -depth * 0.04)));
			base.draw();

			shader.setMat4("model", translate(model, vec3(0, height/4, -depth * 0.04)));
			layer.draw();

		}

	};

}