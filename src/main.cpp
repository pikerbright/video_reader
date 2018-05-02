//
// Created by 朱亮 on 2018/5/2.
//
#include <string>
#include "VideoFile.h"


using namespace ATVIDEO;
using namespace std;

int main(int argc, char* argv[])
{
    VideoFile video_file;
    video_file.open(string(argv[1]));

    cv::Mat frame;
    video_file.getFrameByIdx(0, frame);
}

