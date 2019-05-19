#pragma once

#include "Objects/Script.h"
#include "FileSystem/Path.h"

//extern "C" {
//#include "libavcodec/avcodec.h"
//#include "libavdevice/avdevice.h"
//#include "libavfilter/avfilter.h"
//#include "libavformat/avformat.h"
//#include "libavutil/avutil.h"
//#include "libavutil/imgutils.h"
//#include "libswscale/swscale.h"
//#include <libavutil/opt.h>
//#include <libavcodec/avcodec.h>
//#include <libavutil/channel_layout.h>
//#include <libavutil/common.h>
//#include <libavutil/imgutils.h>
//#include <libavutil/mathematics.h>
//#include <libavutil/samplefmt.h>
//}


namespace MCF
{
  namespace Media
  {
    class VideoPlayer : public CelesteEngine::Script
    {
      DECLARE_SCRIPT(VideoPlayer)

      public:
        void play() const;

      protected:
        void onInitialize() override;

      private:
        using Inherited = CelesteEngine::Script;

        Path m_videoPath;
        bool m_playImmediately;
        bool m_autoExit;
    };
  }
}