#pragma once
#include "Component.h"

namespace nc
{
	class CameraComponent : public Component
	{
	public:
		void Update() override;

		void SetPerspective(float fov, float aspectRatio, float near, float far);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::mat4 projection{ 1 };
		glm::mat4 view{ 1 };
	};
}
