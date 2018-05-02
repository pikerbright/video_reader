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
    class VideoFile : public IVideoInput {
    public:
        VideoFile();

        virtual ~VideoFile();

        bool open(string path) override ;

        void close() override ;

        virtual bool getFrameByIdx(int idx, cv::Mat &frame);

        virtual bool getFrameByTime(float offset, cv::Mat &frame);

        virtual bool getNextFrame(cv::Mat &frame, Size& size);

        virtual bool readSequenceFrame(int idx, int count, Size& size);

        virtual double getVideoFPS();

    private:
        NVVL::VideoLoader loader_;
        string filename;
        int current_frame;
        bool is_open;
    };
}
#endif //STREAM_VIDEOFILE_H
