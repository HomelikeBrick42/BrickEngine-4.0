#pragma once

#include "BrickEngine/Core/Base.h"

#include "BrickEngine/Scene/Entity.h"

#include "BrickEngine/Events/Event.h"

namespace BrickEngine {

	class EntityScript
	{
	public:
		virtual ~EntityScript() {}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Entity.AddComponent<T>(std::forward(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Entity.HasComponent<T>();
		}

		template<typename T>
		void RemoveComponent()
		{
			m_Entity.RemoveComponent<T>();
		}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}
		virtual void OnEvent(Event& e) {}
	private:
		Entity m_Entity;
		friend class Scene;
	};

}
