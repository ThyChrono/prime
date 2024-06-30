
#include "pch.h"
#include "opengl_renderer2DAPI.h"
#include "prime/renderer/vertex.h"
#include "prime/renderer/shaders.h"

#include <glad/glad.h>

namespace prime::renderer
{
	struct SpriteVertex
	{
		maths::vec3 position = maths::vec3(0.0f);
		maths::vec4 color = maths::vec4(1.0f);
	};

	struct Data
	{
		// sprite
		u32 s_vertexarray = 0, s_vertexbuffer = 0, s_indexbuffer = 0;
		u32 s_index_count = 0;
		u32 s_program = 0, s_vertexshader = 0, s_fragmentshader = 0;
		maths::vec4 s_vertices[4]{};
		SpriteVertex* s_vertexbuffer_base = nullptr;
		SpriteVertex* s_vertexbuffer_ptr = nullptr;
	};

	static Data s_data;

	static b8 s_cleaned = false;

	static GLuint createShader(const char* source, GLenum type)
	{
		int status = GL_FALSE;
		char errorLog[512];

		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			glGetShaderInfoLog(shader, sizeof(errorLog), NULL, errorLog);
			if (type == GL_VERTEX_SHADER)
			{
				PERROR("Vertex shader compilation error: {}", errorLog);
			}
			else if (type == GL_FRAGMENT_SHADER)
			{
				PERROR("Fragment shader compilation error: {}", errorLog);
			}
			PASSERT(false);
		}
		return shader;
	}

	static GLuint createProgram(GLuint vertex_shader, GLuint fragment_shader)
	{
		int status = GL_FALSE;
		char errorLog[512];

		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glValidateProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status != GL_TRUE)
		{
			glGetProgramInfoLog(program, sizeof(errorLog), NULL, errorLog);
			PERROR("Shader link error: {}", errorLog);

			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);
			glDeleteProgram(program);
			program = -1;
			PASSERT(false);
		}
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	static void start_batch()
	{
		s_data.s_index_count = 0;
		s_data.s_vertexbuffer_ptr = s_data.s_vertexbuffer_base;
	}

	static GLenum VertexTypeToOpenGLType(VertexType type)
	{
		switch (type)
		{
		case vertexType_position: 
		case vertexType_color: 
			return GL_FLOAT; 
			break;
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
		s_layout.addVertex(Vertex(vertexType_color, "a_color"));
		s_layout.process();

		s_data.s_vertices[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_data.s_vertices[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_data.s_vertices[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_data.s_vertices[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		glGenVertexArrays(1, &s_data.s_vertexarray);
		glBindVertexArray(s_data.s_vertexarray);

		glGenBuffers(1, &s_data.s_vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, s_data.s_vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, (max_sprites * 4) * sizeof(SpriteVertex), nullptr, GL_DYNAMIC_DRAW);
		SunmitLayout(s_layout);

		s_data.s_vertexbuffer_base = new SpriteVertex[max_sprites * 4];
		u32* s_indices = new u32[max_sprites * 6];

		u32 offset = 0;
		for (u32 i = 0; i < max_sprites * 6; i += 6)
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

		s_data.s_vertexshader = createShader(s_sprite_vertexshader, GL_VERTEX_SHADER);
		s_data.s_fragmentshader = createShader(s_sprite_fragmentshader, GL_FRAGMENT_SHADER);
		s_data.s_program = createProgram(s_data.s_vertexshader, s_data.s_fragmentshader);
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
			delete[] s_data.s_vertexbuffer_base;
			glDeleteVertexArrays(1, &s_data.s_vertexarray);
			glDeleteBuffers(1, &s_data.s_vertexbuffer);
			glDeleteBuffers(1, &s_data.s_indexbuffer);
			glDeleteProgram(s_data.s_program);

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
			u32 data_size = (u32)((uint8_t*)s_data.s_vertexbuffer_ptr - (uint8_t*)s_data.s_vertexbuffer_base);
			glBindBuffer(GL_ARRAY_BUFFER, s_data.s_vertexbuffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, s_data.s_vertexbuffer_base);

			glUseProgram(s_data.s_program);
			glBindVertexArray(s_data.s_vertexarray);
			glDrawElements(GL_TRIANGLES, s_data.s_index_count, GL_UNSIGNED_INT, nullptr);
		}
	}

	void OpenGLRenderer2DAPI::drawSprite(const maths::vec3& pos, const maths::vec2& scale, f32 rotation, const maths::vec4& color)
	{
		maths::mat4 transform = maths::getTransform(pos, scale, rotation);

		for (size_t i = 0; i < 4; i++)
		{
			s_data.s_vertexbuffer_ptr->position = transform * s_data.s_vertices[i];
			s_data.s_vertexbuffer_ptr->color = color;
			s_data.s_vertexbuffer_ptr++;
		}
		s_data.s_index_count += 6;
	}
}