#include <BrickEngine.h>

#include "CameraController.h"

using namespace BrickEngine;

class GameApplication : public Application
{
public:
	GameApplication()
		: Application("Game")
	{
		m_VertexArray = VertexArray::Create();
		m_VertexArray->Bind();
		{
			float positions[] = {
				 0.0f,  0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f
			};
			Ref<VertexBuffer> positionsVertexBuffer = VertexBuffer::Create(positions, sizeof(positions));
			positionsVertexBuffer->Bind();
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" }
			};
			positionsVertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(positionsVertexBuffer);
		}
		{
			float colors[] = {
				0.2f, 0.8f, 0.3f, 1.0f,
				0.8f, 0.2f, 0.3f, 1.0f,
				0.2f, 0.3f, 0.8f, 1.0f
			};
			Ref<VertexBuffer> colorsVertexBuffer = VertexBuffer::Create(colors, sizeof(colors));
			colorsVertexBuffer->Bind();
			BufferLayout layout = {
				{ ShaderDataType::Float4, "a_Color" }
			};
			colorsVertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(colorsVertexBuffer);
		}
		uint32_t indices[] = {
			0, 1, 2
		};
		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		indexBuffer->Bind();
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexColorShaderVertexSource = R"(
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_View * u_Model * a_Position;
	v_Color = a_Color;
}
)";
		std::string vertexColorShaderFragmentSource = R"(
#version 330 core

in vec4 v_Color;

out vec4 o_Color;

void main()
{
	o_Color = v_Color;
}
)";
		m_VertexColorShader = Shader::Create(vertexColorShaderVertexSource, vertexColorShaderFragmentSource);

		m_Entity = m_Scene.CreateEntity();
		m_Entity.AddComponent<Transform>();
		m_Entity.AddComponent<MeshRenderer>(m_VertexArray, m_VertexColorShader);

		m_Camera = m_Scene.CreateEntity();
		m_Camera.AddComponent<Transform>().Position.z = -1.5f;
		m_Camera.AddComponent<Camera>();
		m_Camera.AddComponent<Script>().Bind<CameraController>();
	}

	~GameApplication()
	{
	}

	void OnUpdate() override
	{
		m_Scene.OnUpdate();
		Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Renderer::Clear();
		m_Scene.OnRender();
	}

	void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>([&](WindowResizeEvent& e)
			{
				Renderer::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
				return false;
			});

		m_Scene.OnEvent(e);
	}
private:
	Scene m_Scene;
	Entity m_Entity;
	Entity m_Camera;
	Ref<Shader> m_VertexColorShader;
	Ref<VertexArray> m_VertexArray;
};

int main()
{
	Application* app = new GameApplication();
	app->Run();
	delete app;
}
