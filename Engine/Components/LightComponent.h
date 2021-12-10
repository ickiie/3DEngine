#pragma once
#include "Component.h"
#include "CameraComponent.h"
#include "Engine.h"

namespace nc {

	class LightComponent : public Component
	{
	public:
		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		/*<declare a vec3 for ambient, set default value to 0>
		<declare a vec3 for diffuse, set default value to 1>
		<declare a vec3 for specular, set default value to 1>*/

		glm::vec3 ambient{ 0 };
		glm::vec3 diffuse{ 1 };
		glm::vec3 specular{ 1 };
	};

}