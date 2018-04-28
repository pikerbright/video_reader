//
// Created by 赵之健 on 2018/4/26.
//

#include "opencvstream.hpp"
#include "opencv2/opencv.hpp"

using namespace ATVIDEO;

_opencvStream::_opencvStream(std::string path) {
  stream = new cv::VideoCapture();
  stream->open(path);

}

_opencvStream::~_opencvStream(){
  if (stream->isOpened()){
    stream->release();
  }
  delete(stream);

}

bool _opencvStream::open(std::string path, std::string type) {

  if (type == "opencv"){
    if (stream->isOpened()){
      stream->release();
    }

    stream->open(path);
    return true;
  }
  return false;
}

bool _opencvStream::getNextFrame(cv::Mat &frame) {
  if (stream->isOpened()){
    stream->read(frame);
    return true;
  }
  return false;

}

bool _opencvStream::getFrameByTime(float offset, cv::Mat &frame) {
  if (stream->isOpened()){
    stream->set(cv::CAP_PROP_POS_MSEC,offset*1000);
    getNextFrame(frame);
    return true;
  }
  return false;
}

bool _opencvStream::getFrameByIdx(int idx, cv::Mat &frame) {
  if (stream->isOpened()){
    stream->set(cv::CAP_PROP_POS_FRAMES,idx);
    getNextFrame(frame);
    return true;
  }
  return false;
}

double _opencvStream::getVideoFPS() {
  if (stream->isOpened()){
    return stream->get(cv::CAP_PROP_FPS);
  }
  return  -1;
}

