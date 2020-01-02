#include <engine/hogl-engine.h>

HOGLEngine::HOGLEngine()
{}

HOGLEngine::~HOGLEngine()
{
	glfwTerminate();
}

void HOGLEngine::initialize()
{
	if (!glfwInit())
		throw engine_init_ex(std::string("Failed to initialize GLFW library.\n"));

	_window = glfwCreateWindow(_width, _height, "HOGL", nullptr, nullptr);

	if (!_window)
	{
		glfwTerminate();
		throw engine_init_ex(std::string("Failed to create window context.\n"));
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(_window);

	if (glewInit() != GLEW_OK)
	{
		throw engine_init_ex(std::string("Failed to initialize GLEW library. glewInit() != GLEW_OK\n"));
	}
}

void HOGLEngine::pollEvents() const
{
	glfwPollEvents();
}

void HOGLEngine::swapBuffers() const
{
	glfwSwapBuffers(_window);
}
