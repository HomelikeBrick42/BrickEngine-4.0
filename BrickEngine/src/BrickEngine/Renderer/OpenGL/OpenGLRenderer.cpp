#include "pch.h"
#include "OpenGLRenderer.h"

#include <glad/glad.h>

namespace BrickEngine {

	OpenGLRenderer::OpenGLRenderer()
	{
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
	}

	void OpenGLRenderer::SetViewportImpl(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderer::SetClearColorImpl(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderer::ClearImpl()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::BeginSceneImpl(const glm::mat4& projection)
	{
		m_ProjectionMatrix = projection;
	}

	void OpenGLRenderer::EndSceneImpl()
	{
		m_ProjectionMatrix = glm::mat4(1.0f);
	}

	void OpenGLRenderer::DrawImpl(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, uint32_t count)
	{
		shader->Bind();
		shader->SetFloatMatrix4x4("u_View", m_ProjectionMatrix);
		vertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void OpenGLRenderer::DrawIndexedImpl(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, uint32_t count)
	{
		shader->Bind();
		shader->SetFloatMatrix4x4("u_View", m_ProjectionMatrix);
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, count == 0 ? vertexArray->GetIndexBuffer()->GetCount() : count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderer::DrawIndexedImpl(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, const glm::mat4& transform, uint32_t count)
	{
		shader->Bind();
		shader->SetFloatMatrix4x4("u_View", m_ProjectionMatrix);
		shader->SetFloatMatrix4x4("u_Model", transform);
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, count == 0 ? vertexArray->GetIndexBuffer()->GetCount() : count, GL_UNSIGNED_INT, nullptr);
	}

}
