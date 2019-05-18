#include "stdafx.h"

#include "Media/VideoPlayer.h"
#include "Objects/GameObject.h"

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavfilter/avfilter.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
}

//#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
//#include <libswscale/swscale.h>


namespace MCF
{
  namespace Media
  {
    REGISTER_SCRIPT(VideoPlayer, 1)

    //------------------------------------------------------------------------------------------------
    VideoPlayer::VideoPlayer()
    {
    }

    //------------------------------------------------------------------------------------------------
    VideoPlayer::~VideoPlayer()
    {
    }

    //------------------------------------------------------------------------------------------------
    void VideoPlayer::onInitialize()
    {
      Inherited::onInitialize();

      AVFormatContext* pFormatCtx = NULL;

      // Open video file
      if (avformat_open_input(&pFormatCtx, "C:\\Repos\\ModernCocoaFarmer\\ModernCocoaFarmer\\Resources\\Videos\\IntroMovie.mp4", nullptr, nullptr) != 0)
        return; // Couldn't open file

      // Retrieve stream information
      if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
        return; // Couldn't find stream information
    }

    //------------------------------------------------------------------------------------------------
    void VideoPlayer::onUpdate(float elapsedGameTime)
    {
      Inherited::onUpdate(elapsedGameTime);
    }
  } 
}