#pragma once

#include "BrickEngine/Core/Base.h"

namespace BrickEngine {

	enum class ShaderDataType
	{
		Unknown = 0,
		Bool,
		Bool2,
		Bool3,
		Bool4,
		Byte,
		Byte2,
		Byte3,
		Byte4,
		UByte,
		UByte2,
		UByte3,
		UByte4,
		Short,
		Short2,
		Short3,
		Short4,
		UShort,
		UShort2,
		UShort3,
		UShort4,
		Int,
		Int2,
		Int3,
		Int4,
		UInt,
		UInt2,
		UInt3,
		UInt4,
		Float,
		Float2,
		Float3,
		Float4,
		Double,
		Double2,
		Double3,
		Double4
	};

	class BufferElement
	{
	public:
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement()
			: Name(""), Type(ShaderDataType::Unknown), Size(0), Offset(0), Normalized(false) { CalculateSize(); }
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(0), Offset(0), Normalized(normalized) { CalculateSize(); }

		uint32_t GetElementCount() const;
	private:
		void CalculateSize();
	};

	class BufferLayout
	{
	public:
		BufferLayout()
			: m_Elements({}), m_Stride(0) {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements), m_Stride(0) { CalculateStrideAndOffset(); }
		BufferLayout(const std::vector<BufferElement>& elements)
			: m_Elements(elements), m_Stride(0) { CalculateStrideAndOffset(); }

		void CalculateStrideAndOffset();
		inline uint32_t GetStride() const { return m_Stride; }

		inline std::vector<BufferElement>& GetElements() { return m_Elements; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		inline std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

}
