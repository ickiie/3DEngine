#pragma once
#include "Framework/System.h"
//#include "Math/glm::vec3.h"
#include "Math/MathTypes.h"
#include <SDL.h>
#include <vector>
#include <array>

namespace nc {

	class InputSystem : public System {

	public:
		enum class eKeyState { Idle, Pressed, Held, Release };
		enum class eMouseButton { Left, Middle, Right };

		// Inherited via System
		virtual void Startup() override;
		virtual void Shutdown() override;
		virtual void Update(float dt) override;

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id) const { return keyboardState[id]; }
		bool IsPreviousKeyDown(int id) const { return prevKeyboardState[id]; }

		const glm::vec2& GetMousePosition() { return mousePosition; }
		const glm::vec2& GetMouseRelative() { return mouseRelative; }
		bool isButtonDown(int id) { return mouseButtonState[id]; }
		bool isPrevButtonDown(int id) { return prevMouseButtonState[id]; }

		eKeyState GetButtonState(int id);

	private:
		std::vector<Uint8> keyboardState;
		std::vector<Uint8> prevKeyboardState;
		int numKeys;

		glm::vec2 mousePosition;
		glm::vec2 prevMousePosition;
		glm::vec2 mouseRelative;
		std::array<Uint8, 3> mouseButtonState;
		std::array<Uint8, 3> prevMouseButtonState;

	};

}