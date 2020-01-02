#include <cstdlib>
#include <iostream>
#include <string>
#include <engine/hogl-engine.h>
#include <func/shaders.h>

int main(int argc, char** argv)
{
	HOGLEngine engine;
	int code = engine.initialize();

	if (code != 1)
	{
		std::cout << "Failed to initialize HOGLEngine!\n Error code: " << code << std::endl;
		return EXIT_FAILURE;
	}
	/* Get window context */
	GLFWwindow* window = engine.window();

	const std::string vertexShaderSrc = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
		"}\n";

	unsigned int vertexShader = 0;
	try
	{
		vertexShader = shaders::createShader(GL_VERTEX_SHADER, vertexShaderSrc);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	const std::string fragmentShaderSrc = "#version 330 core\n"
		"layout (location = 0) out vec4 color;\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";

	unsigned int fragmentShader = 0;
	try
	{
		fragmentShader = shaders::createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	/* Link shaders in shader program */
	int success = 0;
	char log[512];
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	/* Check if shader program has been linked without errors */
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(log), nullptr, log);
		std::cout << "Error during shader program linking\n" << log << std::endl;
	}

	/* Remove shaders */
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left
		 0.5f, -0.5f, 0.0f, // Right
		 0.0f,  0.5f, 0.0f  // Top
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	/* Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s). */
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	/* Note that this is allowed, the call to glVertexAttribPointer registered VBO as
	the currently bound vertex buffer object so afterwards we can safely unbind */
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs) */
	glBindVertexArray(0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Poll for and process events */
		engine.pollEvents();
		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		/* Swap front and back buffers */
		engine.swapBuffers();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	return EXIT_SUCCESS;
}
