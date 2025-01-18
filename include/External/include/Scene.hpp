#pragma once
#include "Shader.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Globals.hpp"
#include "Textures.hpp"
#include "../Model/Model.h"
#include "../Resources/Blocks.h"
#include "../Resources/Surface.h"
#include "../Resources/Window.h"
#include "../Resources/CenterHolder.h"
#include "../Resources/Holder.h"
#include "../Resources/Fridge.h"
#include "../Resources/Desk.h"
#include "../Resources/Can.h"
#include "../Resources/Toy.h"


using namespace std;
using namespace glm;


namespace workspace {

	class Scene {
		inline static mat4 model;
		inline static mat4 view;
		inline static mat4 perspect;
		inline static vec3 cameraPos;


		/* Resources */
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
		inline static Holder holder;
		inline static Fridge fridge;
		inline static Desk desk;
		inline static Can can[8];
		inline static Toy ball[4];


		/* Lighting */
		inline static Rectangular_Cuboid light;



	public:
		static void prepare() {
			prepareProducts();
			prepareInterior();
			prepareExterior();
		}

		static void prepareProducts() {
			vector<vec3> offsets;

			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 2; j++)
					offsets.push_back(vec3(i * 0.5, 0, -j * 0.5));

			// Holder 1
			can[0] = Can(0.2, 0.5, 36, offsets, Textures::id_map.at("can1"), Textures::id_map.at("can0"));
			can[1] = Can(0.2, 0.5, 36, offsets, Textures::id_map.at("can2"), Textures::id_map.at("can0"));
			can[2] = Can(0.2, 0.5, 36, offsets, Textures::id_map.at("can3"), Textures::id_map.at("can0"));
			can[3] = Can(0.2, 0.5, 36, offsets, Textures::id_map.at("can4"), Textures::id_map.at("can0"));


			// Holder 2
			can[4] = Can(0.2, 0.25, 36, offsets, Textures::id_map.at("can1"), Textures::id_map.at("can0"));
			can[5] = Can(0.2, 0.25, 36, offsets, Textures::id_map.at("can2"), Textures::id_map.at("can0"));
			can[6] = Can(0.2, 0.25, 36, offsets, Textures::id_map.at("can3"), Textures::id_map.at("can0"));
			can[7] = Can(0.2, 0.25, 36, offsets, Textures::id_map.at("can4"), Textures::id_map.at("can0"));



			offsets = {};
			for (int i = 0; i < 5; i++)
				offsets.push_back(vec3(0, 0, -i));

			// Holder 3
			ball[0] = Toy(0.4, 36, 36, offsets, Textures::id_map.at("ball0"));
			ball[1] = Toy(0.4, 36, 36, offsets, Textures::id_map.at("ball1"));
			ball[2] = Toy(0.4, 36, 36, offsets, Textures::id_map.at("ball2"));
			ball[3] = Toy(0.4, 36, 36, offsets, Textures::id_map.at("ball3"));

		}

		static void prepareExterior() {
			vector<vec3> offsets;

			/* Walls */
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
			wall[2] = Blocks(1, 2, 1, offsets, Textures::id_map.at("outer_wall2"));

			offsets = {};
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 2; j++)
					offsets.push_back(vec3(i * 1, j * 2, 0));
			wall[3] = Blocks(1, 2, 1, offsets, Textures::id_map.at("outer_wall3"));

