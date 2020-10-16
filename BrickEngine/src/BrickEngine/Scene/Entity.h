#pragma once

#include "BrickEngine/Scene/Scene.h"

namespace BrickEngine {

	class Entity
	{
		friend class Scene;
	public:
		Entity()
			: m_EntityID(entt::null), m_Scene(nullptr) {}
		Entity(entt::entity id, Scene* scene)
			: m_EntityID(id), m_Scene(scene) {}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			BRICKENGINE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			BRICKENGINE_CORE_ASSERT(HasComponent<T>(), "Entity doen't have component!");
			return m_Scene->m_Registry.get<T>(m_EntityID);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityID);
		}

		template<typename T>
		void RemoveComponent()
		{
			BRICKENGINE_CORE_ASSERT(HasComponent<T>(), "Entity doen't have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityID != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityID; }

		bool operator==(const Entity& other) const
		{
			return m_EntityID == other.m_EntityID && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		entt::entity m_EntityID;
		Scene* m_Scene;
	};

}
