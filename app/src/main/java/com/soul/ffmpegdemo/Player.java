package com.soul.ffmpegdemo;

/**
 * @描述：TODO
 * @作者：祝明
 * @项目名:FfmpegDemo
 * @创建时间：2019/1/3 15:57
 */
public class Player {

    static {
        System.loadLibrary("Player");
    }

    public native void playVideo(String str, Object surface);

}
