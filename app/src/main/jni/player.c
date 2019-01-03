
#include <libavformat/avformat.h>
#include "com_soul_ffmpegdemo_Player.h"
#include <libyuv.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>

/*
 * Class:     com_soul_ffmpegdemo_Player
 * Method:    playVideo
 * Signature: (Ljava/lang/String;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_soul_ffmpegdemo_Player_playVideo
        (JNIEnv *env, jobject object, jstring path_str, jobject surface) {
    //字符转换成c可用
    const char *input_path = (*env)->GetStringUTFChars(env, path_str, JNI_FALSE);

    //注册所有组件
    av_register_all();
    //注册网络
    avformat_network_init();

    //解封装
    AVFormatContext *avFormatContext = avformat_alloc_context();
    avformat_open_input(&avFormatContext, input_path, NULL, NULL);

    avformat_find_stream_info(avFormatContext, NULL);

    //保存视频流索引
    int video_stram_idx = -1;
    //获取navtive 窗口信息
    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env, surface);
    ANativeWindow_Buffer *outBuffer;


    for (int i = 0; i < avFormatContext->nb_streams; i++) {
        if (avFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stram_idx = i;
            break;
        }
    }

    //解码
    AVCodecContext *avCodecContext = avFormatContext->streams[video_stram_idx]->codec;
    AVCodec *codec = avcodec_find_decoder(avCodecContext->codec_id);
    if (codec == NULL) {
        return;
    }

    AVPacket *packet = av_malloc(sizeof(AVPacket));
    avcodec_open2(avCodecContext, codec, NULL);
    int *got_picture_ptr;
    AVFrame *yun_frame = av_frame_alloc();
    AVFrame *pRGBFrame = av_frame_alloc();
    int width = avCodecContext->width;
    int height = avCodecContext->height;
    while (av_read_frame(avFormatContext, packet) >= 0) {
        //已经得到压缩数据,如果渲染的话 先解压缩
        //得到图片的原始数据
//        int *got_picture_ptr
//        const AVPacket *avPacket =

        avcodec_decode_video2(avCodecContext, yun_frame, &got_picture_ptr, packet);

        ANativeWindow_setBuffersGeometry(nativeWindow, width, height, WINDOW_FORMAT_RGBA_8888);
        ANativeWindow_lock(nativeWindow, &outBuffer, NULL);
        //往画布写rgb数据 共享内存
        avpicture_fill(pRGBFrame, outBuffer, AV_PIX_FMT_RGBA, width, height);

        if (got_picture_ptr) {
            //渲染到屏幕中
            //图像采样格式的转换
            // 5、将YUV420P->RGBA_8888
            I420ToARGB(yun_frame->data[0], yun_frame->linesize[0],// Y
                       yun_frame->data[2], yun_frame->linesize[2],// V
                       yun_frame->data[1], yun_frame->linesize[1],// U
                       pRGBFrame->data[0], pRGBFrame->linesize[0],
                       width, height);

        }
        ANativeWindow_unlockAndPost(nativeWindow);

    }


    //释放资源
    (*env)->ReleaseStringUTFChars(env, path_str, input_path);

}

