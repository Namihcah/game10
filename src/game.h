#ifndef game10_game_h
#define game10_game_h

#include "render.h"
#include "tetris.h"

namespace game10_game
{
	class Game10
	{
		game10_tetris::Tetris* tetris;
		GLFWwindow* window;
	public:
		bool init();
		int start();
		~Game10();

		static void error_callback(int error, const char*description);
		static void resize_callback(GLFWwindow *window, int width, int height);
		static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	};
}

#endif
