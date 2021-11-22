#include "Renderer.h"
#include "Math/Mathutils.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

namespace nc
{
	void Renderer::Startup()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}

		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();
	}

	void Renderer::Shutdown()
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);

		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}

	void Renderer::Update(float dt)
	{
	}

	void Renderer::Create(const std::string& name, int width, int height)
	{
		window = SDL_CreateWindow(name.c_str(), 100, 100, width, height, SDL_WINDOW_OPENGL);
		if (window == nullptr)
		{
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetSwapInterval(1);

		SDL_GLContext context = SDL_GL_CreateContext(window);
		if (!gladLoadGL())
		{
			SDL_Log("Failed to create OpenGL context");
			exit(-1);
		}

		glEnable(GL_DEPTH_TEST);

	}

	void Renderer::BeginFrame()
	{
		glClearColor(0.7, 0.15, 0.85, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::EndFrame()
	{
		SDL_GL_SwapWindow(window);
	}

	/*void Renderer::Draw(std::shared_ptr<nc::Texture> texture, const glm::vec3& position, float angle, const glm::vec3& scale)
	{
		glm::vec3 size = texture->GetSize();
		size = size * scale;
		glm::vec3 newPosition = position - (size * 0.5f);

		SDL_Rect dest;
		dest.x = static_cast<int>(newPosition.x);
		dest.y = static_cast<int>(newPosition.y);
		dest.w = static_cast<int>(size.x);
		dest.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(renderer, texture->texture, nullptr, &dest, nc::RadToDeg(angle), nullptr, SDL_FLIP_NONE);
	}

	void Renderer::Draw(std::shared_ptr<nc::Texture> texture, const Transform& transform)
	{
		glm::vec3 size = texture->GetSize();
		size = size * transform.scale;
		glm::vec3 newPosition = transform.position - (size * 0.5f);

		SDL_Rect dest;
		dest.x = static_cast<int>(newPosition.x);
		dest.y = static_cast<int>(newPosition.y);
		dest.w = static_cast<int>(size.x);
		dest.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(renderer, texture->texture, nullptr, &dest, nc::RadToDeg(transform.rotation), nullptr, SDL_FLIP_NONE);
	}
	void Renderer::Draw(std::shared_ptr<nc::Texture> texture, const SDL_Rect& source, const Transform& transform) {

		glm::vec3 size = glm::vec3{ source.w, source.h };
		size = size * transform.scale;
		glm::vec3 newPosition = transform.position - (size * 0.5f);

		SDL_Rect dest;
		dest.x = static_cast<int>(newPosition.x);
		dest.y = static_cast<int>(newPosition.y);
		dest.w = static_cast<int>(size.x);
		dest.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(renderer, texture->texture, &source, &dest, nc::RadToDeg(transform.rotation), nullptr, SDL_FLIP_NONE);
		
	}
	*/
}