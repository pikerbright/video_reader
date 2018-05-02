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
    Size size;
    video_file.readSequenceFrame(0, argv[2], size);

    for(int i = 0; i < 3; i++)
        video_file.getNextFrame(frame, size);

    video_file.close();
}

