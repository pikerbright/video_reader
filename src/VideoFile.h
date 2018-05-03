//
// Created by 朱亮 on 2018/4/28.
//

#ifndef STREAM_VIDEOFILE_H
#define STREAM_VIDEOFILE_H
#include <cstdint>
#include <iostream>
#include "opencv2/opencv.hpp"

#include "VideoLoader.h"
#include "VideoInput.h"

using namespace std;

namespace ATVIDEO {
    class VideoFile {
    public:
        VideoFile();

        virtual ~VideoFile();

        bool open(string path);

        void close();

        bool getFrameByIdx(int idx, cv::Mat &frame);

        bool getFrameByTime(float offset, cv::Mat &frame);

        bool getNextFrame(cv::Mat &frame);

        bool readSequenceFrame(int idx, int count);

        double getVideoFPS();

    private:
        NVVL::VideoLoader loader_;
        string filename;
        Size size;
        bool is_open;
    };
}
#endif //STREAM_VIDEOFILE_H
