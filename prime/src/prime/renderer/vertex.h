#pragma once

#include "prime/core/defines.h"

#include <vector>

namespace prime::renderer
{
	enum VertexType
	{
		vertexType_position,
		vertexType_color
	};

	static u32 getVertexTypeSize(const VertexType type)
	{
		switch (type)
		{
		case vertexType_position: return 12; break;
		case vertexType_color: return 16; break;
		}
		return 0;
	}

	static u32 getVertexTypeCount(const VertexType type)
	{
		switch (type)
		{
		case vertexType_position: return 3; break;
		case vertexType_color: return 4; break;
		}
		return 0;
	}

	class Vertex
	{
	public:
		str name = "";
		VertexType type = vertexType_position;
		u32 size = 0;
		i64 offset = 0;
		bool normalize = false;

	public:
		Vertex() = default;

		Vertex(const VertexType type, const str& name)
			: name(name), type(type)
		{
			size = getVertexTypeSize(type);
			offset = 0;

			if (type == vertexType_position) { normalize = false; }
			if (type == vertexType_color) { normalize = false; }
		}
	};

	class VertexLayout
	{
	private:
		std::vector<Vertex> m_vertices;
		u32 m_stride = 0;

	public:
		VertexLayout() {}

		u32 getStride() const { return m_stride; }
		const std::vector<Vertex>& getVertices() const { return m_vertices; }

		void addVertex(const Vertex& vertex) { m_vertices.push_back(vertex); }

		void process()
		{
			i64 offset = 0;
			m_stride = 0;
			for (Vertex& vertex : m_vertices)
			{
				vertex.offset = offset;
				offset += vertex.size;
				m_stride += vertex.size;
			}
		}

		std::vector<Vertex>::iterator begin() { return m_vertices.begin(); }
		std::vector<Vertex>::iterator end() { return m_vertices.end(); }
		std::vector<Vertex>::const_iterator begin() const { return m_vertices.begin(); }
		std::vector<Vertex>::const_iterator end() const { return m_vertices.end(); }
	};
}