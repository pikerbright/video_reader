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

using PictureSequence = NVVL::PictureSequence;
constexpr auto sequence_count = uint16_t{4};

namespace ATVIDEO {

    VideoFile::VideoFile() : loader_(0, LogLevel_Debug), is_open(false) {
    }

    VideoFile::VideoFile(string path) : loader_(0, LogLevel_Debug),
                                        is_open(false) {
        filename = path;
        size = nvvl_video_size_from_file(filename.c_str());
        is_open = true;
    }

    VideoFile::~VideoFile() {
        close();
    }

    bool VideoFile::open(string path) {
        if (!is_open) {
            try {
                filename = path;
                size = nvvl_video_size_from_file(filename.c_str());
                is_open = true;
            }
            catch (exception& e) {
                cout << e.what() << endl;
                return false;
            }
        }

        return true;
    }

    void VideoFile::close() {
        loader_.finish();
    }

    bool VideoFile::getFrameByIdx(int idx, cv::Mat &frame) {
        if (!is_open)
            return false;

        loader_.read_sequence(filename.c_str(), idx, 1);
        bool ret = get_frame(loader_, frame, size.width, size.height, ColorSpace_RGB, false, false, false);

        return ret;
    }

    bool VideoFile::getFrameByTime(float offset, cv::Mat &frame) {
        if (!is_open)
            return false;

        int req_frame = nvvl_get_req_frame_by_time(filename.c_str(), (int) offset * 1000);
        loader_.read_sequence(filename.c_str(), req_frame, 1);
        bool ret = get_frame(loader_, frame, size.width, size.height, ColorSpace_RGB, false, false, false);

        return ret;
    }

    bool VideoFile::getNextFrame(cv::Mat &frame) {
        if (!is_open)
            return false;

        bool ret = get_frame(loader_, frame, size.width, size.height, ColorSpace_RGB, false, false, false);

        return ret;
    }

    bool VideoFile::readSequenceFrame(int idx, int count) {
        if (!is_open)
            return false;

        loader_.read_sequence(filename.c_str(), idx, count);
        return true;
    }

    double VideoFile::getVideoFPS() {

    }

    int VideoFile::getVideoFrameCount() {
        if (!is_open)
            throw std::runtime_error(std::string("Video file is not open yet"));

        return nvvl_video_frame_count_from_file(filename.c_str());
    }

}


