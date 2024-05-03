#include "Transform.h"

void TG::Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

bool TG::Transform::IsEqualVector(const glm::vec2& first, const glm::vec2& other, float margin)
{
	return (std::fabsf(first.x - other.x) <= margin && std::fabsf(first.y - other.y) <= margin);
}

void TG::Transform::SetDirection(glm::vec2& normalisedDirection, const glm::vec2& newDirection)
{
	if (normalisedDirection.x * newDirection.x < 0)
		normalisedDirection.x *= -1;

	if (normalisedDirection.y * newDirection.y < 0)
		normalisedDirection.y *= -1;
}
