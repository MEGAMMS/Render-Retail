#pragma once
#include "Shader.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Globals.hpp"
#include "Textures.hpp"
#include "../Shapes/Rectangular.hpp"
#include "../Shapes/Sphere.hpp"
#include "../Shapes/Rectangular_Cuboid.hpp"
#include "../Shapes/Circle.hpp"
#include "../Shapes/Cylinder.hpp"
#include "../Shapes/Ellipse.hpp"
#include "../Resources/Blocks.h"
#include "../Resources/Surface.h"
#include "../Resources/Window.h"
#include "../Resources/CenterHolder.h"


using namespace std;
using namespace glm;


extern Camera camera;

namespace workspace {

	class Scene {
		inline static Blocks wall[5];
		inline static Surface floor;
		inline static Surface ceil;
		inline static Blocks base[3];
		inline static Blocks signBoard[2];
		inline static Surface logo;
		inline static Blocks shutter;
		inline static Blocks cover[2];
		inline static Window window[9];
		inline static Surface ad[6];
		inline static CenterHolder centerHolder;


	public:
		static void prepare() {

			/* Walls */
			vector<vec3> offsets;

			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					offsets.push_back(vec3(i * 4, j * 2, 0));
			wall[0] = Blocks(4, 2, 2, offsets, Textures::id_map.at("outer_wall"));

			offsets = {};
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					offsets.push_back(vec3(i * 4, j * 2, 0));
			wall[1] = Blocks(4, 2, 2, offsets, Textures::id_map.at("outer_wall"));

			offsets = {};
			for (int i = 0; i < 1; i++)
				for (int j = 0; j < 5; j++)
					offsets.push_back(vec3(i * 1, j * 2, 0));
			wall[2] = Blocks(1, 2, 1, offsets, Textures::id_map.at("outer_wall"));

			offsets = {};
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 2; j++)
					offsets.push_back(vec3(i * 1, j * 2, 0));
			wall[3] = Blocks(1, 2, 1, offsets, Textures::id_map.at("outer_wall"));

			offsets = {};
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 1; j++)
					offsets.push_back(vec3(i * 1, j * 2, 0));
			wall[4] = Blocks(1, 1, 1, offsets, Textures::id_map.at("outer_wall"));



