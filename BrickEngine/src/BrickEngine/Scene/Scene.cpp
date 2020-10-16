#include "pch.h"
#include "Scene.h"

#include "BrickEngine/Scene/Entity.h"
#include "BrickEngine/Scene/Components.h"
#include "BrickEngine/Renderer/Renderer.h"

namespace BrickEngine {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity()
	{
		entt::entity entityID = m_Registry.create();
		return Entity(entityID, this);
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity.m_EntityID);
	}

	void Scene::OnUpdate()
	{
		m_Registry.view<Script>().each([&](entt::entity entity, Script& sc)
			{
				if (!sc.Instance)
				{
					sc.Instance = sc.InstantiateScript();
					sc.Instance->m_Entity = Entity(entity, this);
					sc.Instance->OnCreate();
				}

				if (sc.Instance)
					sc.Instance->OnUpdate();
			});
	}

	void Scene::OnRender()
	{
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		m_Registry.view<Transform, Camera>().each([&](entt::entity, Transform& transform, Camera& camera)
			{
				viewMatrix = camera.Projection * glm::inverse(transform.GetMatrix());
			});

		Renderer::BeginScene(viewMatrix);
		m_Registry.view<Transform, MeshRenderer>().each([](entt::entity, Transform& transform, MeshRenderer& meshRenderer)
			{
				Renderer::DrawIndexed(meshRenderer.Shader, meshRenderer.VertexArray, transform);
			});
		Renderer::EndScene();

		m_Registry.view<Script>().each([&](entt::entity, Script& sc)
			{
				if (sc.Instance)
					sc.Instance->OnRender();
			});
	}

	void Scene::OnEvent(Event& e)
	{
		auto view = m_Registry.view<Script>();
		for (entt::entity id : view)
		{
			if (e.Handled)
				break;
			auto& sc = m_Registry.get<Script>(id);
			if (sc.Instance)
				sc.Instance->OnEvent(e);
		}
	}

}