			offsets = {};
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 1; j++)
					offsets.push_back(vec3(i * 1, j * 2, 0));
			wall[4] = Blocks(1, 1, 1, offsets, Textures::id_map.at("outer_wall4"));



			/* Floor & Ceil */
			offsets = {};
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 12; j++)
					offsets.push_back(vec3(-i * 4, -j * 4, 0));
			floor = Surface(4, 4, true, offsets, Textures::id_map.at("floor"));
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

			ad[0] = Surface(2.5, 1.25, false, { vec3(0) }, Textures::id_map.at("ad1"));
			ad[1] = Surface(2, 2, false, { vec3(0) }, Textures::id_map.at("ad2"));
		}

		static void prepareInterior() {
			vector<vec3> offsets;

			/* Ads */
			ad[2] = Surface(3, 3, false, { vec3(0) }, Textures::id_map.at("ad4"));
			ad[3] = Surface(3, 3, false, { vec3(0) }, Textures::id_map.at("ad5"));
			ad[4] = Surface(6, 4, false, { vec3(0) }, Textures::id_map.at("ad6"));


			/* Inside Store */
			centerHolder = CenterHolder(4, 5, 3.5, Textures::id_map.at("holder"));
			holder = Holder(6, 6, 2, Textures::id_map.at("holder"));
			fridge = Fridge(4,6.5,3,
			Textures::id_map.at("fridgeBody"),
			Textures::id_map.at("fridgeBottom"),
			Textures::id_map.at("fridgeTop"),
			Textures::id_map.at("glass"),
			Textures::id_map.at("fridgeFrame")
			);
			desk = Desk(3,4,2.5, Textures::id_map.at("desk"));

		}



		static void draw(mat4 model , mat4 view , mat4 perspect , vec3 cameraPos)
		{
			Scene::model = model * translate(mat4(1),vec3(28,4.25,16)) * scale(mat4(1),vec3(0.25)) * rotate(mat4(1),radians(90.0f),vec3(0,1,0));
			Scene::view = view;
			Scene::perspect = perspect;
			Scene::cameraPos = cameraPos;
			//drawLights();
			Shaders::material.use();
			Shaders::material.setMat4("view",view);
			Shaders::material.setMat4("perspect",perspect);
			Shaders::material.setVec3("cameraPos", cameraPos);
			drawInterior();
			drawExterior();
			drawTransperent();
		}


		static void drawLights() {
			Shaders::standard.use();
			Shaders::standard.setMat4("view",view);
			Shaders::standard.setMat4("perspect",perspect);
			Shaders::standard.setVec3("color", vec3(1));
			Shaders::standard.setMat4("model", translate(mat4(1), vec3(35, 8, -20)));
			light.draw();
		}


		static void drawProducts() {

			// Holder 1 Cans
			can[0].draw(Shaders::material, model * translate(mat4(1), vec3(10, -0.35, -12.8)));
			can[1].draw(Shaders::material, model * translate(mat4(1), vec3(10, 0.80, -12.8)));
			can[2].draw(Shaders::material, model * translate(mat4(1), vec3(10, 2.02, -12.8)));
			can[3].draw(Shaders::material, model * translate(mat4(1), vec3(10, 3.2, -12.8)));

			can[0].draw(Shaders::material, model * translate(mat4(1), vec3(10, -0.35, -14.6)));
			can[1].draw(Shaders::material, model * translate(mat4(1), vec3(10, 0.80, -14.6)));
			can[2].draw(Shaders::material, model * translate(mat4(1), vec3(10, 2.02, -14.6)));
			can[3].draw(Shaders::material, model * translate(mat4(1), vec3(10, 3.2, -14.6)));


			// Holder 2 Small Cans
			can[4].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, -0.5, -12.8)));
			can[5].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 0.65, -12.8)));
			can[6].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 1.87, -12.8)));
			can[7].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 3.1, -12.8)));

			can[4].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, -0.35, -14.6)));
			can[5].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 0.65, -14.6)));
			can[6].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 1.87, -14.6)));
			can[7].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 3.1, -14.6)));


			// Holder 3 Cans
			can[0].draw(Shaders::material, model * translate(mat4(1), vec3(10, -0.35, -21.8)));
			can[1].draw(Shaders::material, model * translate(mat4(1), vec3(10, 0.80, -21.8)));
			can[2].draw(Shaders::material, model * translate(mat4(1), vec3(10, 2.02, -21.8)));
			can[3].draw(Shaders::material, model * translate(mat4(1), vec3(10, 3.2, -21.8)));

			can[0].draw(Shaders::material, model * translate(mat4(1), vec3(10, -0.35, -23.6)));
			can[1].draw(Shaders::material, model * translate(mat4(1), vec3(10, 0.80, -23.6)));
			can[2].draw(Shaders::material, model * translate(mat4(1), vec3(10, 2.02, -23.6)));
			can[3].draw(Shaders::material, model * translate(mat4(1), vec3(10, 3.2, -23.6)));


			// Holder 4 Small Cans
			can[4].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, -0.5, -21.8)));
			can[5].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 0.65, -21.8)));
			can[6].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 1.87, -21.8)));
			can[7].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 3.1, -21.8)));

			can[4].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, -0.35, -23.6)));
			can[5].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 0.65, -23.6)));
			can[6].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 1.87, -23.6)));
			can[7].draw(Shaders::material, model * translate(mat4(1), vec3(4.5, 3.1, -23.6)));



			// Holder 3
			ball[0].draw(Shaders::material, model * translate(mat4(1), vec3(2, -0.1, -29.5)));
			ball[1].draw(Shaders::material, model * translate(mat4(1), vec3(2, 1.2, -29.5)));
			ball[2].draw(Shaders::material, model * translate(mat4(1), vec3(2, 2.7, -29.5)));
			ball[3].draw(Shaders::material, model * translate(mat4(1), vec3(2, 4.2, -29.5)));
		}


		static void drawExterior() {
			vec3 lightPos = vec3(model * vec4(vec3(30, 8, -18),1));
			Shaders::material.setVec3("lightPosition", lightPos);
			Shaders::material.setVec3("lightColor", vec3(1));

			/* Walls */
			wall[0].draw(Shaders::material, model * mat4(1));
			wall[0].draw(Shaders::material, model * translate(mat4(1), vec3(-1, 0, -3)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			wall[0].draw(Shaders::material, model * translate(mat4(1), vec3(-1, 0, -19)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			wall[0].draw(Shaders::material, model * translate(mat4(1), vec3(0, 0, -38)));
			wall[0].draw(Shaders::material, model * translate(mat4(1), vec3(0, 0, -48)));

			wall[1].draw(Shaders::material, model * translate(mat4(1), vec3(-1, 0, -41)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			wall[2].draw(Shaders::material, model * translate(mat4(1), vec3(17.5, 0, -6.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			wall[2].draw(Shaders::material, model * translate(mat4(1), vec3(17.5, 0, -14)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			wall[2].draw(Shaders::material, model * translate(mat4(1), vec3(17.5, 0, -21)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			wall[2].draw(Shaders::material, model * translate(mat4(1), vec3(17.5, 0, -28)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			wall[3].draw(Shaders::material, model * translate(mat4(1), vec3(17.5, 0, -1.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			wall[4].draw(Shaders::material, model * translate(mat4(1), vec3(17.5, 8.5, -1.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));


			/* Floor & Ceil */
			floor.draw(Shaders::material, model * translate(mat4(1), vec3(16, -1, -1)) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)));
			ceil.draw(Shaders::material, model * translate(mat4(1), vec3(16, 9, -3)) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)));



			/* SignBoard */
			base[0].draw(Shaders::material, model * translate(mat4(1), vec3(18, 9.1, 1)) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)));
			base[1].draw(Shaders::material, model * translate(mat4(1), vec3(18, 11.75, 1)) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)));
			base[2].draw(Shaders::material, model * translate(mat4(1), vec3(18.25, 12.0, 1.25)) * rotate(mat4(1), radians(90.0f), vec3(1, 0, 0)));

			signBoard[0].draw(Shaders::material, model * translate(mat4(1), vec3(-2, 10.4, 1)));
			signBoard[0].draw(Shaders::material, model * translate(mat4(1), vec3(-2, 10.4, -49)));
			signBoard[1].draw(Shaders::material, model * translate(mat4(1), vec3(18, 10.4, 0.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			signBoard[1].draw(Shaders::material, model * translate(mat4(1), vec3(-2, 10.4, 0.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			logo.draw(Shaders::material, model * translate(mat4(1), vec3(18.28, 10.4, -23)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));



			/* Shutter */
			shutter.draw(Shaders::material, model * translate(mat4(1), vec3(17.75, 6.5, -46)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));


			/* Store Front */
			//cover[0].draw(Shaders::material, translate(mat4(1), vec3(17.75, 0.625, -17.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			//cover[0].draw(Shaders::material, translate(mat4(1), vec3(17.75, 0.625, -24.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			cover[1].draw(Shaders::material, model * translate(mat4(1), vec3(18, 8, -10.25)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			ad[0].draw(Shaders::material, model * translate(mat4(1), vec3(18.1, 6, -23)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			ad[1].draw(Shaders::material, model * translate(mat4(1), vec3(18.1, 5, -30.5)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
		}


		static void drawInterior() {
			vec3 lightPos = vec3(model * vec4(vec3(8, 8, -18),1));
			Shaders::material.setVec3("lightPosition", lightPos);
			Shaders::material.setVec3("lightColor", vec3(1));

			drawProducts();

			/* Inside Ads */
			ad[2].draw(Shaders::material, model * translate(mat4(1), vec3(0.1, 7, -26)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			ad[3].draw(Shaders::material, model * translate(mat4(1), vec3(0.1, 7, -20)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			ad[4].draw(Shaders::material, model * translate(mat4(1), vec3(13.75, 6.5, -1.1)) * rotate(mat4(1), radians(180.0f), vec3(0, 1, 0)));

			fridge.draw(Shaders::material, model * translate(mat4(1), vec3(14, 2.25, -35.40)));
			fridge.draw(Shaders::material, model * translate(mat4(1), vec3(9, 2.25, -35.40)));

			desk.draw(Shaders::material, model * translate(mat4(1), vec3(14, 1, -6)));


			// Draw Holders Without Mapping
			centerHolder.draw(Shaders::material, model * translate(mat4(1), vec3(11.5, 1.5, -14)));
			centerHolder.draw(Shaders::material, model * translate(mat4(1), vec3(6, 1.5, -14)));
			centerHolder.draw(Shaders::material, model * translate(mat4(1), vec3(11.5, 1.5, -23)));
			centerHolder.draw(Shaders::material, model * translate(mat4(1), vec3(6, 1.5, -23)));

			holder.draw(Shaders::material, model * translate(mat4(1), vec3(6.5, 2, -3)));
			holder.draw(Shaders::material, model * translate(mat4(1), vec3(1.75, 2, -7.5)) * rotate(mat4(1), radians(-90.0f), vec3(0, 1, 0)) );

			holder.draw(Shaders::material, model * translate(mat4(1), vec3(1.75, 2, -31.5)) * rotate(mat4(1), radians(-90.0f), vec3(0, 1, 0)));
		}



		static void drawTransperent() {
			window[0].draw(Shaders::material, model * translate(mat4(1), vec3(18, 5.5, -2.25)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[0].draw(Shaders::material, model * translate(mat4(1), vec3(18, 5.5, -4.75)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			window[7].draw(Shaders::material, model * translate(mat4(1), vec3(18, 1.25, -8.6)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[7].draw(Shaders::material, model * translate(mat4(1), vec3(18, 1.25, -11.85)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[8].draw(Shaders::material, model * translate(mat4(1), vec3(18, 5.25, -8.6)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[8].draw(Shaders::material, model * translate(mat4(1), vec3(18, 5.25, -11.85)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			window[1].draw(Shaders::material, model * translate(mat4(1), vec3(18, 0.625, -16)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[1].draw(Shaders::material, model * translate(mat4(1), vec3(18, 0.625, -19)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[2].draw(Shaders::material, model * translate(mat4(1), vec3(18, 4.625, -16)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[2].draw(Shaders::material, model * translate(mat4(1), vec3(18, 4.625, -19)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[3].draw(Shaders::material, model * translate(mat4(1), vec3(18, 8, -16)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[3].draw(Shaders::material, model * translate(mat4(1), vec3(18, 8, -19)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			window[1].draw(Shaders::material, model * translate(mat4(1), vec3(18, 0.625, -23)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[1].draw(Shaders::material, model * translate(mat4(1), vec3(18, 0.625, -26)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[2].draw(Shaders::material, model * translate(mat4(1), vec3(18, 4.625, -23)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[2].draw(Shaders::material, model * translate(mat4(1), vec3(18, 4.625, -26)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[3].draw(Shaders::material, model * translate(mat4(1), vec3(18, 8, -23)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[3].draw(Shaders::material, model * translate(mat4(1), vec3(18, 8, -26)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));

			window[4].draw(Shaders::material, model * translate(mat4(1), vec3(18, 0.625, -30.625)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[4].draw(Shaders::material, model * translate(mat4(1), vec3(18, 0.625, -34.825)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[5].draw(Shaders::material, model * translate(mat4(1), vec3(18, 4.625, -30.625)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[5].draw(Shaders::material, model * translate(mat4(1), vec3(18, 4.625, -34.825)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[6].draw(Shaders::material, model * translate(mat4(1), vec3(18, 8, -30.625)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
			window[6].draw(Shaders::material, model * translate(mat4(1), vec3(18, 8, -34.825)) * rotate(mat4(1), radians(90.0f), vec3(0, 1, 0)));
		}



		


	};

}