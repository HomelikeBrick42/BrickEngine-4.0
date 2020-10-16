#pragma once

#include "BrickEngine/Renderer/Renderer.h"

namespace BrickEngine {

	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer();

		virtual void SetViewportImpl(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColorImpl(const glm::vec4& color) override;
		virtual void ClearImpl() override;

		virtual void BeginSceneImpl(const glm::mat4& projection) override;
		virtual void EndSceneImpl() override;

		virtual void DrawImpl(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, uint32_t count) override;
		virtual void DrawIndexedImpl(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, uint32_t count = 0) override;
		virtual void DrawIndexedImpl(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, const glm::mat4& transform, uint32_t count = 0) override;
	private:
		glm::mat4 m_ProjectionMatrix;
	};

}
