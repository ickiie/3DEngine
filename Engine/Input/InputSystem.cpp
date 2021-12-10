#include "InputSystem.h"
#include <SDL_keyboard.h>
#include <SDL.h>
#include <array>
#include <algorithm>

namespace nc {

	InputSystem::eKeyState InputSystem::GetKeyState(int id)
	{
		eKeyState state = eKeyState::Idle;

		bool keyDown = IsKeyDown(id);
		bool prevKeyDown = IsPreviousKeyDown(id);

		if (keyDown)
		{
			state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed;
		}
		else
		{
			state = (prevKeyDown) ? eKeyState::Release : eKeyState::Idle;
		}

		return state;
	}

	InputSystem::eKeyState InputSystem::GetButtonState(int id)
	{
		eKeyState state = eKeyState::Idle;

		bool keyDown = isButtonDown(id);
		bool prevKeyDown = isPrevButtonDown(id);

		if (keyDown)
		{
			state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed;
		}
		else
		{
			state = (prevKeyDown) ? eKeyState::Release : eKeyState::Idle;
		}

		return state;
	}

	/*bool InputSystem::IsKeyDown(int id)
	{
		return keyboardState[id];
	}
	bool InputSystem::IsPreviousKeyDown(int id)
	{
		return prevKeyboardState[id];
	}*/

	void InputSystem::Startup()
	{
		// get pointer to sdl keyboard states
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(&numKeys);
		// resize of keyboard state using numKeys for size
		keyboardState.resize(numKeys);
		// copy sdl keyboard state to keyboard state vector
		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardState.begin());
		// set previous keyboard state to keyboard state
		prevKeyboardState = keyboardState;

		// set initial mouse position
		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		mousePosition = glm::vec2{ x , y };
		prevMousePosition = mousePosition;

	}

	void InputSystem::Shutdown()
	{
	}

	void InputSystem::Update(float dt)
	{
		// set the previous keyboard state to keyboard state
		prevKeyboardState = keyboardState;
		// copy the current SDL keyboard state to keyboard state
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardState.begin());

		prevMouseButtonState = mouseButtonState;
		prevMousePosition = mousePosition;
		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		mousePosition = glm::vec3{ x,y,0 };
		mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; //button [0000]
		mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; //button [0000]
		mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; //button [0000]
		mouseRelative = mousePosition - prevMousePosition;

		mousePosition = glm::vec3{ x,y,0 };

	}

}