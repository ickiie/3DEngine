#include "Shader.h"
#include "Core/FileSystem.h"

namespace nc {

	Shader::~Shader() {
		if (shader != 0)
		{
			// delete shader
			glDeleteShader(shader);
		}

	}

	bool Shader::Load(const std::string& name, void* data)
	{
		// get shader source from file
		std::string source;
		bool success = ReadFileToString(name, source);
		if (success == false) {
			SDL_Log("Error: Failed to open file (%s).", name.c_str());
			return false;
		}

		// create shader
		GLuint shaderType = static_cast<GLuint>(reinterpret_cast<std::uintptr_t>(data));
		shader = glCreateShader(shaderType);

		// compile shader
		const char* source_c = source.c_str();
		glShaderSource(shader, 1, &source_c, NULL);
		glCompileShader(shader);

		// check shader compilation status
		// check program link status
		GLint status;
		glGetProgramiv(shader, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint length = 0;
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);

			if (length > 0)
			{
				std::string infoLog(length, ' ');
				glGetProgramInfoLog(shader, length, &length, &infoLog[0]);

				SDL_Log("Error: Failed to link program.");
				SDL_Log("Program Info: %s", infoLog.c_str());
			}

			glDeleteProgram(shader);

			shader = 0;

			return false;
		}

		return true;
	}

}