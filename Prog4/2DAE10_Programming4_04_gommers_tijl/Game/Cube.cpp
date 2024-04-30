#include "Cube.h"
#include "SpriteComponent.h"

Game::Cube::Cube(const glm::vec2& position, const CubeState& state, const std::string& name)
	:TG::GameObject(name)
	, m_State{state}
{
	AddComponent<TG::RenderComponent>(this, "Textures/Qbert Cubes.png");
	AddComponent<TG::SpriteComponent>(this, 6, 3, true);
	SetLocalPosition(position);	
}
