#ifndef PROJECT_OPENCVSTREAM_HPP
#define PROJECT_OPENCVSTREAM_HPP

#include "opencv2/opencv.hpp"

using namespace cv;
namespace  ATVIDEO{
class _opencvStream{
 public:
  _opencvStream(std::string path);
  ~_opencvStream();
  bool open(std::string path,std::string type);
  bool getFrameByIdx(int idx, cv::Mat &frame);
  bool getFrameByTime(float offset, cv::Mat &frame);
  bool getNextFrame(cv::Mat & frame);
  double getVideoFPS();
 private:
  VideoCapture *stream;
};
}



#endif //PROJECT_OPENCVSTREAM_HPP
