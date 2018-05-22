#include "VideoLoader.h"
#include "VideoStream.h"
#include "utils.h"

using PictureSequence = NVVL::PictureSequence;

namespace ATVIDEO {

    VideoStream::VideoStream() : loader_(0, LogLevel_Debug), is_open(false) {
    }

    VideoStream::VideoStream(string path) : loader_(0, LogLevel_Debug),
                                        is_open(false) {
        path_ = path;
        size = nvvl_video_size_from_file(path_.c_str());
        is_open = true;
    }

    VideoStream::~VideoStream() {
        close();
    }

    bool VideoStream::open(string path) {
        if (!is_open) {
            try {
                path_ = path;
                size = nvvl_video_size_from_file(path_.c_str());
                is_open = true;
            }
            catch (exception& e) {
                cout << e.what() << endl;
                return false;
            }
        }

        return true;
    }

    void VideoStream::close() {
        loader_.finish();
    }

    bool VideoStream::getNextFrame(cv::Mat &frame) {
        if (!is_open)
            return false;

        bool ret = get_frame(loader_, frame, size.width, size.height, ColorSpace_RGB, false, false, false);

        return ret;
    }

    bool VideoStream::readStream() {
        if (!is_open)
            return false;

        loader_.read_stream(path_.c_str());
        return true;
    }

    double VideoStream::getVideoFPS() {
        if (!is_open)
            throw std::runtime_error(std::string("Video file is not open yet"));

        return nvvl_video_fps_from_file(path_.c_str());
    }

}
