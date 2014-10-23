#include "game.h"
#include "dbg.h"

using namespace game10_tetris;

namespace game10_game
{
	void Game10::error_callback(int error, const char*description)
	{
		log_err("Error code: %i Message: %s", error, description);
	}

	void Game10::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		else if (action > 0)
		{
			Tetris *t = (Tetris*)glfwGetWindowUserPointer(window);
			switch (key)
			{
			case GLFW_KEY_RIGHT:
				t->move_r();
				break;
			case GLFW_KEY_LEFT:
				t->move_l();
				break;
			case GLFW_KEY_DOWN:
				t->tick();
				break;
			case GLFW_KEY_UP:
				t->turn();
				break;
			case GLFW_KEY_SPACE:
				t->drop();
				break;
			}
		}
	}

	void Game10::resize_callback(GLFWwindow *window, int width, int height)
	{
		if (width > MIN_RES_W || height > MIN_RES_H)
		{
			glfwSetWindowSize(window, MIN_RES_W, MIN_RES_H);
		}
		else
		{
			glfwSetWindowSize(window, width, height);
		}
	}

	Game10::~Game10()
	{
		if (tetris != NULL)
		{
			delete tetris;
		}
	}

	bool Game10::init()
	{
		glfwSetErrorCallback(error_callback);

		if (!glfwInit())
		{
			return false;
		}

		window = glfwCreateWindow(MIN_RES_W, MIN_RES_H, "", NULL, NULL);

		if (window == NULL)
		{
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowSizeCallback(window, resize_callback);

		return true;
	}

	int Game10::start()
	{
		tetris = new Tetris();

		if (!init() || tetris == NULL)
		{
			exit(EXIT_FAILURE);
		}

		glfwSetWindowUserPointer(window, tetris);

		double time, last_time = glfwGetTime();
		int frames = 0;
		int ptick = 0;

		while (!glfwWindowShouldClose(window))
		{
			time = glfwGetTime();
			glfwPollEvents();
			if (time - last_time >= 0.5f)
			{
				TickResult res = tetris->tick();
				if (res == game_over)
					glfwSetWindowShouldClose(window, GL_TRUE);
				else if (res == move_down && tetris->getParty())
					ptick++;

				char title[256];
				double diffms = (time - last_time) * 1000;
				snprintf(title, 255, "Score: %i FPS: %3.0f LAT: %3.2fms",
					tetris->getScore(), (double)frames * 2, diffms / frames);

				glfwSetWindowTitle(window, title);

				last_time = glfwGetTime();
				frames = 0;
				if (ptick > 6)
				{
					tetris->setParty(false);
					ptick = 0;
				}
			}

			draw(window, tetris);
			glfwSwapBuffers(window);

			frames++;
		}

		glfwDestroyWindow(window);
		glfwTerminate();

		return tetris->getScore();
	}
}
