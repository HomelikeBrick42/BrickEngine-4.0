#pragma once

#include "BrickEngine/Renderer/Shader.h"

namespace BrickEngine {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetFloatMatrix2x2(const std::string& name, const glm::mat2x2& matrix, bool transpose = false) override;
		virtual void SetFloatMatrix3x3(const std::string& name, const glm::mat3x3& matrix, bool transpose = false) override;
		virtual void SetFloatMatrix4x4(const std::string& name, const glm::mat4x4& matrix, bool transpose = false) override;

		virtual void SetDoubleMatrix2x2(const std::string& name, const glm::dmat2x2& matrix, bool transpose = false) override;
		virtual void SetDoubleMatrix3x3(const std::string& name, const glm::dmat3x3& matrix, bool transpose = false) override;
		virtual void SetDoubleMatrix4x4(const std::string& name, const glm::dmat4x4& matrix, bool transpose = false) override;

		virtual void SetInt(const std::string& name, int32_t value) override;
		virtual void SetInt2(const std::string& name, const glm::ivec2& value) override;
		virtual void SetInt3(const std::string& name, const glm::ivec3& value) override;
		virtual void SetInt4(const std::string& name, const glm::ivec4& value) override;
		virtual void SetIntArray(const std::string& name, int32_t* values, uint32_t count) override;

		virtual void SetUInt(const std::string& name, uint32_t value) override;
		virtual void SetUInt2(const std::string& name, const glm::uvec2& value) override;
		virtual void SetUInt3(const std::string& name, const glm::uvec3& value) override;
		virtual void SetUInt4(const std::string& name, const glm::uvec4& value) override;
		virtual void SetUIntArray(const std::string& name, uint32_t* values, uint32_t count) override;

		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetFloatArray(const std::string& name, float* values, uint32_t count) override;

		virtual void SetDouble(const std::string& name, double value) override;
		virtual void SetDouble2(const std::string& name, const glm::dvec2& value) override;
		virtual void SetDouble3(const std::string& name, const glm::dvec3& value) override;
		virtual void SetDouble4(const std::string& name, const glm::dvec4& value) override;
		virtual void SetDoubleArray(const std::string& name, double* values, uint32_t count) override;
	private:
		uint32_t m_RendererID;
	};

}
