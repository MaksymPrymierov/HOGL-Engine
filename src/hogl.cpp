#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLchar* vertexShaderProgram = "#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
	"}\n";

const GLchar* fragmentShaderProgram = "#version 330 core\n"
	"layout (location = 0) out vec4 color;\n"
	"void main()\n"
	"{\n"
	"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n";

int main(int argc, char** argv)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "HOGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error occured during GLEW initialization\n";
		return EXIT_FAILURE;
	}

	/* Compile vertex shader */
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderProgram, nullptr);
	glCompileShader(vertexShader);

	/* Check if vertex shader has been compiled without errors */
	int success = 0;
	GLchar log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, sizeof(log), nullptr, log);
		std::cout << "Error during vertex shader compilation\n" << log << std::endl;
	}

	/* Compile fragment shader */
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderProgram, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	/* Check if vertex shader has been compiled without errors */
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(log), nullptr, log);
		std::cout << "Error during vertex shader compilation\n" << log << std::endl;
	}

	/* Link shaders in shader program */
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
		glfwPollEvents();
		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return EXIT_SUCCESS;
}
