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
    char output_file[256];

    cv::Mat frame;
    int count = atoi(argv[2]);
    video_file.readSequenceFrame(0, count);

    for(int i = 0; i < count; i++) {
        if (!video_file.getNextFrame(frame))
            break;
        sprintf(output_file,"./output/%05d.jpg",i);
        cv::imwrite(output_file,frame);
    }

    video_file.close();
}

