#ifndef HOGLENGINE_H
#define HOGLENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class HOGLEngine
{
private:
	GLFWwindow* _window = nullptr;
	unsigned int _width = 640;
	unsigned int _height = 480;

public:
	HOGLEngine();
	~HOGLEngine();
	int initialize();
	unsigned int windowWidth() const { return _width; }
	unsigned int windowHeight() const { return _height; }
	GLFWwindow* window() { return _window; }
	void pollEvents() const;
	void swapBuffers() const;
};

#endif
