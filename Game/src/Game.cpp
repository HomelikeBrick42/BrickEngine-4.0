#include "pch.h"

#include "Vertex.h"
#include "CameraController.h"

#include "SimplexNoise.h"
#include "MapGenerator.h"

class GameApplication : public Application
{
public:
	GameApplication()
		: Application("Game")
	{
		m_VertexArray = VertexArray::Create();
		m_VertexArray->Bind();

		Vertex positions[] = {
			Vertex({ -0.5f, -0.5f, 0.0f }, { 0.2f, 0.8f, 0.3f, 1.0f }),
			Vertex({ -0.5f,  0.5f, 0.0f }, { 0.8f, 0.8f, 0.3f, 1.0f }),
			Vertex({  0.5f,  0.5f, 0.0f }, { 0.8f, 0.2f, 0.3f, 1.0f }),
			Vertex({  0.5f, -0.5f, 0.0f }, { 0.2f, 0.3f, 0.8f, 1.0f })
		};
		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(positions, sizeof(positions));
		vertexBuffer->Bind();

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Normal"   },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float4, "a_Color"    }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		indexBuffer->Bind();
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexColorShaderVertexSource = R"(
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec4 a_Color;

out vec3 v_Normal;
out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_View * u_Model * a_Position;
	v_Normal = normalize(a_Normal);
	v_TexCoord = a_TexCoord;
	v_Color = a_Color;
}
)";
		std::string vertexColorShaderFragmentSource = R"(
#version 330 core

in vec3 v_Normal;
in vec2 v_TexCoord;
in vec4 v_Color;

out vec4 o_Color;

void main()
{
	vec3 normal = normalize(v_Normal);
	o_Color = vec4(v_Color.xyz * dot(normal, normalize(vec3(1.0, 1.0, 1.0))), v_Color.w);
}
)";
		m_VertexColorShader = Shader::Create(vertexColorShaderVertexSource, vertexColorShaderFragmentSource);

		m_Noise = OpenSimplexNoise(50);

		m_Entity = m_Scene.CreateEntity();
		m_Entity.AddComponent<Transform>();
		m_Entity.AddComponent<MeshRenderer>(m_VertexArray, m_VertexColorShader);

		Ref<VertexArray> va = MapGenerator::GenerateMap(1000, 1000, m_Noise);
		Entity entity = m_Scene.CreateEntity();
		entity.AddComponent<Transform>().Position.y = -2.0f;
		entity.AddComponent<MeshRenderer>(va, m_VertexColorShader);

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
	Ref<VertexArray> m_TerrainVertexArray;
	OpenSimplexNoise m_Noise;
};

int main()
{
	Application* app = new GameApplication();
	app->Run();
	delete app;
}
