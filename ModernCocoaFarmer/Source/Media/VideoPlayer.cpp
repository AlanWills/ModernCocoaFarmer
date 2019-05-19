#include "stdafx.h"

#include "Media/VideoPlayer.h"
#include "Objects/GameObject.h"
#include "Media/ffplay.h"

//#define INBUF_SIZE 4096


namespace MCF
{
  namespace Media
  {
    REGISTER_SCRIPT(VideoPlayer, 1)

    //------------------------------------------------------------------------------------------------
    VideoPlayer::VideoPlayer() :
      m_videoPath(),
      m_playImmediately(true),
      m_autoExit(true)
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

      if (m_playImmediately)
      {
        play();
      }
    }

    //------------------------------------------------------------------------------------------------
    void VideoPlayer::play() const
    {
      CelesteEngine::Media::ffplay::playVideo(m_videoPath.as_string(), m_autoExit);
    }

//#define ALPHA_MIX(A,BACK,FORE) (((255-(A)) * (BACK) + (A) * (FORE)) / 255)
//
//    //------------------------------------------------------------------------------------------------
//    void VideoPlayer::ppm_save(unsigned char* buf, int wrap, int xsize, int ysize, char* filename)
//    {
//      if (!m_done)
//      {
//        const Handle<Rendering::SpriteRenderer> spriteRenderer = getGameObject()->findComponent<Rendering::SpriteRenderer>();
//
//        m_texture->setImageFormat(GL_RGBA);
//        m_texture->setInternalFormat(GL_RGBA);
//
//        /*for (int i = 0;; ++i)
//        {
//          auto c = buf[i];
//        }*/
//
//        m_texture->generate(100, 100, buf);
//        spriteRenderer->setTexture(m_texture.handle());
//
//        m_done = true;
//      }
//
//      /*FILE* f;
//      int i;
//      fopen_s(&f, filename, "w");
//      fprintf(f, "P6\n%d %d\n%d\n", xsize, ysize, 255);
//      for (i = 0; i < ysize; i++)
//      {
//        for (int x = 0; x < xsize; ++x)
//        {
//          fwrite(buf + i * wrap + x, 3, 1, f);
//        }
//      }
//      fclose(f);*/
//
//      int x, y, alpha;
//      uint32_t v;
//      int back[3] = { 0, 255, 0 };  /* green background */
//      FILE* f;
//
//      fopen_s(&f, filename, "w");
//      if (!f) {
//        perror(filename);
//        return;
//      }
//
//      fprintf(f, "P6\n"
//        "%d %d\n"
//        "%d\n",
//        xsize, ysize, 255);
//      for (y = 0; y < ysize; y++) {
//        for (x = 0; x < xsize; x++) {
//          /*v = 0xffffff;
//          alpha = 0xffffff;
//          putc(ALPHA_MIX(alpha, back[0], (v >> 16) & 0xff), f);
//          putc(ALPHA_MIX(alpha, back[1], (v >> 8) & 0xff), f);
//          putc(ALPHA_MIX(alpha, back[2], (v >> 0) & 0xff), f);*/
//          auto orig = buf[y * xsize + x];
//          auto origInt = static_cast<int>(orig);
//          int v1 = (static_cast<int>(buf[y * xsize + x]) >> 16) & 0xff;
//          int v2 = (static_cast<int>(buf[y * xsize + x]) >> 8) & 0xff;
//          int v3 = (static_cast<int>(buf[y * xsize + x]) >> 0) & 0xff;
//          putc(v1, f);
//          putc(v2, f);
//          putc(v3, f);
//        }
//      }
//      fclose(f);
//    }

    ////------------------------------------------------------------------------------------------------
    //void VideoPlayer::decode(AVCodecContext * dec_ctx, AVFrame * frame, AVPacket * pkt, const char* filename)
    //{
    //  char buf[1024];
    //  int ret;
    //  ret = avcodec_send_packet(dec_ctx, pkt);
    //  if (ret < 0) {
    //    fprintf(stderr, "Error sending a packet for decoding\n");
    //    exit(1);
    //  }
    //  while (ret >= 0) {
    //    ret = avcodec_receive_frame(dec_ctx, frame);
    //    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
    //      return;
    //    else if (ret < 0) {
    //      fprintf(stderr, "Error during decoding\n");
    //      exit(1);
    //    }
    //    printf("saving frame %3d\n", dec_ctx->frame_number);
    //    fflush(stdout);
    //    /* the picture is allocated by the decoder. no need to
    //       free it */
    //    snprintf(buf, sizeof(buf), "%s-%d", filename, dec_ctx->frame_number);
    //    ppm_save(frame->data[0], frame->linesize[0],
    //      frame->width, frame->height, buf);
    //  }
    //}

