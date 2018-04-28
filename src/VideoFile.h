//
// Created by 朱亮 on 2018/4/28.
//

#ifndef STREAM_VIDEOFILE_H
#define STREAM_VIDEOFILE_H
#include <iostream>
#include "opencv2/opencv.hpp"

#include "VideoLoader.h"
#include "VideoInput.h"

using namespace std;

namespace ATVIDEO {
    class VideoFile : public IVideoInput {
    public:
        VideoFile();

        virtual ~VideoFile();

        virtual bool open(string path, string type);

        virtual bool getFrameByIdx(int idx, cv::Mat &frame);

        virtual bool getFrameByTime(float offset, cv::Mat &frame);

        virtual bool getNextFrame(cv::Mat &frame);

        virtual double getVideoFPS();

    private:
        NVVL::VideoLoader loader_;
        uint32_t current_frame;
        string filename;
    };
}
#endif //STREAM_VIDEOFILE_H
