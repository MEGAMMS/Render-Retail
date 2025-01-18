#pragma once

#pragma once

#include "../Shapes/Rectangular_Cuboid.hpp"
#include "../include/Shader.hpp"
#include "Window.h"

using namespace workspace;


namespace workspace {

	class Fridge {
	public:
		Rectangular_Cuboid shape;
		Rectangular_Cuboid bottom;
		Rectangular_Cuboid top;
		Rectangular_Cuboid layer;
		Window window;
		double length, height, depth;
		GLuint body_texture;
		GLuint bottom_texture;
		GLuint top_texture;
		GLuint frame_texture;


		Fridge() {}
		Fridge(double length, double height, double depth, GLuint body_texture, GLuint bottom_texture, GLuint top_texture, GLuint window_texture, GLuint frame_texture) :
		length(length) , height(height) , depth(depth) , body_texture(body_texture) , bottom_texture(bottom_texture) , top_texture(top_texture) , frame_texture(frame_texture)
		{
			shape = Rectangular_Cuboid(vec3(0), length, height, depth, { vec3(0) });
			top = Rectangular_Cuboid(vec3(0), length * 0.99, height/6, depth*0.05, { vec3(0) });
			bottom = Rectangular_Cuboid(vec3(0), length * 0.99, height / 6, depth * 0.05, { vec3(0) });
			layer = Rectangular_Cuboid(vec3(0), length*0.985, height * 0.01, depth * 0.985, { vec3(0) });
			window = Window(length/2*0.99,height*2/3,depth*0.05,length*0.02,length*0.02,window_texture,frame_texture);
		}


		void draw(Shader& shader, mat4 model) {
			glActiveTexture(GL_TEXTURE0);
			shader.setInt("tex", 0);
			
			glBindTexture(GL_TEXTURE_2D, body_texture);
			shader.setMat4("model", model);
			for (int i = 1; i < 6; i++)
				shape.drawFace(i);

			glBindTexture(GL_TEXTURE_2D, bottom_texture);
			shader.setMat4("model", translate(model,vec3(0,-height/2 + height/12,depth/2)));
			bottom.draw();

			glBindTexture(GL_TEXTURE_2D, top_texture);
			shader.setMat4("model", translate(model, vec3(0, height / 2 - height / 12, depth / 2)));
			top.draw();

			

			glBindTexture(GL_TEXTURE_2D, body_texture);
			shader.setMat4("model", translate(model, vec3(0, -height/6, 0)));
			layer.draw();
			shader.setMat4("model", model);
			layer.draw();
			shader.setMat4("model", translate(model, vec3(0, height / 6, 0)));
			layer.draw();

			window.draw(shader, translate(model, vec3(-length / 4, 0, depth / 2)));
			window.draw(shader, translate(model, vec3(length / 4, 0, depth / 2)));
		}

	};

}