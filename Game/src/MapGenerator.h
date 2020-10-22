#pragma once

#include "pch.h"
#include "Vertex.h"

#include "SimplexNoise.h"

class MapGenerator
{
public:
	static Ref<VertexArray> GenerateMap(uint32_t xSize, uint32_t zSize, OpenSimplexNoise noise)
	{
		std::vector<Vertex> vertices((xSize + 1) * (zSize + 1));
		std::vector<uint32_t> indices(xSize * zSize * 6);

		uint32_t i = 0;
		for (uint32_t z = 0; z <= zSize; z++)
		{
			for (uint32_t x = 0; x <= xSize; x++)
			{
				vertices[i].Position = glm::vec3(x - xSize * 0.5f, noise.Evaluate(x / 20.0f, z  / 20.0f) * 2.0f, z - zSize * 0.5f);
				i++;
			}
		}

		uint32_t vert = 0;
		uint32_t tris = 0;
		for (uint32_t z = 0; z < zSize; z++)
		{
			for (uint32_t x = 0; x < xSize; x++)
			{
				indices[tris + 0] = vert + 0;
				indices[tris + 1] = vert + xSize + 1;
				indices[tris + 2] = vert + 1;
				indices[tris + 3] = vert + 1;
				indices[tris + 4] = vert + xSize + 1;
				indices[tris + 5] = vert + xSize + 2;

				vert++;
				tris += 6;
			}
			vert++;
		}

		uint32_t triangleCount = indices.size() / 3;
		for (uint32_t i = 0; i < triangleCount; i++)
		{
			uint32_t normalTriangleIndex = i * 3;
			uint32_t vertexNormalA = indices[normalTriangleIndex + 0];
			uint32_t vertexNormalB = indices[normalTriangleIndex + 1];
			uint32_t vertexNormalC = indices[normalTriangleIndex + 2];

			glm::vec3 pointA = vertices[vertexNormalA].Position;
			glm::vec3 pointB = vertices[vertexNormalB].Position;
			glm::vec3 pointC = vertices[vertexNormalC].Position;

			glm::vec3 sizeAB = pointB - pointA;
			glm::vec3 sizeAC = pointC - pointA;

			glm::vec3 triangleNormal = glm::normalize(glm::cross(sizeAB, sizeAC));

			vertices[vertexNormalA].Normal += triangleNormal;
			vertices[vertexNormalB].Normal += triangleNormal;
			vertices[vertexNormalC].Normal += triangleNormal;
		}

		for (uint32_t i = 0; i < vertices.size(); i++)
		{
			vertices[i].Normal = glm::normalize(vertices[i].Normal);
		}

		Ref<VertexArray> vertexArray = VertexArray::Create();
		vertexArray->Bind();

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(Vertex));
		vertexBuffer->Bind();

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Normal"   },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float4, "a_Color"    }
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), indices.size());
		indexBuffer->Bind();
		vertexArray->SetIndexBuffer(indexBuffer);

		return vertexArray;
	}
};
