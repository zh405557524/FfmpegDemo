# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# 设置生成的so动态库最后输出的路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/jniLibs/${ANDROID_ABI})

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/jni/include)
# 设置头文件路径，在代码中include时不需要带路径了
include_directories(${INCLUDE_DIR}/ffmpeg ${INCLUDE_DIR}/libyuv)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )

add_library( # Sets the name of the library.
             Player

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
              src/main/jni/player.c )



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

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib
                       avcodec
                       avdevice
                       avfilter
                       avformat
                       avutil
                       swresample
                       swscale
                       yuv


                       # Links the target library to the log library
                       # included in the NDK.
                       # 这里可以简化，不使用${log-lib}
                       # 目录在...\sdk\ndk-bundle\platforms\android-21\arch-arm\usr\lib\liblog.so
                       log )