    ////------------------------------------------------------------------------------------------------
    //void VideoPlayer::onSetGameObject(const Handle<CelesteEngine::GameObject>& gameObject)
    //{
    //  Inherited::onSetGameObject(gameObject);

    //  const char* filePath = "C:\\Repos\\ModernCocoaFarmer\\ModernCocoaFarmer\\Resources\\Videos\\IntroMovie.mpeg";
    //  const char* outputFilePath = "C:\\Repos\\ModernCocoaFarmer\\ModernCocoaFarmer\\Resources\\Videos\\Output.ppm";

    //  const AVCodec* codec;
    //  AVCodecParserContext* parser;
    //  AVCodecContext* c = NULL;
    //  FILE* f;
    //  AVFrame* frame;
    //  uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    //  uint8_t* data;
    //  size_t   data_size;
    //  int ret;
    //  AVPacket* pkt;
    //  
    //  pkt = av_packet_alloc();
    //  if (!pkt)
    //    exit(1);
    //  /* set end of buffer to 0 (this ensures that no overreading happens for damaged MPEG streams) */
    //  memset(inbuf + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    //  /* find the MPEG-1 video decoder */
    //  codec = avcodec_find_decoder(AV_CODEC_ID_MPEG1VIDEO);
    //  if (!codec) {
    //    fprintf(stderr, "Codec not found\n");
    //    exit(1);
    //  }
    //  parser = av_parser_init(codec->id);
    //  if (!parser) {
    //    fprintf(stderr, "parser not found\n");
    //    exit(1);
    //  }
    //  c = avcodec_alloc_context3(codec);
    //  if (!c) {
    //    fprintf(stderr, "Could not allocate video codec context\n");
    //    exit(1);
    //  }
    //  /* For some codecs, such as msmpeg4 and mpeg4, width and height
    //     MUST be initialized there because this information is not
    //     available in the bitstream. */
    //     /* open it */
    //  if (avcodec_open2(c, codec, nullptr) < 0) {
    //    fprintf(stderr, "Could not open codec\n");
    //    exit(1);
    //  }
    //  fopen_s(&f, filePath, "rb");
    //  if (!f) {
    //    fprintf(stderr, "Could not open %s\n", filePath);
    //    exit(1);
    //  }
    //  frame = av_frame_alloc();
    //  if (!frame) {
    //    fprintf(stderr, "Could not allocate video frame\n");
    //    exit(1);
    //  }
    //  while (!feof(f)) {
    //    /* read raw data from the input file */
    //    data_size = fread(inbuf, 1, INBUF_SIZE, f);
    //    if (!data_size)
    //      break;
    //    /* use the parser to split the data into frames */
    //    data = inbuf;
    //    while (data_size > 0) {
    //      ret = av_parser_parse2(parser, c, &pkt->data, &pkt->size,
    //        data, data_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
    //      if (ret < 0) {
    //        fprintf(stderr, "Error while parsing\n");
    //        exit(1);
    //      }
    //      data += ret;
    //      data_size -= ret;
    //      if (pkt->size)
    //        decode(c, frame, pkt, outputFilePath);
    //    }
    //  }
    //  /* flush the decoder */
    //  decode(c, frame, nullptr, outputFilePath);
    //  fclose(f);
    //  av_parser_close(parser);
    //  avcodec_free_context(&c);
    //  av_frame_free(&frame);
    //  av_packet_free(&pkt);
    //}

    /*
     * Video decoding example
     */
    
    //static void pgm_save(unsigned char *buf, int wrap, int xsize, int ysize,
    //                     const char *filename)
    //{
    //  for (int y = 0; y < ysize; ++y)
    //  {
    //    for (int x = 0; x < xsize; ++x)
    //    {
    //      buf[y * wrap + x] -= 16;
    //      char c = buf[y * wrap + x];
    //      int i = static_cast<int>(c);
    //      char otherc = '\x1';
    //      int otheri = static_cast<int>(otherc);
    //      ASSERT(true);
    //    }
    //  }
    //    FILE *f;
    //    int i;
    //
    //    fopen_s(&f, filename,"w");
    //    fprintf(f,"P5\n%d %d\n%d\n",xsize,ysize,255);
    //    for (i = 0; i < ysize; i++)
    //    {
    //      fwrite(buf + i * wrap, 1, xsize, f);
    //      //fwrite("\n", 1, 1, f);
    //    }
    //    fclose(f);
    //}
    //
    //static int decode_write_frame(const char *outfilename, AVCodecContext *avctx,
    //                              AVFrame *frame, int *frame_count, AVPacket *pkt, int last)
    //{
    //    int len, got_frame;
    //    char buf[1024];
    //
    //    len = avcodec_decode_video2(avctx, frame, &got_frame, pkt);
    //    if (len < 0) {
    //        fprintf(stderr, "Error while decoding frame %d\n", *frame_count);
    //        return len;
    //    }
    //    if (got_frame) {
    //        printf("Saving %sframe %3d\n", last ? "last " : "", *frame_count);
    //        fflush(stdout);
    //
    //        /* the picture is allocated by the decoder, no need to free it */
    //        Path p(outfilename);
    //        Directory d(p.getParentDirectory());
    //        Path newP(d.getDirectoryPath(), std::to_string(*frame_count) + ".pgm");