			/* Floor & Ceil */
			offsets = {};
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 12; j++)
					offsets.push_back(vec3(-i * 4, -j * 4, 0));
			floor = Surface(4, 4, false, offsets, Textures::id_map.at("floor"));
			ceil = Surface(4, 4, false, offsets, Textures::id_map.at("ceil"));



			/* SignBoard */
			offsets = {};
			for (int i = 0; i < 41; i++)
				for (int j = 0; j < 101; j++)
					offsets.push_back(vec3(-i * 0.5, -j * 0.5, 0));
			base[0] = Blocks(0.5, 0.5, 0.1, offsets, Textures::id_map.at("base"));

			offsets = {};
			for (int i = 0; i < 41; i++)
				for (int j = 0; j < 101; j++)
					offsets.push_back(vec3(-i * 0.5, -j * 0.5, 0));
			base[1] = Blocks(0.5, 0.5, 0.2, offsets, Textures::id_map.at("base"));

			offsets = {};
			for (int i = 0; i < 42; i++)
				for (int j = 0; j < 102; j++)
					offsets.push_back(vec3(-i * 0.5, -j * 0.5, 0));
			base[2] = Blocks(0.5, 0.5, 0.4, offsets, Textures::id_map.at("base"));


			offsets = {};
			for (int i = 0; i < 41; i++)
				offsets.push_back(vec3(i * 0.5, 0, 0));
			signBoard[0] = Blocks(0.5, 2.5, 0.5, offsets, Textures::id_map.at("arma"));

			offsets = {};
			for (int i = 0; i < 99; i++)
				offsets.push_back(vec3(i * 0.5, 0, 0));
			signBoard[1] = Blocks(0.5, 2.5, 0.5, offsets, Textures::id_map.at("arma"));

			logo = Surface(7, 2.5, false, { vec3(0) }, Textures::id_map.at("logo"));


			/* Shutter */
			offsets = {};
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 2; j++)
					offsets.push_back(vec3(-i * 2, -j * 5, 0));
			shutter = Blocks(2, 5, 0.5, offsets, Textures::id_map.at("shutter"));


			/* Store Front */
			window[0] = Window(2.5, 5, 0.1, 0.1, 0.05, Textures::id_map.at("glass"), Textures::id_map.at("frame"));

			cover[0] = Blocks(6, 3.25, 0.5, { vec3(0) }, Textures::id_map.at("frame"));
			window[1] = Window(3, 3.25, 0.1, 0.1, 0.05, Textures::id_map.at("glass"), Textures::id_map.at("frame"));
			window[2] = Window(3, 4.75, 0.1, 0.1, 0.05, Textures::id_map.at("glass"), Textures::id_map.at("frame"));
			window[3] = Window(3, 2, 0.1, 0.1, 0.05, Textures::id_map.at("glass"), Textures::id_map.at("frame"));

			window[4] = Window(4.25, 3.25, 0.1, 0.1, 0.05, Textures::id_map.at("glass"), Textures::id_map.at("frame"));
			window[5] = Window(4.25, 4.75, 0.1, 0.1, 0.05, Textures::id_map.at("glass"), Textures::id_map.at("frame"));
			window[6] = Window(4.25, 2, 0.1, 0.1, 0.05, Textures::id_map.at("glass"), Textures::id_map.at("frame"));

			cover[1] = Blocks(6.5, 2, 0.1, { vec3(0) }, Textures::id_map.at("ad3"));
			window[7] = Window(3.25, 4.5, 0.1, 0.2, 0.2, Textures::id_map.at("glass"), Textures::id_map.at("frame"));
			window[8] = Window(3.25, 3.5, 0.1, 0.2, 0.2, Textures::id_map.at("glass"), Textures::id_map.at("frame"));


			/* Ads */
			ad[0] = Surface(2.5, 1.25, false, { vec3(0) }, Textures::id_map.at("ad1"));
			ad[1] = Surface(2, 2, false, { vec3(0) }, Textures::id_map.at("ad2"));
			ad[2] = Surface(3, 3, false, { vec3(0) }, Textures::id_map.at("ad4"));
			ad[3] = Surface(3, 3, false, { vec3(0) }, Textures::id_map.at("ad5"));
			ad[4] = Surface(6, 4, false, { vec3(0) }, Textures::id_map.at("ad6"));




			/* Inside Store */
			centerHolder = CenterHolder(4, 5, 3.5, Textures::id_map.at("base"));



		}




		static void draw(mat4 model , mat4 view , mat4 perspect,vec3 cameraPos) {
			Shaders::material.use();
			Shaders::material.setMat4("view",view);
			Shaders::material.setMat4("perspect",perspect);


			/* Walls */
			wall[0].draw(Shaders::material, mat4(1));
			wall[0].draw(Shaders::material, translate(mat4(1), vec3(-1, 0, -3)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			wall[0].draw(Shaders::material, translate(mat4(1), vec3(-1, 0, -19)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			wall[0].draw(Shaders::material, translate(mat4(1), vec3(0, 0, -38)));
			wall[0].draw(Shaders::material, translate(mat4(1), vec3(0, 0, -48)));

			wall[1].draw(Shaders::material, translate(mat4(1), vec3(-1, 0, -41)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			wall[2].draw(Shaders::material, translate(mat4(1), vec3(17.5, 0, -6.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			wall[2].draw(Shaders::material, translate(mat4(1), vec3(17.5, 0, -14)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			wall[2].draw(Shaders::material, translate(mat4(1), vec3(17.5, 0, -21)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			wall[2].draw(Shaders::material, translate(mat4(1), vec3(17.5, 0, -28)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			wall[3].draw(Shaders::material, translate(mat4(1), vec3(17.5, 0, -1.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			wall[4].draw(Shaders::material, translate(mat4(1), vec3(17.5, 8.5, -1.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));


			/* Floor & Ceil */
			floor.draw(Shaders::material, translate(mat4(1), vec3(16, -1, -1)) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)));
			ceil.draw(Shaders::material, translate(mat4(1), vec3(16, 9, -3)) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)));



			/* SignBoard */
			base[0].draw(Shaders::material, translate(mat4(1), vec3(18, 9.1, 1)) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)));
			base[1].draw(Shaders::material, translate(mat4(1), vec3(18, 11.75, 1)) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)));
			base[2].draw(Shaders::material, translate(mat4(1), vec3(18.25, 12.0, 1.25)) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)));

			signBoard[0].draw(Shaders::material, translate(mat4(1), vec3(-2, 10.4, 1)));
			signBoard[0].draw(Shaders::material, translate(mat4(1), vec3(-2, 10.4, -49)));
			signBoard[1].draw(Shaders::material, translate(mat4(1), vec3(18, 10.4, 0.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			signBoard[1].draw(Shaders::material, translate(mat4(1), vec3(-2, 10.4, 0.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			logo.draw(Shaders::material, translate(mat4(1), vec3(18.28, 10.4, -23)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));



			/* Shutter */
			shutter.draw(Shaders::material, translate(mat4(1), vec3(17.75, 6.5, -46)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));



			/* Inside Ads */
			ad[2].draw(Shaders::material, translate(mat4(1), vec3(0.1, 7, -26)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			ad[3].draw(Shaders::material, translate(mat4(1), vec3(0.1, 7, -20)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			ad[4].draw(Shaders::material, translate(mat4(1), vec3(8, 6, -1.1)) * rotate(mat4(1), radians(180.0f), vec3(0, 1, 0)));



			/* Store Front */
			window[0].draw(Shaders::material, translate(mat4(1), vec3(18, 5.5, -2.25)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[0].draw(Shaders::material, translate(mat4(1), vec3(18, 5.5, -4.75)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			cover[1].draw(Shaders::material, translate(mat4(1), vec3(18, 8, -10.25)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[7].draw(Shaders::material, translate(mat4(1), vec3(18, 1.25, -8.6)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[7].draw(Shaders::material, translate(mat4(1), vec3(18, 1.25, -11.85)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[8].draw(Shaders::material, translate(mat4(1), vec3(18, 5.25, -8.6)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[8].draw(Shaders::material, translate(mat4(1), vec3(18, 5.25, -11.85)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			cover[0].draw(Shaders::material, translate(mat4(1), vec3(17.75, 0.625, -17.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[1].draw(Shaders::material, translate(mat4(1), vec3(18, 0.625, -16)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[1].draw(Shaders::material, translate(mat4(1), vec3(18, 0.625, -19)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[2].draw(Shaders::material, translate(mat4(1), vec3(18, 4.625, -16)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[2].draw(Shaders::material, translate(mat4(1), vec3(18, 4.625, -19)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[3].draw(Shaders::material, translate(mat4(1), vec3(18, 8, -16)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[3].draw(Shaders::material, translate(mat4(1), vec3(18, 8, -19)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			cover[0].draw(Shaders::material, translate(mat4(1), vec3(17.75, 0.625, -24.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[1].draw(Shaders::material, translate(mat4(1), vec3(18, 0.625, -23)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[1].draw(Shaders::material, translate(mat4(1), vec3(18, 0.625, -26)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[2].draw(Shaders::material, translate(mat4(1), vec3(18, 4.625, -23)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[2].draw(Shaders::material, translate(mat4(1), vec3(18, 4.625, -26)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[3].draw(Shaders::material, translate(mat4(1), vec3(18, 8, -23)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[3].draw(Shaders::material, translate(mat4(1), vec3(18, 8, -26)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			ad[0].draw(Shaders::material, translate(mat4(1), vec3(18.1, 6, -23)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));


			window[4].draw(Shaders::material, translate(mat4(1), vec3(18, 0.625, -30.625)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[4].draw(Shaders::material, translate(mat4(1), vec3(18, 0.625, -34.825)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[5].draw(Shaders::material, translate(mat4(1), vec3(18, 4.625, -30.625)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[5].draw(Shaders::material, translate(mat4(1), vec3(18, 4.625, -34.825)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[6].draw(Shaders::material, translate(mat4(1), vec3(18, 8, -30.625)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[6].draw(Shaders::material, translate(mat4(1), vec3(18, 8, -34.825)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			ad[1].draw(Shaders::material, translate(mat4(1), vec3(18.1, 5, -30.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));



			/* Inside Store */


			// Holders
			centerHolder.draw(Shaders::material, translate(mat4(1), vec3(25, 3, 20)));



		}

	};

}