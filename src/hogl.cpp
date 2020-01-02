#include <cstdlib>
#include <iostream>
#include <string>
#include <engine/hogl-engine.h>
#include <func/shaders.h>

int main(int argc, char** argv)
{
	HOGLEngine engine;

	try
	{
		engine.initialize();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
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
		std::cerr << e.what();
		return EXIT_FAILURE;
	}

	const std::string fragmentShaderSrc = "#version 330 core\n"
		"layout (location = 0) out vec4 color;\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";

	const std::string fragmentShaderSrc2 = "#version 330 core\n"
		"layout (location = 0) out vec4 color;\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n";

	unsigned int fragmentShaderO = 0;
	try
	{
		fragmentShaderO = shaders::createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	unsigned int fragmentShaderY = 0;
	try
	{
		fragmentShaderY = shaders::createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc2);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	/* Link shaders in shader program */
	int success = 0;
	char log[512];
	unsigned int shaderProgramOrange = glCreateProgram();
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderO);
	glLinkProgram(shaderProgramOrange);

	/* Check if shader program has been linked without errors */
	glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgramOrange, sizeof(log), nullptr, log);
		std::cout << "Error during shader program linking\n" << log << std::endl;
	}

	unsigned int shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderY);
	glLinkProgram(shaderProgramYellow);

	/* Check if shader program has been linked without errors */
	glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgramYellow, sizeof(log), nullptr, log);
		std::cout << "Error during shader program linking\n" << log << std::endl;
	}

	/* Remove shaders */
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderO);
	glDeleteShader(fragmentShaderY);

	float vertices[] = {
		-1.0f,  0.0f, 0.0f, // Left
		 0.5f,  0.0f, 0.0f, // Right
		-0.25f, 1.0f, 0.0f  // Top
	};

	unsigned int VBO[2], VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	/* Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s). */
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	/* Note that this is allowed, the call to glVertexAttribPointer registered VBO as
	the currently bound vertex buffer object so afterwards we can safely unbind */
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs) */
	glBindVertexArray(0);

	float vertices1[] = {
		-0.5f,  0.0f, 0.0f, // Left
		 1.0f,  0.0f, 0.0f, // Right
		 0.25f, 1.0f, 0.0f  // Bot
	};

	/* Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s). */
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

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

		glUseProgram(shaderProgramOrange);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		/* Swap front and back buffers */
		engine.swapBuffers();
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	return EXIT_SUCCESS;
}
