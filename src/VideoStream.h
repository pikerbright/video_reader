#ifndef STREAM_VIDEOSTREAM_H
#define STREAM_VIDEOSTREAM_H

#include "VideoLoader.h"

using namespace std;

namespace ATVIDEO {
    class VideoStream {
    public:
        VideoStream();

        VideoStream(string path);

        virtual ~VideoStream();

        bool open(string path);

        void close();

        bool getNextFrame(cv::Mat &frame);

        bool readStream();

        double getVideoFPS();

    private:
        NVVL::VideoLoader loader_;
        string path_;
        Size size;
        bool is_open;
    };
}

#endif //STREAM_VIDEOSTREAM_H