    //        //snprintf(buf, sizeof(buf), outfilename, *frame_count);
    //        pgm_save(frame->data[0], frame->linesize[0],
    //                 avctx->width, avctx->height, newP.c_str());
    //        (*frame_count)++;
    //    }
    //    if (pkt->data) {
    //        pkt->size -= len;
    //        pkt->data += len;
    //    }
    //    return 0;
    //}
    
    //void VideoPlayer::onSetGameObject(const Handle<CelesteEngine::GameObject>& gameObject)
    //{
    //  File file(Path("C:\\Users\\alawi\\Downloads\\ffmpeg-20190517-96c79d4-win64-static\\bin\\output_0001.pgm"));
    //  std::string output;
    //  file.read(output);

    //  //return;

    //  const char* filename = "C:\\Repos\\ModernCocoaFarmer\\ModernCocoaFarmer\\Resources\\Videos\\IntroMovie.mpeg";
    //  const char* outfilename = "C:\\Repos\\ModernCocoaFarmer\\ModernCocoaFarmer\\Resources\\Videos\\Output.ppm";
    //  AVCodec* codec;
    //  AVCodecContext* c = NULL;
    //  int frame_count;
    //  FILE* f;
    //  AVFrame* frame;
    //  uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    //  AVPacket avpkt;

    //  av_init_packet(&avpkt);

    //  /* set end of buffer to 0 (this ensures that no overreading happens for damaged mpeg streams) */
    //  memset(inbuf + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    //  printf("Decode video file %s to %s\n", filename, outfilename);

    //  /* find the mpeg1 video decoder */
    //  codec = avcodec_find_decoder(AV_CODEC_ID_MPEG1VIDEO);
    //  if (!codec) {
    //    fprintf(stderr, "Codec not found\n");
    //    exit(1);
    //  }

    //  c = avcodec_alloc_context3(codec);
    //  if (!c) {
    //    fprintf(stderr, "Could not allocate video codec context\n");
    //    exit(1);
    //  }

    //  if (codec->capabilities & AV_CODEC_CAP_TRUNCATED)
    //    c->flags |= AV_CODEC_FLAG_TRUNCATED; /* we do not send complete frames */

    ///* For some codecs, such as msmpeg4 and mpeg4, width and height
    //   MUST be initialized there because this information is not
    //   available in the bitstream. */

    //   /* open it */
    //  if (avcodec_open2(c, codec, NULL) < 0) {
    //    fprintf(stderr, "Could not open codec\n");
    //    exit(1);
    //  }

    //  fopen_s(&f, filename, "rb");
    //  if (!f) {
    //    fprintf(stderr, "Could not open %s\n", filename);
    //    exit(1);
    //  }

    //  frame = av_frame_alloc();
    //  if (!frame) {
    //    fprintf(stderr, "Could not allocate video frame\n");
    //    exit(1);
    //  }

    //  frame_count = 0;
    //  for (;;) {
    //    avpkt.size = fread(inbuf, 1, INBUF_SIZE, f);
    //    if (avpkt.size == 0)
    //      break;

    //    /* NOTE1: some codecs are stream based (mpegvideo, mpegaudio)
    //       and this is the only method to use them because you cannot
    //       know the compressed data size before analysing it.

    //       BUT some other codecs (msmpeg4, mpeg4) are inherently frame
    //       based, so you must call them with all the data for one
    //       frame exactly. You must also initialize 'width' and
    //       'height' before initializing them. */

    //       /* NOTE2: some codecs allow the raw parameters (frame size,
    //          sample rate) to be changed at any frame. We handle this, so
    //          you should also take care of it */

    //          /* here, we use a stream based decoder (mpeg1video), so we
    //             feed decoder and see if it could decode a frame */
    //    avpkt.data = inbuf;
    //    while (avpkt.size > 0)
    //      if (decode_write_frame(outfilename, c, frame, &frame_count, &avpkt, 0) < 0)
    //        exit(1);
    //  }

    //  /* some codecs, such as MPEG, transmit the I and P frame with a
    //     latency of one frame. You must do the following to have a
    //     chance to get the last frame of the video */
    //  avpkt.data = NULL;
    //  avpkt.size = 0;
    //  decode_write_frame(outfilename, c, frame, &frame_count, &avpkt, 1);

    //  fclose(f);

    //  avcodec_close(c);
    //  av_free(c);
    //  av_frame_free(&frame);
    //  printf("\n");
    //}
  } 
}