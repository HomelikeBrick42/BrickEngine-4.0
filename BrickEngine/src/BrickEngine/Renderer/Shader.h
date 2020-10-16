#pragma once

#include "BrickEngine/Core/Base.h"

namespace BrickEngine {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetFloatMatrix2x2(const std::string& name, const glm::mat2x2& matrix, bool transpose = false) = 0;
		virtual void SetFloatMatrix3x3(const std::string& name, const glm::mat3x3& matrix, bool transpose = false) = 0;
		virtual void SetFloatMatrix4x4(const std::string& name, const glm::mat4x4& matrix, bool transpose = false) = 0;

		virtual void SetDoubleMatrix2x2(const std::string& name, const glm::dmat2x2& matrix, bool transpose = false) = 0;
		virtual void SetDoubleMatrix3x3(const std::string& name, const glm::dmat3x3& matrix, bool transpose = false) = 0;
		virtual void SetDoubleMatrix4x4(const std::string& name, const glm::dmat4x4& matrix, bool transpose = false) = 0;

		virtual void SetInt(const std::string& name, int32_t value) = 0;
		virtual void SetInt2(const std::string& name, const glm::ivec2& value) = 0;
		virtual void SetInt3(const std::string& name, const glm::ivec3& value) = 0;
		virtual void SetInt4(const std::string& name, const glm::ivec4& value) = 0;
		virtual void SetIntArray(const std::string& name, int32_t* values, uint32_t count) = 0;

		virtual void SetUInt(const std::string& name, uint32_t value) = 0;
		virtual void SetUInt2(const std::string& name, const glm::uvec2& value) = 0;
		virtual void SetUInt3(const std::string& name, const glm::uvec3& value) = 0;
		virtual void SetUInt4(const std::string& name, const glm::uvec4& value) = 0;
		virtual void SetUIntArray(const std::string& name, uint32_t* values, uint32_t count) = 0;

		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetFloatArray(const std::string& name, float* values, uint32_t count) = 0;

		virtual void SetDouble(const std::string& name, double value) = 0;
		virtual void SetDouble2(const std::string& name, const glm::dvec2& value) = 0;
		virtual void SetDouble3(const std::string& name, const glm::dvec3& value) = 0;
		virtual void SetDouble4(const std::string& name, const glm::dvec4& value) = 0;
		virtual void SetDoubleArray(const std::string& name, double* values, uint32_t count) = 0;

		static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
	protected:
		Shader() = default;
	};

}
