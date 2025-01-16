#pragma once

#include "../Shapes/Rectangular_Cuboid.hpp"
#include "../include/Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



namespace workspace {

	class CenterHolder {
	public:
		GLuint texture;
		double length, height, depth;
		Rectangular_Cuboid base;
		Rectangular_Cuboid bottomLayer;
		Rectangular_Cuboid layer;
		Rectangular_Cuboid leg;



		CenterHolder() {}
		CenterHolder(double length, double height, double depth, GLuint texture) :
			length(length), height(height), depth(depth), texture(texture)
		{
			base = Rectangular_Cuboid(vec3(0), length, height * 0.975, depth * 0.10, { vec3(0) });
			bottomLayer = Rectangular_Cuboid(vec3(0), length, height * 0.05, depth * 0.5, { vec3(0) });
			layer = Rectangular_Cuboid(vec3(0), length * 0.90, height * 0.025, depth * 0.45, { vec3(0) });
			leg = Rectangular_Cuboid(vec3(0), length * 0.025, height * 0.025, depth * 0.025, { vec3(0) });
		}


		void draw(Shader& shader, mat4 model) {
			shader.setMat4("model", model);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			shader.setInt("tex", 0);

			shader.setMat4("model", translate(model, vec3(0, height * 0.025 / 2, 0)));
			base.draw();

			shader.setMat4("model", translate(model, vec3(0, height * (-0.975 + 0.05 + 0.025) / 2, depth * -0.5 / 2)));
			bottomLayer.draw();
			shader.setMat4("model", translate(model, vec3(0, height * (-0.975 + 0.05 + 0.025) / 2, depth * 0.5 / 2)));
			bottomLayer.draw();

			shader.setMat4("model", translate(model, vec3(length * (1 - 0.025) / 2, height * (-1 + 0.025) / 2, depth * (1 - 0.025) / 2)));
			leg.draw();
			shader.setMat4("model", translate(model, vec3(-length * (1 - 0.025) / 2, height * (-1 + 0.025) / 2, depth * (1 - 0.025) / 2)));
			leg.draw();
			shader.setMat4("model", translate(model, vec3(length * (1 - 0.025) / 2, height * (-1 + 0.025) / 2, -depth * (1 - 0.025) / 2)));
			leg.draw();
			shader.setMat4("model", translate(model, vec3(-length * (1 - 0.025) / 2, height * (-1 + 0.025) / 2, -depth * (1 - 0.025) / 2)));
			leg.draw();

			shader.setMat4("model", translate(model, vec3(0, height * (-0.975 + 0.5 + 0.025 + 0.025) / 2, depth * 0.45 / 2)));
			layer.draw();
			shader.setMat4("model", translate(model, vec3(0, height * (-0.975 + 0.5 + 0.025 + 0.025) / 2, -depth * 0.45 / 2)));
			layer.draw();

			shader.setMat4("model", translate(model, vec3(0, height * (-0.975 + 1 + 0.025 + 0.025) / 2, depth * 0.45 / 2)));
			layer.draw();
			shader.setMat4("model", translate(model, vec3(0, height * (-0.975 + 1 + 0.025 + 0.025) / 2, -depth * 0.45 / 2)));
			layer.draw();

			shader.setMat4("model", translate(model, vec3(0, height * (-0.975 + 1.5 + 0.025 + 0.025) / 2, depth * 0.45 / 2)));
			layer.draw();
			shader.setMat4("model", translate(model, vec3(0, height * (-0.975 + 1.5 + 0.025 + 0.025) / 2, -depth * 0.45 / 2)));
			layer.draw();

		}



	};

}