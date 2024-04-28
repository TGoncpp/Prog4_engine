#include "ServiceLocator.h"
#include <iostream>

void TG::Locator::initialize()
{
    int result = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048 );
    if (result < 0)
    {
        std::cout << "audio init failed\n";
        return;
    }
	m_Service = std::make_unique<NullAudio>();
}

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
