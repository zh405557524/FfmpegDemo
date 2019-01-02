# FfmpegDemo 
## 一 编译ffmpeg (Ubuntu 18.10 x64系统)
### 1 下载
    wget https://ffmpeg.org/releases/ffmpeg-4.1.tar.bz2
### 2 解压
    .tar.gz     格式解压为          tar   -zxvf   xx.tar.gz
    .tar.bz2    格式解压为          tar   -jxvf   xx.tar.bz2
    
### 3 编译
#### 1 编译armeabi-v7a的脚本
    #!/bin/bash
     #shell脚本第一行必须是指定shell脚本解释器，这里使用的是bash解释器
     
     #一系列命令的集合 cd xx;dir
     
     #ndk r17
     
     make clean
     
     #指令的集合
     
     #执行ffmpeg 配置脚本
     #--prefix 安装、输出目录 so、a的输出目录 javac -o
     #--enable-cross-compile 开启交叉编译器
     #--cross-prefix 编译工具前缀 指定ndk中的工具给这个参数
     #--disable-shared 关闭动态库
     #--disable-programs 关闭程序的编译 ffmpeg ffplay
     #--extra-cflags 给编译的参数
     
     export NDK=/usr/ndk/android-ndk-r17
     export SYSROOT=$NDK/platforms/android-21/arch-arm/
     export TOOLCHAIN=$NDK/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64
     export CPU=arm
     export PREFIX=$(pwd)/android/$CPU
     
     #给编译器的变量
     #定义变量 值从FFmpeg_Player\app\.externalNativeBuild\cmake\release\armeabi-v7a\build.ninja 复制的
     FLAG="-isystem $NDK/sysroot/usr/include/arm-linux-androideabi -D__ANDROID_API__=21 -g -DANDROID -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb -Wa,--noexecstack -Wformat -Werror=format-security  -Os -DNDEBUG  -fPIC"
     
     INCLUDES="-isystem $NDK/sources/cxx-stl/gnu-libstdc++/4.9/include -isystem $NDK/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/include -isystem $NDK/sources/cxx-stl/gnu-libstdc++/4.9/include/backward"
     
     ./configure \
     --target-os=android \
     --prefix=$PREFIX \
     --arch=arm \
     --enable-shared \
     --disable-static \
     --disable-yasm \
     --enable-gpl \
     --disable-ffmpeg \
     --disable-ffplay \
     --disable-ffprobe \
     --disable-doc \
     --disable-symver \
     --cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
     --enable-cross-compile \
     --sysroot=$SYSROOT \
     --extra-cflags="-isysroot $NDK/sysroot $FLAG $INCLUDES" \
     --extra-ldflags="$ADDI_LDFLAGS" \
     $ADDITIONAL_CONFIGURE_FLAG
     make clean
     make
     make install
     
#### 2 编译arm64-v8a的脚本 
    #!/bin/bash
    #shell脚本第一行必须是指定shell脚本解释器，这里使用的是bash解释器
    
    #一系列命令的集合 cd xx;dir
    
    #ndk r17
    
    make clean
    
    #指令的集合
    
    #执行ffmpeg 配置脚本
    #--prefix 安装、输出目录 so、a的输出目录 javac -o
    #--enable-cross-compile 开启交叉编译器
    #--cross-prefix 编译工具前缀 指定ndk中的工具给这个参数
    #--disable-shared 关闭动态库
    #--disable-programs 关闭程序的编译 ffmpeg ffplay
    #--extra-cflags 给编译的参数
    
    export NDK=/usr/ndk/android-ndk-r17
    export SYSROOT=$NDK/platforms/android-21/arch-arm64/
    export TOOLCHAIN=$NDK/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64
    export CPU=arm64
    export PREFIX=$(pwd)/android/$CPU
    
    #给编译器的变量
    #定义变量 值从FFmpeg_Player\app\.externalNativeBuild\cmake\release\arm64-v8a\build.ninja 复制的                                                                                      
    FLAG="-isystem $NDK/sysroot/usr/include/aarch64-linux-android -D__ANDROID_API__=21 -g -DANDROID -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -Wa,--noexecstack -Wformat -Werror=format-security  -O2 -DNDEBUG  -fPIC"
    
    INCLUDES="-isystem $NDK/sources/cxx-stl/gnu-libstdc++/4.9/include -isystem $NDK/sources/cxx-stl/gnu-libstdc++/4.9/libs/arm64-v8a/include -isystem $NDK/sources/cxx-stl/gnu-libstdc++/4.9/include/backward"
    
    ./configure \
    --target-os=android \
    --prefix=$PREFIX \
    --arch=aarch64 \
    --enable-shared \
    --disable-static \
    --disable-yasm \
    --enable-gpl \
    --disable-ffmpeg \
    --disable-ffplay \
    --disable-ffprobe \
    --disable-doc \
    --disable-symver \
    --cross-prefix=$TOOLCHAIN/bin/aarch64-linux-android- \
    --enable-cross-compile \
    --sysroot=$SYSROOT \
    --extra-cflags="-isysroot $NDK/sysroot $FLAG $INCLUDES" \
    --extra-ldflags="$ADDI_LDFLAGS" \
    $ADDITIONAL_CONFIGURE_FLAG
    make clean
    make
    make install 
    
