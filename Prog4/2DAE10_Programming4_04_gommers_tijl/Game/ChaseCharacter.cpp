#include "ChaseCharacter.h"
#include "QbertCharacter.h"
#include <iostream>

glm::vec2 Game::ChaseCharacterComponent::GetDirectionToTarget() const
{
    bool disc = m_TargetPtr->GetIsOnDisc() ;

    glm::vec2 targetPos = m_TargetPtr->GetWorldPosition();
    glm::vec2 currentPos = m_OwnerPTR->GetLocalPosition();
    glm::vec2 diffPos = glm::vec2{ targetPos.x - currentPos.x,  targetPos.y - currentPos.y };

    if (disc)
    {
        if (diffPos.x > 0)
            return glm::vec2{ 0.f, 1.f };
        else
            return glm::vec2{ -1.f, 0.f };
    }

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
