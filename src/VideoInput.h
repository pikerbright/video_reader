//
// Created by 朱亮 on 2018/4/28.
//

#ifndef STREAM_VIDEOINPUT_H
#define STREAM_VIDEOINPUT_H

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;

namespace ATVIDEO {
    class IVideoInput {
    public:
        virtual bool open(string path, string type) = 0;

        virtual bool getFrameByIdx(int idx, cv::Mat &frame) = 0;

        virtual bool getFrameByTime(float offset, cv::Mat &frame) = 0;

        virtual bool getNextFrame(cv::Mat &frame) = 0;

        virtual double getVideoFPS() = 0;
    };
}

#endif //STREAM_VIDEOINPUT_H