#### 3 编译步骤
     1 修改文件权限 
        chmod 777 xx.sh
     2 开始编译
        sh xx.sh
        
## 二  ffmpeg 在 android studio 中的配置

### 1 CmakeLists语法

   * cmake_minimum_required(VERSION 3.4.1)
   
    用来设置编译本地native library的时候需要的Cmake最小版本.
 
   * add_library()
   
    add_library( # Sets the name of the library.
                 native-lib
    
    # Sets the library as a shared library.
    SHARED
    
    # Provides a relative path to your source file(s).
    src/main/cpp/native-lib.cpp )
    ****
    native-lib : 设置本地lib的name 
    SHARED : 表示编译生成的是动态链接库 
    src/main/cpp/native-lib.cpp : 表示编译文件的相对路径,这里可以是一个文件的路径也可以是多个文件的路径
    
   * find_library()
    
    find_library( # Sets the name of the path variable.
                  log-lib
    
                  # Specifies the name of the NDK library that
                  # you want CMake to locate.
                  log )
    这个的作用是用来让我们加一些编译本地NDK库的时候所用的到一些依赖库. 
    log-lib 是这个库的别名,方便我们以后引用 
    log 是我们调试的时候打印log的一个库
    
   * target_link_libraries() 
    
    target_link_libraries( # Specifies the target library.
                           native-lib
    
                           # Links the target library to the log library
                           # included in the NDK.
                           ${log-lib} )
                           
    这个的目的是用来关联我们本地的库跟第三方的库.这里就是把native-lib库和log库关联起来.
    
###  2 ffmpeg 在Android Studio 中 CmakeLists 的用法
    
   * 设置生成的so动态库最后输出的路径  
   
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/jniLibs/${ANDROID_ABI})
    
   * 设置头文件路径
   
    set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/jni/include)
    #设置头文件路径，在代码中include时不需要带路径了
    include_directories(${INCLUDE_DIR}/ffmpeg ${INCLUDE_DIR}/libyuv)       
             
  * 设置编译文件路径
  
  
    add_library( # Sets the name of the library.
                 player
    
                 # Sets the library as a shared library.
                 SHARED
    
                 # Provides a relative path to your source file(s).
                 src/main/jni/player.c )
                 
  * 设置导入的路径

  
    set(LIB_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs)

    add_library(avcodec SHARED IMPORTED)
    # 设置导入的路径
    set_target_properties(avcodec
                          PROPERTIES IMPORTED_LOCATION
                          ${LIB_DIR}/${ANDROID_ABI}/libavcodec.so)
    
    add_library(avdevice SHARED IMPORTED)
    set_target_properties(avdevice
                          PROPERTIES IMPORTED_LOCATION
                          ${LIB_DIR}/${ANDROID_ABI}/libavdevice.so)
    
    add_library(avfilter SHARED IMPORTED)
    set_target_properties(avfilter
                          PROPERTIES IMPORTED_LOCATION
                          ${LIB_DIR}/${ANDROID_ABI}/libavfilter.so)
    
    add_library(avformat SHARED IMPORTED)
    set_target_properties(avformat
                          PROPERTIES IMPORTED_LOCATION
                          ${LIB_DIR}/${ANDROID_ABI}/libavformat.so)
    
    add_library(avutil SHARED IMPORTED)
    set_target_properties(avutil
                          PROPERTIES IMPORTED_LOCATION
                          ${LIB_DIR}/${ANDROID_ABI}/libavutil.so)
    
    add_library(postproc SHARED IMPORTED)
    set_target_properties(postproc
                          PROPERTIES IMPORTED_LOCATION
                          ${LIB_DIR}/${ANDROID_ABI}/libpostproc.so)
    
    add_library(swresample SHARED IMPORTED)
    set_target_properties(swresample
                          PROPERTIES IMPORTED_LOCATION
                          ${LIB_DIR}/${ANDROID_ABI}/libswresample.so)
    
    add_library(swscale SHARED IMPORTED)
    set_target_properties(swscale
                          PROPERTIES IMPORTED_LOCATION
                          ${LIB_DIR}/${ANDROID_ABI}/libswscale.so)
    
    add_library(yuv SHARED IMPORTED)
    set_target_properties(yuv
                          PROPERTIES IMPORTED_LOCATION
                          ${LIB_DIR}/${ANDROID_ABI}/libyuv.so)
  
  * 关联第三方库
   
   
    target_link_libraries( # Specifies the target library.
                          player
                          avcodec
                          avdevice
                          avfilter
                          avformat
                          avutil
                          postproc
                          swresample
                          swscale
                          yuv
   
                          # Links the target library to the log library
                          # included in the NDK.
                          # 使用native_window需要引入，android这里是简写，也可以仿照log-lib去写
                          android
                          ${log-lib} )
 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    