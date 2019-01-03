package com.soul.ffmpegdemo.widget

import android.content.Context
import android.graphics.PixelFormat
import android.util.AttributeSet
import android.view.SurfaceView

/**
 * @描述：TODO
 * @作者：祝明
 * @项目名:FfmpegDemo
 * @创建时间：2019/1/2 18:54
 */
class VideoView(context: Context?, attrs: AttributeSet?) : SurfaceView(context, attrs) {

    init {
        val surfaceHolder = holder
        // 初始化SurfaceView绘制的像素格式
        surfaceHolder.setFormat(PixelFormat.RGBA_8888)
    }
}