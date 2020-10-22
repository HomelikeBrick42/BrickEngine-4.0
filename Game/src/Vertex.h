#pragma once

#include "pch.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
	glm::vec4 Color;

	Vertex()
		: Position(glm::vec3(0.0f, 0.0f, 0.0f)), Normal(glm::vec3(0.0f, 0.0f, 0.0f)), TexCoord(glm::vec2(0.0f, 0.0f)), Color(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)) {}
	Vertex(const glm::vec3& position, const glm::vec4& color)
		: Position(position), Normal(glm::vec3(0.0f, 0.0f, 0.0f)), TexCoord(glm::vec2(0.0f, 0.0f)), Color(color) {}
	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texcoord)
		: Position(position), Normal(normal), TexCoord(texcoord), Color(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)) {}
	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec4& color)
		: Position(position), Normal(normal), TexCoord(glm::vec2(0.0f, 0.0f)), Color(color) {}
	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texcoord, const glm::vec4& color)
		: Position(position), Normal(normal), TexCoord(texcoord), Color(color) {}
};
