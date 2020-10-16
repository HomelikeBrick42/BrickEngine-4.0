#include "pch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace BrickEngine {

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		const char* vShaderCode = vertexSource.c_str();
		const char* fShaderCode = fragmentSource.c_str();
		uint32_t vertexShader, fragmentShader, shader;

		// Vertex Shader
		{
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vShaderCode, NULL);
			glCompileShader(vertexShader);

			int32_t success;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				std::cout << "Vertex Shader Compilation Failed!\n" << infoLog << std::endl;
			};
		}
		// Fragment Shader
		{
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
			glCompileShader(fragmentShader);

			int32_t success;
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
				std::cout << "Fragment Shader Compilation Failed!\n" << infoLog << std::endl;
			};
		}
		// Shader Program
		{
			shader = glCreateProgram();
			glAttachShader(shader, vertexShader);
			glAttachShader(shader, fragmentShader);
			glLinkProgram(shader);

			int32_t success;
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				glGetProgramInfoLog(shader, 512, NULL, infoLog);
				std::cout << "Shader Linking Failed\n" << infoLog << std::endl;
			}
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		m_RendererID = shader;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetFloatMatrix2x2(const std::string& name, const glm::mat2x2& matrix, bool transpose)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniformMatrix2fv(location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetFloatMatrix3x3(const std::string& name, const glm::mat3x3& matrix, bool transpose)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniformMatrix3fv(location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetFloatMatrix4x4(const std::string& name, const glm::mat4x4& matrix, bool transpose)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniformMatrix4fv(location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetDoubleMatrix2x2(const std::string& name, const glm::dmat2x2& matrix, bool transpose)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniformMatrix2dv(location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetDoubleMatrix3x3(const std::string& name, const glm::dmat3x3& matrix, bool transpose)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniformMatrix3dv(location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetDoubleMatrix4x4(const std::string& name, const glm::dmat4x4& matrix, bool transpose)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniformMatrix4dv(location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetInt(const std::string& name, int32_t value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform1i(location, value);
	}

	void OpenGLShader::SetInt2(const std::string& name, const glm::ivec2& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform2i(location, value.x, value.y);
	}

	void OpenGLShader::SetInt3(const std::string& name, const glm::ivec3& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform3i(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetInt4(const std::string& name, const glm::ivec4& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform4i(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int32_t* values, uint32_t count)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform1iv(location, count, values);
	}

	void OpenGLShader::SetUInt(const std::string& name, uint32_t value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform1ui(location, value);
	}

	void OpenGLShader::SetUInt2(const std::string& name, const glm::uvec2& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform2ui(location, value.x, value.y);
	}

	void OpenGLShader::SetUInt3(const std::string& name, const glm::uvec3& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform3ui(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetUInt4(const std::string& name, const glm::uvec4& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform4ui(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetUIntArray(const std::string& name, uint32_t* values, uint32_t count)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform1uiv(location, count, values);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetFloatArray(const std::string& name, float* values, uint32_t count)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform1fv(location, count, values);
	}

	void OpenGLShader::SetDouble(const std::string& name, double value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform1d(location, value);
	}

	void OpenGLShader::SetDouble2(const std::string& name, const glm::dvec2& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform2d(location, value.x, value.y);
	}

	void OpenGLShader::SetDouble3(const std::string& name, const glm::dvec3& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform3d(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetDouble4(const std::string& name, const glm::dvec4& value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform4d(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetDoubleArray(const std::string& name, double* values, uint32_t count)
	{
		int32_t location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			Log::Error("Unable to find uniform named '{0}'", name);
		else
			glUniform1dv(location, count, values);
	}

}
