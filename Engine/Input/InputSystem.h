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
		bool IsKeyDown(int id);
		bool IsPreviousKeyDown(int id);

		const glm::vec3 GetMousePosition() const { return mousePosition; }
		bool IsButtonDown(int id) { return mouseButtonState[id]; }
		bool IsPreviousButtonDown(int id) { return prevMouseButtonState[id]; }
		eKeyState GetButtonState(int id);

	private:
		std::vector<uint8_t> keyboardState;
		std::vector<uint8_t> prevKeyboardState;
		int numKeys;

		glm::vec3 mousePosition;
		std::array<Uint8, 3> mouseButtonState;
		std::array<Uint8, 3> prevMouseButtonState;

	};

}