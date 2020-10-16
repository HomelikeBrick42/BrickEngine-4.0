#include "pch.h"
#include "BufferLayout.h"

namespace BrickEngine {

	void BufferElement::CalculateSize()
	{
		switch (Type)
		{
		case ShaderDataType::Bool:
			Size = sizeof(bool) * 1;
			return;
		case ShaderDataType::Bool2:
			Size = sizeof(bool) * 2;
			return;
		case ShaderDataType::Bool3:
			Size = sizeof(bool) * 3;
			return;
		case ShaderDataType::Bool4:
			Size = sizeof(bool) * 4;
			return;
		case ShaderDataType::Byte:
		case ShaderDataType::UByte:
			Size = sizeof(char) * 1;
			return;
		case ShaderDataType::Byte2:
		case ShaderDataType::UByte2:
			Size = sizeof(char) * 2;
			return;
		case ShaderDataType::Byte3:
		case ShaderDataType::UByte3:
			Size = sizeof(char) * 3;
			return;
		case ShaderDataType::Byte4:
		case ShaderDataType::UByte4:
			Size = sizeof(char) * 4;
			return;
		case ShaderDataType::Short:
		case ShaderDataType::UShort:
			Size = sizeof(short) * 1;
			return;
		case ShaderDataType::Short2:
		case ShaderDataType::UShort2:
			Size = sizeof(short) * 2;
			return;
		case ShaderDataType::Short3:
		case ShaderDataType::UShort3:
			Size = sizeof(short) * 3;
			return;
		case ShaderDataType::Short4:
		case ShaderDataType::UShort4:
			Size = sizeof(short) * 4;
			return;
		case ShaderDataType::Int:
		case ShaderDataType::UInt:
			Size = sizeof(int) * 1;
			return;
		case ShaderDataType::Int2:
		case ShaderDataType::UInt2:
			Size = sizeof(int) * 2;
			return;
		case ShaderDataType::Int3:
		case ShaderDataType::UInt3:
			Size = sizeof(int) * 3;
			return;
		case ShaderDataType::Int4:
		case ShaderDataType::UInt4:
			Size = sizeof(int) * 4;
			return;
		case ShaderDataType::Float:
			Size = sizeof(float) * 1;
			return;
		case ShaderDataType::Float2:
			Size = sizeof(float) * 2;
			return;
		case ShaderDataType::Float3:
			Size = sizeof(float) * 3;
			return;
		case ShaderDataType::Float4:
			Size = sizeof(float) * 4;
			return;
		case ShaderDataType::Double:
			Size = sizeof(double) * 1;
			return;
		case ShaderDataType::Double2:
			Size = sizeof(double) * 2;
			return;
		case ShaderDataType::Double3:
			Size = sizeof(double) * 3;
			return;
		case ShaderDataType::Double4:
			Size = sizeof(double) * 4;
			return; 
		}

		BRICKENGINE_CORE_ASSERT(false, "Unknown shader data type!");
		Size = 0;
	}

	uint32_t BufferElement::GetElementCount() const
	{
		switch (Type)
		{
		case ShaderDataType::Bool:
		case ShaderDataType::Byte:
		case ShaderDataType::UByte:
		case ShaderDataType::Short:
		case ShaderDataType::UShort:
		case ShaderDataType::Int:
		case ShaderDataType::UInt:
		case ShaderDataType::Float:
		case ShaderDataType::Double:
			return 1;
		case ShaderDataType::Bool2:
		case ShaderDataType::Byte2:
		case ShaderDataType::UByte2:
		case ShaderDataType::Short2:
		case ShaderDataType::UShort2:
		case ShaderDataType::Int2:
		case ShaderDataType::UInt2:
		case ShaderDataType::Float2:
		case ShaderDataType::Double2:
			return 2;
		case ShaderDataType::Bool3:
		case ShaderDataType::Byte3:
		case ShaderDataType::UByte3:
		case ShaderDataType::Short3:
		case ShaderDataType::UShort3:
		case ShaderDataType::Int3:
		case ShaderDataType::UInt3:
		case ShaderDataType::Float3:
		case ShaderDataType::Double3:
			return 3;
		case ShaderDataType::Bool4:
		case ShaderDataType::Byte4:
		case ShaderDataType::UByte4:
		case ShaderDataType::Short4:
		case ShaderDataType::UShort4:
		case ShaderDataType::Int4:
		case ShaderDataType::UInt4:
		case ShaderDataType::Float4:
		case ShaderDataType::Double4:
			return 4;
		}

		BRICKENGINE_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	void BufferLayout::CalculateStrideAndOffset()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

}
