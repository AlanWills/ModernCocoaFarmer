#pragma once

#include "Objects/Script.h"


namespace MCF
{
  namespace Media
  {
    class VideoPlayer : public CelesteEngine::Script
    {
      DECLARE_SCRIPT(VideoPlayer)

      protected:
        void onInitialize() override;
        void onUpdate(float elapsedGameTime) override;

      private:
        using Inherited = CelesteEngine::Script;
    };
  }
}