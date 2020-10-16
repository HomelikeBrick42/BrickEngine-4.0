#pragma once

#include "BrickEngine/Core/Base.h"

#include "BrickEngine/Renderer/Shader.h"
#include "BrickEngine/Renderer/VertexArray.h"

#include "BrickEngine/Scene/EntityScript.h"

namespace BrickEngine {

	struct Transform
	{
		glm::vec3 Position;
		glm::quat Rotation;
		glm::vec3 Scale;

		Transform(const glm::vec3& position = glm::vec3(0.0f), const glm::quat& rotation = glm::quat(), const glm::vec3& scale = glm::vec3(1.0f))
			: Position(position), Rotation(rotation), Scale(scale) {}

		glm::mat4 GetMatrix() const
		{
			return
				glm::translate(glm::mat4(1.0f), Position) *
				glm::mat4_cast(Rotation) *
				glm::scale(glm::mat4(1.0f), Scale);
		}

		operator glm::mat4() const { return GetMatrix(); }
	};

	struct MeshRenderer
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> Shader;

		MeshRenderer() = default;
		MeshRenderer(const Ref<BrickEngine::VertexArray>& vertexArray, const Ref<BrickEngine::Shader>& shader)
			: VertexArray(vertexArray), Shader(shader) {}
	};

	struct Camera
	{
		glm::mat4 Projection;

		Camera(const glm::mat4& projection = glm::mat4(1.0f))
			: Projection(projection) {}
	};

	struct Script
	{
		EntityScript* Instance = nullptr;

		EntityScript* (*InstantiateScript)();
		void (*DestroyScript)(Script*);

		template<typename T, typename... Args>
		void Bind(const Args&... args)
		{
			if (Instance)
				DestroyScript(this);
			InstantiateScript = []() { return static_cast<EntityScript*>(new T(args...)); };
			DestroyScript = [](Script* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

}
