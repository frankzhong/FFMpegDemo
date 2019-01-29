#include <jni.h>
#include <string>
#include <android/log.h>
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "testff", __VA_ARGS__)
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

extern "C" JNIEXPORT jstring JNICALL
Java_frank_com_ffmpegdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    hello += avcodec_configuration();
    //初始化解封装
    av_register_all();
    //初始化网路
    avformat_network_init();
    //打开文件
    AVFormatContext *ic = NULL;
//    char path[] = "/sdcard/fftest.mp4";
    char path[] = "/sdcard/Wildlife.flv";
    int re = avformat_open_input(&ic, path, 0, 0);
    if(re != 0)
    {
        LOGW("avformat_open_input failed!:%s", av_err2str(re));
        return env->NewStringUTF(hello.c_str());
    }
    //获取流信息
    re = avformat_find_stream_info(ic, 0);
    if(re != 0){
        LOGW("avformat_find_stream_info failed!");
    }
    LOGW("avformat_open_input %s success!", path);

    LOGW("duration = %lld  nb_streams = %d", ic->duration, ic->nb_streams);
    //关闭上下文
    avformat_close_input(&ic);
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_frank_com_ffmpegdemo_MainActivity_open(JNIEnv *env, jobject instance, jstring url_,
                                              jobject handle) {
    const char *url = env->GetStringUTFChars(url_, 0);
    LOGW("---------------------------");
    // TODO
    FILE *fp = fopen(url, "rb");
    if(!fp)
    {
        LOGW("%s open failed!", url);
    } else
    {
        LOGW("%s open success!", url);
        fclose(fp);
    }

    env->ReleaseStringUTFChars(url_, url);
    return true;
}