//
// Created by 朱亮 on 2018/4/28.
//
#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>

#include <cuda.h>

#include "VideoLoader.h"
#include "VideoFile.h"
#include "cuda/utils.h"
#include "utils.h"

using namespace ATVIDEO;
using PictureSequence = NVVL::PictureSequence;
constexpr auto sequence_count = uint16_t{4};

VideoFile::VideoFile() : loader_(0, LogLevel_Debug), current_frame(0) {
}

VideoFile::~VideoFile() {
    loader_.finish();
}

bool VideoFile::open(string path) {
    filename = path;
}

void VideoFile::close() {
    loader_.finish();
}

bool VideoFile::getFrameByIdx(int idx, cv::Mat &frame) {
    loader_.read_sequence(filename.c_str(), idx, 1);
    auto size = nvvl_video_size_from_file(filename.c_str());
    get_frame(loader_, frame, size.width, size.height, ColorSpace_RGB, false, false, false);
    current_frame = idx + 1;
}

bool VideoFile::getFrameByTime(float offset, cv::Mat &frame) {
    loader_.read_sequence_by_time(filename.c_str(), (int)offset*1000, 1);
    auto size = nvvl_video_size_from_file(filename.c_str());
    get_frame(loader_, frame, size.width, size.height, ColorSpace_RGB, false, false, false);
    current_frame++;
}

bool VideoFile::getNextFrame(cv::Mat &frame) {
    loader_.read_sequence(filename.c_str(), current_frame, 1);
    auto size = nvvl_video_size_from_file(filename.c_str());
    get_frame(loader_, frame, size.width, size.height, ColorSpace_RGB, false, false, false);
    current_frame++;
}

double VideoFile::getVideoFPS() {

}


