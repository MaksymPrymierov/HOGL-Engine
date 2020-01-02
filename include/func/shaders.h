#ifndef SHADERS_H
#define SHADERS_H

#include <string>
#include <exception>

#include <GL/glew.h>

namespace shaders
{
	class shader_compilation_ex: public std::exception
	{
		private:
			std::string what_message;

		public:
			shader_compilation_ex(const std::string message) : what_message(message)
			{}

		const char* what() const throw()
		{
			return what_message.c_str();
		}
	};

	unsigned int createShader(unsigned int type, const std::string& src);
	void validateShader(unsigned int shader);
}

#endif
