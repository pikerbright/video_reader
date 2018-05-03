//
// Created by 朱亮 on 2018/4/28.
//
#include <iostream>

# include <opencv2/imgcodecs.hpp>
# include <opencv2/cudaimgproc.hpp>
# include <opencv2/cudaarithm.hpp>
#include <cuda.h>

#include "VideoLoader.h"
#include "utils.h"

using PictureSequence = NVVL::PictureSequence;

constexpr auto scale_width = int16_t{1280/2};
constexpr auto scale_height = int16_t{720/2};

template<typename T>
T* new_data(size_t* pitch, size_t width, size_t height) {
    T* data;
    if(cudaMallocPitch(&data, pitch, width * sizeof(T), height) != cudaSuccess) {
        throw std::runtime_error("Unable to allocate buffer in device memory");
    }
    return data;
}

// just use one buffer for each different type
template<typename T>
auto get_data(size_t* ret_pitch, size_t width, size_t height) {
    static size_t pitch;
    static auto data = std::unique_ptr<T, decltype(&cudaFree)>{
            new_data<T>(&pitch, width, height * 1 * 3),
            cudaFree};
    *ret_pitch = pitch / sizeof(T);
    //std::cout << "get data " << width << " " << height << " " << *ret_pitch << std::endl;
    return data.get();
}

template<typename T>
cv::cuda::GpuMat get_pixels(const PictureSequence& sequence, int index,
                            std::initializer_list<int> channel_order) {
    auto pixels = sequence.get_layer<T>("data", index);
    auto type = cv::DataType<T>::type;
    auto channels = std::vector<cv::cuda::GpuMat>();
    for (auto i : channel_order) {
        channels.emplace_back(pixels.desc.height, pixels.desc.width, type,
                              pixels.data + pixels.desc.stride.c*i,
                              pixels.desc.stride.y * sizeof(T));
    }
    auto tmp = cv::cuda::GpuMat();
    cv::cuda::merge(channels, tmp);
    auto out = cv::cuda::GpuMat();
    tmp.convertTo(out, CV_8U, pixels.desc.normalized ? 255.0 : 1.0);
    return out;
}

template<>
cv::cuda::GpuMat get_pixels<half>(const PictureSequence& sequence, int index,
                                  std::initializer_list<int> channel_order) {
    auto pixels = sequence.get_layer<half>("data", index);
    auto channels = std::vector<cv::cuda::GpuMat>();
    for (auto i : channel_order) {
        auto channel = cv::cuda::GpuMat((int)pixels.desc.height, (int)pixels.desc.width, CV_32FC1);

        half2float(pixels.data + pixels.desc.stride.c*i, pixels.desc.stride.y,
                   pixels.desc.width, pixels.desc.height,
                   channel.ptr<float>(), channel.step1());
        channels.push_back(channel);
    }
    auto tmp = cv::cuda::GpuMat();
    cv::cuda::merge(channels, tmp);
    auto out = cv::cuda::GpuMat();
    tmp.convertTo(out, CV_8U, pixels.desc.normalized ? 255.0 : 1.0);
    return out;
}

template<typename T>
bool get_frame_data(const PictureSequence& sequence, cv::Mat &frame) {
    auto frame_nums = sequence.get_meta<int>("frame_num");
    int ret_frame = frame_nums[0];
    if (ret_frame < 0) {
        std::cout << "reach stream end" << std::endl;
        return false;
    }
    for (int i = 0; i < sequence.count(); ++i) {
        auto pixels = sequence.get_layer<T>("data", i);

        auto gpu_bgr = cv::cuda::GpuMat();
        if (pixels.desc.color_space == ColorSpace_RGB) {
            gpu_bgr = get_pixels<T>(sequence, i, {2, 1, 0});
        } else {
            auto gpu_yuv = get_pixels<T>(sequence, i, {0, 2, 1});
            cv::cuda::cvtColor(gpu_yuv, gpu_bgr, CV_YCrCb2BGR);
        }

        //cv::Mat host_bgr;
        gpu_bgr.download(frame);
    }

    return true;
}

template<typename T>
bool get_frame(NVVL::VideoLoader& loader, cv::Mat &frame, size_t width, size_t height,
               NVVL::ColorSpace color_space,
               bool scale, bool normalized, bool flip,
               NVVL::ScaleMethod scale_method)
{
    auto s = PictureSequence{1};

    auto pixels = PictureSequence::Layer<T>{};
    pixels.data = get_data<T>(&pixels.desc.stride.y, width, height);
    pixels.desc.count = 1;
    pixels.desc.channels = 3;
    pixels.desc.width = width;
    pixels.desc.height = height;
    if (scale) {
        pixels.desc.scale_width = scale_width;
        pixels.desc.scale_height = scale_height;
    }
    pixels.desc.horiz_flip = flip;
    pixels.desc.normalized = normalized;
    pixels.desc.color_space = color_space;
    pixels.desc.scale_method = scale_method;
    pixels.desc.stride.x = 1;
    pixels.desc.stride.c = pixels.desc.stride.y * pixels.desc.height;
    pixels.desc.stride.n = pixels.desc.stride.c * 3;
    s.set_layer("data", pixels);

    loader.receive_frames_sync(s);
    return get_frame_data<T>(s, frame);
}

bool get_frame(NVVL::VideoLoader& loader, cv::Mat &frame, size_t width, size_t height,
               NVVL::ColorSpace color_space,
               bool scale, bool normalized, bool flip,
               NVVL::ScaleMethod scale_method)
{
    return get_frame<uint8_t>(loader, frame, width, height, color_space,
                       scale, normalized, flip, scale_method);
}

