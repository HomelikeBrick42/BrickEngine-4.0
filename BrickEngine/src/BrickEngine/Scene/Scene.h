#pragma once

#include "BrickEngine/Core/Base.h"

#include "BrickEngine/Events/Event.h"

#include <entt.hpp>

namespace BrickEngine {

	class Entity;

	class Scene
	{
		friend class Entity;
	public:
		Scene();
		~Scene();

		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		template<typename... Types>
		std::vector<Entity> GetEntities()
		{
			std::vector<Entity> result;
			auto view = m_Registry.view<Types...>();
			for (auto& id : view)
			{
				result.emplace_back(id, this);
			}
			return result;
		}

		void OnUpdate();
		void OnRender();
		void OnEvent(Event& e);
	private:
		entt::registry m_Registry;
	};

}
