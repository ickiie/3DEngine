#pragma once

#define REGISTER_CLASS(class) nc::ObjectFactory::Instance().Register<class>(#class);
#define CREATE_ENGINE_OBJECT(class) nc::ObjectFactory::Instance().Create<nc::class>(#class);

//core
#include "Core/Utilities.h"
#include "Core/FileSystem.h"
#include "Core/Timer.h"
#include "Core/Json.h"
#include "Core/Serializable.h"

//framework
#include "Framework/EventSystem.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"

//math
#include "Math/MathTypes.h"
//#include "Math/glm::vec3.h"
//#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

// graphics
#include "Graphics/Renderer.h" 
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Graphics/Program.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexBuffer.h"
//#include "Graphics/VertexIndexBuffer.h"
//#include "Graphics/Font.h"
//#include "Graphics/ParticleSystem.h"

// Physics System
//#include "Physics/PhysicsSystem.h"

//audio
#include "Audio/AudioSystem.h"

//Input
#include "Input/InputSystem.h"

//Object
#include "Object/Actor.h"
#include "Object/Scene.h"
//#include "Object/Tilemap.h"

//Components
//#include "Components/SpriteComponent.h"
//#include "Components/SpriteAnimationComponent.h"
#include "Components/PhysicsComponent.h"
//#include "Components/RBPhysicsComponent.h"
#include "Components/AudioComponent.h"
//#include "Components/TextComponent.h"
#include "Components/CameraComponent.h"
#include "Components/MeshComponent.h"
#include "Components/ModelComponent.h"
#include "Components/CameraComponent.h"
#include "Components/FreeCameraController.h"
#include "Components/LightComponent.h"

//Resource
#include "Resource/ResourceSystem.h"

#include <vector>
#include <memory>
#include <algorithm>

namespace nc {

	using ObjectFactory = Singleton<Factory<std::string, Object>>;

	class Engine {

	public:
		void Startup();
		void Shutdown();

		void Update();
		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();


	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get() {

		for (auto& system : systems) {

			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}
