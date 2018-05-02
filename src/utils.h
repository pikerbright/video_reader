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

template<typename T>
T* new_data(size_t* pitch, size_t width, size_t height);

template<typename T>
T* get_data(size_t* ret_pitch, size_t width, size_t height);

template<typename T>
cv::cuda::GpuMat get_pixels(const PictureSequence& sequence, int index,
                            std::initializer_list<int> channel_order);

template<>
cv::cuda::GpuMat get_pixels<half>(const PictureSequence& sequence, int index,
                                  std::initializer_list<int> channel_order);

template<typename T>
void write_frame(const PictureSequence& sequence);

template<typename T>
void get_frame(NVVL::VideoLoader& loader, cv::Mat &frame, size_t width, size_t height,
               NVVL::ColorSpace color_space = ColorSpace_RGB,
               bool scale = false, bool normalized = false, bool flip = false,
               NVVL::ScaleMethod scale_method = ScaleMethod_Linear);
#endif //STREAM_UTILS_H
