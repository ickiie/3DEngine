#include "Engine.h"

#include <glad\glad.h>
#include <sdl.h>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include <iostream>

// vertices
const float vertices[] =
{
	// front
	-1.0f, -1.0f,  1.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 1.0f, -1.0f,  1.0, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	 1.0f,  1.0f,  1.0, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f,  1.0, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	// back
	-1.0f, -1.0f, -1.0, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 1.0f, -1.0f, -1.0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	 1.0f,  1.0f, -1.0, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-1.0f,  1.0f, -1.0, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f
};



const GLuint indices[] =
{
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
};

// vertex shader
const char* vertexSource = R"(
    #version 430 core 

	layout(location = 0) in vec3 position;
	layout(location = 1) in vec3 color;

	out vec3 fs_color;

	uniform float scale;

    void main()
    {
		fs_color = color;
        gl_Position = vec4(position * scale, 1.0);
    }
)";

// fragment
const char* fragmentSource = R"(
    #version 430 core
	in vec3 fs_color;
    out vec4 outColor;

	uniform vec3 tint;

    void main()
    {
        outColor = vec4(fs_color, 1.0) * vec4(tint, 1.0);
    }
)";

int main(int argc, char** argv)
{
	nc::Engine engine;
	engine.Startup();
	engine.Get<nc::Renderer>()->Create("OpenGL", 800, 600);

	nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nc::SetFilePath("../resources");

	// set vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cout << buffer;
	}

	// set fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint fragStatus;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragStatus);
	if (fragStatus == GL_FALSE)
	{
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		std::cout << buffer;
	}

	// create shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// link and use shader program
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	GLint shadStatus;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &shadStatus);
	if (fragStatus == GL_FALSE)
	{
		char buffer[512];
		glGetShaderInfoLog(shaderProgram, 512, NULL, buffer);
		std::cout << buffer;
	}

	glUseProgram(shaderProgram);

	std::shared_ptr<nc::Program> program = engine.Get<nc::ResourceSystem>()->Get<nc::Program>("basic_program");
	std::shared_ptr<nc::Shader> vshader = engine.Get<nc::ResourceSystem>()->Get<nc::Shader>("shaders/basic.vert", (void*)GL_VERTEX_SHADER);
	std::shared_ptr<nc::Shader> fshader = engine.Get<nc::ResourceSystem>()->Get<nc::Shader>("shaders/basic.frag", (void*)GL_FRAGMENT_SHADER);

	program->AddShader(vshader);
	program->AddShader(fshader);
	program->Link();
	program->Use();

	// vertex array
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create vertex buffer
	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint ebo; //element buffer object
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLubyte*)NULL);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLubyte*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);




	// uniform

	//GLuint location = glGetUniformLocation(shaderProgram, "scale");
	float time = 1;
	program->SetUniform("scale", time);

	//GLuint tintLocation = glGetUniformLocation(shaderProgram, "tint");
	glm::vec3 tint{ 1.0f, 1.0f, 1.0f };
	program->SetUniform("tint", tint);

	glm::mat4 view{ 1 };
	//view = glm::lookAt(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
	program->SetUniform("view", view);

	glm::vec3 translate{ 0.0f };
	float angle = 0;
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}

		SDL_PumpEvents();
		engine.Update();

		time += engine.time.deltaTime;
		program->SetUniform("sclae", 0.5f);


		if (engine.Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == nc::InputSystem::eKeyState::Held) {
			translate.x += -1 * engine.time.deltaTime;
		}
		if (engine.Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == nc::InputSystem::eKeyState::Held) {
			translate.x += 1 * engine.time.deltaTime;
		}
		if (engine.Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_S) == nc::InputSystem::eKeyState::Held) {
			translate.y += -1 * engine.time.deltaTime;
		}
		if (engine.Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == nc::InputSystem::eKeyState::Held) {
			translate.y += 1 * engine.time.deltaTime;
		}
		angle += engine.time.deltaTime;

		glm::mat4 model{ 1.0f };

		glm::scale(model, glm::vec3{ 0.5f });
		model = glm::rotate(model, angle, glm::vec3{ 0, 1, 0 });
		model = glm::translate(model, translate * engine.time.deltaTime);
		program->SetUniform("model", model);

		/*glUniform1f(location, std::sin(time) * 1.5f);
		glUniform3fv(tintLocation, 1, &tint[0]);*/


		engine.Get<nc::Renderer>()->BeginFrame();

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glEnd();

		engine.Get<nc::Renderer>()->EndFrame();
	}

	return 0;
}
