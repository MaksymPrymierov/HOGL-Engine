#include <func/shaders.h>

unsigned int shaders::createShader(unsigned int type, const std::string& src)
{
	unsigned int shader = glCreateShader(type);
	const char* shader_src = src.c_str();

	/* Shader compilation */
	glShaderSource(shader, 1, &shader_src, nullptr);
	glCompileShader(shader);

	/* Check if vertex shader has been compiled without errors */
	validateShader(shader);

	return shader;
}

void shaders::validateShader(unsigned int shader)
{
	int success = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		/* Pull the error message */
		char info_log[1024];
		glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log);

		throw shaders::shader_compilation_ex(std::string(info_log));
	}
}
