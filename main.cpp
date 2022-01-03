#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

#include <App.h>
#include <graphics/font.h>
#include <graphics/shader_loader.h>

using namespace trade_history;

using app_clock = std::chrono::steady_clock;
using app_time = app_clock::time_point;
using app_duration = app_clock::duration;

bool setup();
void exitApp();

void update();
void render();

GLFWwindow *window = nullptr;
int width = 1080;
int height = 720;

int fps;
app_duration time_step;
app_duration lag(0);
app_time time_end;
app_time time_start;
long long elapsed_time = 0;

int updates = 0;
int frames = 0;

trade_history::App *app = nullptr;

int main()
{
	if (!setup()) exitApp();

	shader_loader::get_instance().load("shaders/text_shader.vert", "shaders/text_shader.frag");
	app = new App();
	time_end = app_clock::now();

	do
	{
		time_start = app_clock::now();
		app_duration delta_time = time_start - time_end;
		time_end = time_start;

		lag += delta_time;
		
		while (lag >= time_step)
		{
			lag -= time_step;
			update(); // update at a fixed rate each time
			updates++;
		}
		
		render();
		frames++;

		elapsed_time += delta_time.count();
		if (elapsed_time >= 1'000'000'000)
		{
			//std::cout << "FPS: " << frames << " Updates: " << updates << std::endl;
			elapsed_time = 0;
			frames = 0;
			updates = 0;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (!glfwWindowShouldClose(window));

	return 0;
}

void update()
{
	app->update();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	app->render();
}

bool setup()
{
	if (!glfwInit()) return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	time_step = app_duration(1'000'000'000 / mode->refreshRate);

	window = glfwCreateWindow(width, height, "Trade History", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Couldn't create window.";
		return false;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Couldn't init glew.";
		return false;
	}

	glViewport(0, 0, width, height);
	glClearColor(194.0f / 255.0f, 194.0f / 255.0f, 194.0f / 255.0f, 1.0f);
}

void exitApp()
{
	glfwTerminate();
	exit(-2);
}