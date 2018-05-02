//
// Created by 赵之健 on 2018/4/26.
//

#ifndef PROJECT_STREAM_HPP
#define PROJECT_STREAM_HPP

#include <memory>
#include "opencv2/opencv.hpp"

using namespace std;
namespace  ATVIDEO{
  class stream{
   public:
    stream(string path);
    bool open(string path,string type);
    bool getFrameByIdx(int idx, cv::Mat &frame);
    bool getFrameByTime(float offset, cv::Mat &frame);
    bool getNextFrame(cv::Mat & frame);
    double getVideoFPS();
   private:
    std::shared_ptr<void> engine_ = nullptr;

  };
}



#endif //PROJECT_STREAM_HPP
