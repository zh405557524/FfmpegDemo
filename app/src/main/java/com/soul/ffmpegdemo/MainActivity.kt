package com.soul.ffmpegdemo

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import android.os.Environment
import android.support.v4.app.ActivityCompat
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.View
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File

class MainActivity : AppCompatActivity(), View.OnClickListener {

    private val REQUEST_EXTERNAL_STORAGE = 1

    private val PERMISSIONS_STORAGE = arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE)

    lateinit var player: Player

    lateinit var file:File

    private val VIDEO_INPUT = "input.mp4"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        play_video.setOnClickListener(this)
        initView()
        initData()
        initEvent()
    }


    private fun initView() {


    }


    private fun initData() {
        checkPermission()
        checkVideoFile()
        player = Player()

    }

    private fun initEvent() {

    }


    private fun checkPermission() {
        val permission = ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
        if (permission != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, PERMISSIONS_STORAGE, REQUEST_EXTERNAL_STORAGE)
            Log.d("Tag", "checkPermission: 尚未授权")
        } else {
            Log.d("Tag", "checkPermission: 已经授权")
        }
    }


    private fun checkVideoFile(): Boolean {
         file = File(Environment.getExternalStorageDirectory(), VIDEO_INPUT)
        val exists = file.exists()
        if (exists) {
            Toast.makeText(this, file.getAbsolutePath() + "文件不存在", Toast.LENGTH_SHORT).show()
        }
        return exists
    }

    override fun onClick(view: View?) {

        when (view?.id) {

            R.id.play_video -> {//视频播放
                if (checkVideoFile()) {
                    player.playVideo(file.absolutePath,videoView)
                }

            }

            R.id.play_voice -> {//音频播放


            }

        }

    }
}
