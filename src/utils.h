//
// Created by 朱亮 on 2018/4/28.
//

#ifndef STREAM_UTILS_H
#define STREAM_UTILS_H

#include <iostream>

# include <opencv2/imgcodecs.hpp>
# include <opencv2/cudaimgproc.hpp>
# include <opencv2/cudaarithm.hpp>
#include <cuda.h>
#include "PictureSequence.h"
#include "PictureSequence.h"
#include "cuda/utils.h"

using PictureSequence = NVVL::PictureSequence;

void get_frame(NVVL::VideoLoader& loader, cv::Mat &frame, size_t width, size_t height,
               NVVL::ColorSpace color_space = ColorSpace_RGB,
               bool scale = false, bool normalized = false, bool flip = false,
               NVVL::ScaleMethod scale_method = ScaleMethod_Linear);
#endif //STREAM_UTILS_H
