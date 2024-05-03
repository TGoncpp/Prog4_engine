#pragma once
#include <glm/glm.hpp>

namespace TG
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);
		static bool IsEqualVector(const glm::vec2& first, const glm::vec2& other , float margin = 0.1f);
		static void SetDirection(glm::vec2& normalisedDirection, const glm::vec2& newDirection);
	private:
		glm::vec3 m_position;
	};
}
