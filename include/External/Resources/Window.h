#pragma once
#include "../Shapes/Rectangular_Cuboid.hpp"
#include "../include/Shader.hpp"



namespace workspace {

	class Window {
	public:
		Rectangular_Cuboid shape;
		Rectangular_Cuboid frame[4];
		GLuint windowTexture;
		GLuint frameTexture;


		Window() {}
		Window(double length, double height, double depth, double frameWidth, double frameHeight, GLuint windowTexture, GLuint frameTexture) :
			windowTexture(windowTexture), frameTexture(frameTexture)
		{
			double windowWidth = length - 2 * frameWidth;
			double windowHeight = height - 2 * frameHeight;

			shape = Rectangular_Cuboid(vec3(0), windowWidth, windowHeight, depth, { vec3(0) });

			// Top
			frame[0] = Rectangular_Cuboid(
				vec3(0, height / 2 - frameHeight / 2, 0),
				length,
				frameHeight,
				depth,
				{ vec3{0} }
			);

			// Bottom
			frame[1] = Rectangular_Cuboid(
				vec3(0, -(height / 2 - frameHeight / 2), 0),
				length,
				frameHeight,
				depth,
				{ vec3{0} }
			);

			// Left
			frame[2] = Rectangular_Cuboid(
				vec3(-(length / 2 - frameWidth / 2), 0, 0),
				frameWidth,
				height - 2 * frameHeight,
				depth,
				{ vec3{0} }
			);

			// Right
			frame[3] = Rectangular_Cuboid(
				vec3(length / 2 - frameWidth / 2, 0, 0),
				frameWidth,
				height - 2 * frameHeight,
				depth,
				{ vec3{0} }
			);

		}


		void draw(Shader& shader, mat4 model) {
			shader.setMat4("model", model);
			glActiveTexture(GL_TEXTURE0);
			shader.setInt("tex", 0);
			glBindTexture(GL_TEXTURE_2D, windowTexture);
			shape.draw();
			glBindTexture(GL_TEXTURE_2D, frameTexture);
			for (int i = 0; i < 4; i++)
				frame[i].draw();

		}


	};

}