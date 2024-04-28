#include "ServiceLocator.h"
#include <iostream>

void TG::Locator::provide(std::unique_ptr<Audio> service)
{
    if (!service)
    {
        m_Service = std::make_unique<NullAudio>();
    }
    else
    {
        m_Service = std::move(service);
    }
}
