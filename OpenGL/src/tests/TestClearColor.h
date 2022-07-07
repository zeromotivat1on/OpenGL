#pragma once
#ifndef TEST_CLEAR_COLOR_H
#define TEST_CLEAR_COLOR_H

#include "Test.h"

namespace test
{
	class TestClearColor : public Test
	{
	private:
		float m_ClearColor[4];
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}
#endif