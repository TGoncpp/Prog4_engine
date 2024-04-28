#pragma once
#include "Audio.h"

namespace TG
{
    class Locator final
    {
    public:
        static void initialize();

        static Audio& getAudio() { return *m_Service; }

        static void provide(std::unique_ptr<Audio> service);
        

    private:
        inline static std::unique_ptr< Audio> m_Service{nullptr};
    };

        ////Should be in service class??
        //void enableAudioLogging()
        //{
        //    // Decorate the existing service.
        //    Audio* service = new LoggedAudio(Locator::getAudio());
        //
        //    // Swap it in.
        //    Locator::provide(service);
        //}
}
