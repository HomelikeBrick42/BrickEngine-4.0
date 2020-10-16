#pragma once

#include "BrickEngine/Core/Base.h"

#include "BrickEngine/Renderer/VertexArray.h"
#include "BrickEngine/Renderer/Shader.h"

namespace BrickEngine {

	enum class RendererAPI
	{
		Unknown = 0,
		OpenGL
	};

	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		static void Init(RendererAPI api = RendererAPI::OpenGL);

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_Renderer->SetViewportImpl(x, y, width, height); }

		inline static void SetClearColor(const glm::vec4& color) { s_Renderer->SetClearColorImpl(color); }
		inline static void Clear() { s_Renderer->ClearImpl(); }

		inline static void BeginScene(const glm::mat4& projection) { s_Renderer->BeginSceneImpl(projection); }
		inline static void EndScene() { s_Renderer->EndSceneImpl(); }

		inline static void Draw(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, uint32_t count) { s_Renderer->DrawImpl(shader, vertexArray, count); }
		inline static void DrawIndexed(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, uint32_t count = 0) { s_Renderer->DrawIndexedImpl(shader, vertexArray, count); }
		inline static void DrawIndexed(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, const glm::mat4& transform, uint32_t count = 0) { s_Renderer->DrawIndexedImpl(shader, vertexArray, transform, count); }

		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	protected:
		virtual void SetViewportImpl(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColorImpl(const glm::vec4& color) = 0;
		virtual void ClearImpl() = 0;

		virtual void BeginSceneImpl(const glm::mat4& projection) = 0;
		virtual void EndSceneImpl() = 0;

		virtual void DrawImpl(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, uint32_t count) = 0;
		virtual void DrawIndexedImpl(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, uint32_t count = 0) = 0;
		virtual void DrawIndexedImpl(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, const glm::mat4& transform, uint32_t count = 0) = 0;
	protected:
		Renderer() = default;
	private:
		static RendererAPI s_RendererAPI;
		static Scope<Renderer> s_Renderer;
	};

}
