#pragma once
#include "Audio.h"

namespace TG
{
    class Locator final
    {
    public:
        static Audio& getAudio() { return *m_Service; }

        static void provide(std::unique_ptr<Audio> service);
        

    private:
        inline static std::unique_ptr< Audio> m_Service{ std::make_unique<NullAudio>() };

    };

        
}
