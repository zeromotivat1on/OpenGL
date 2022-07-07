#pragma once
#ifndef TEST_TEXTURE_2D_H
#define TEST_TEXTURE_2D_H

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "Texture.h"

#include <memory>

namespace test
{
	class TestTexture2D : public Test
	{
	private:
		glm::vec3 m_TranslationA, m_TranslationB;
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<VertexBuffer> m_vb;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Proj, m_View;
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}
#endif