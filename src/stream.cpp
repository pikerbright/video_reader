//
// Created by 赵之健 on 2018/4/26.
//

#include "opencv2/opencv.hpp"
#include "opencvstream.hpp"
#include "stream.hpp"

using namespace ATVIDEO;

using StreamIml = _opencvStream;

stream::stream(string path) { engine_ = std::make_shared<StreamIml>(path); }

bool stream::open(string path, string type){
  auto *engine = reinterpret_cast<StreamIml *>(engine_.get());
  return engine->open(path,type);
}

bool stream::getFrameByIdx(int idx, cv::Mat &frame) {
  auto *engine = reinterpret_cast<StreamIml *>(engine_.get());
  return engine->getFrameByIdx(idx,frame);
}

bool stream::getFrameByTime(float offset, cv::Mat &frame) {
  auto *engine = reinterpret_cast<StreamIml *>(engine_.get());
  return engine->getFrameByTime(offset,frame);
}

bool stream::getNextFrame(cv::Mat &frame) {
  auto *engine = reinterpret_cast<StreamIml *>(engine_.get());
  return engine->getNextFrame(frame);
}

double stream::getVideoFPS() {
  auto *engine = reinterpret_cast<StreamIml *>(engine_.get());
  return engine->getVideoFPS();
}




