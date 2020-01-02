#include <hogl-engine.h>

HOGLEngine::HOGLEngine()
{}

HOGLEngine::~HOGLEngine()
{
	glfwTerminate();
}

int HOGLEngine::initialize()
{
	if (!glfwInit())
		return -1;

	_window = glfwCreateWindow(_width, _height, "HOGL", nullptr, nullptr);

	if (!_window)
	{
		glfwTerminate();
		return -2;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(_window);

	if (glewInit() != GLEW_OK)
	{
		return -3;
	}

	return 1;
}

void HOGLEngine::pollEvents() const
{
	glfwPollEvents();
}

void HOGLEngine::swapBuffers() const
{
	glfwSwapBuffers(_window);
}
