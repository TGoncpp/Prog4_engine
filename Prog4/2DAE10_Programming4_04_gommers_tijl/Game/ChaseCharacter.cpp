#include "ChaseCharacter.h"
#include "QbertCharacter.h"

glm::vec2 Game::ChaseCharacterComponent::GetDirectionToTarget() const
{
    glm::vec2 targetPos = m_TargetPtr->GetLocalPosition();
    glm::vec2 currentPos = m_OwnerPTR->GetLocalPosition();
    glm::vec2 diffPos = targetPos - currentPos;
    
    if (diffPos.y < 0 )
    {
        if (diffPos.x < 0)
            return glm::vec2{ -1.f,0.f };
        else
            return glm::vec2{ 0.f, 1.f };
    }
    else
    {
        if (diffPos.x < 0)
            return glm::vec2{ 0.f, -1.f };
        else
            return glm::vec2{ 1.f,0.f };
    }
    

}
