
#include "pch.h"
#include "opengl_renderer2DAPI.h"
#include "prime/renderer/vertex.h"

#include <glad/glad.h>

namespace prime::renderer
{
	struct SpriteVertex
	{
		maths::vec3 position = maths::vec3(0.0f);
	};

	struct Data
	{
		// sprite
		u32 s_vertexarray = 0, s_vertexbuffer = 0, s_indexbuffer = 0;
		u32 s_index_count = 0;
		maths::vec4 s_vertices[4]{};
		SpriteVertex* s_vertexbufferBase = nullptr;
		SpriteVertex* s_vertexbufferPtr = nullptr;
	};

	static Data s_data;

	static b8 s_cleaned = false;

	static void start_batch()
	{
		s_data.s_index_count = 0;
		s_data.s_vertexbufferPtr = s_data.s_vertexbufferBase;
	}

	static GLenum VertexTypeToOpenGLType(VertexType type)
	{
		switch (type)
		{
		case vertexType_position: return GL_FLOAT; break;
		}
		return 0;
	}

	static void SunmitLayout(const VertexLayout& layout)
	{
		u32 index = 0;
		for (const Vertex& vertex : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				getVertexTypeCount(vertex.type),
				VertexTypeToOpenGLType(vertex.type),
				vertex.normalize ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)(intptr_t)vertex.offset);

			index++;
		}
	}

	static void initSpriteRendering(u32 max_sprites)
	{
		VertexLayout s_layout;
		s_layout.addVertex(Vertex(vertexType_position, "a_position"));

		s_data.s_vertices[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_data.s_vertices[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_data.s_vertices[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_data.s_vertices[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		glGenVertexArrays(1, &s_data.s_vertexarray);
		glBindVertexArray(s_data.s_vertexarray);

		glGenBuffers(1, &s_data.s_vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, s_data.s_vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, max_sprites * sizeof(SpriteVertex), nullptr, GL_DYNAMIC_DRAW);
		SunmitLayout(s_layout);

		s_data.s_vertexbufferBase = new SpriteVertex[max_sprites * 4];
		uint32_t* s_indices = new uint32_t[max_sprites * 6];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < max_sprites * 6; i += 6)
		{
			s_indices[i + 0] = offset + 0;
			s_indices[i + 1] = offset + 1;
			s_indices[i + 2] = offset + 2;

			s_indices[i + 3] = offset + 2;
			s_indices[i + 4] = offset + 3;
			s_indices[i + 5] = offset + 0;

			offset += 4;
		}

		glGenBuffers(1, &s_data.s_indexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data.s_indexbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_sprites * 6, s_indices, GL_STATIC_DRAW);
		delete[] s_indices;
	}

	void OpenGLRenderer2DAPI::init(u32 max_sprites)
	{
		initSpriteRendering(max_sprites);
	}

	void OpenGLRenderer2DAPI::shutdown()
	{
		if (s_cleaned == false)
		{
			// sprite
			delete[] s_data.s_vertexbufferBase;
			glDeleteVertexArrays(1, &s_data.s_vertexarray);
			glDeleteBuffers(1, &s_data.s_vertexbuffer);
			glDeleteBuffers(1, &s_data.s_indexbuffer);

			s_cleaned = true;
		}
	}

	void OpenGLRenderer2DAPI::begin()
	{
		start_batch();
	}
	
	void OpenGLRenderer2DAPI::end()
	{
		if (s_data.s_index_count)
		{
			uint32_t data_size = (uint32_t)((uint8_t*)s_data.s_vertexbufferPtr - (uint8_t*)s_data.s_vertexbufferBase);
			glBindBuffer(GL_ARRAY_BUFFER, s_data.s_vertexbuffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, s_data.s_vertexbufferBase);

			glBindVertexArray(s_data.s_vertexarray);
			glDrawElements(GL_TRIANGLES, s_data.s_index_count, GL_UNSIGNED_INT, nullptr);
		}
	}

	void OpenGLRenderer2DAPI::drawSprite(const maths::vec3& pos)
	{
		maths::mat4 transform = maths::getTransform(pos);

		for (size_t i = 0; i < 4; i++)
		{
			s_data.s_vertexbufferPtr->position = transform * s_data.s_vertices[i];
			s_data.s_vertexbufferPtr++;
		}
		s_data.s_index_count += 6;
	}
}