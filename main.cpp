#include <stdio.h>
#include <MNN/ImageProcess.hpp>
#include <MNN/Interpreter.hpp>
#define MNN_OPEN_TIME_TRACE
#include <algorithm>
#include <fstream>
#include <functional>
#include <memory>
#include <sstream>
#include <vector>
#include <MNN/AutoTime.hpp>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/dnn/dnn.hpp>  //for cv::dnn::blobFromImage

using namespace std;
using namespace MNN;
using namespace MNN::CV;
//https://blog.csdn.net/qq_37546267/article/details/108056650
int main()
{
   //complete your img path and xxx.mnn model path
    const char* input_image_path = "test.png";
    const char* output_image_path = "test_mnn.png";
    
    const char* model_name = "xxx.mnn";
    
    cv::Mat input_img = cv::imread(input_image_path);
    cv::Mat input_img_f;
    input_img.convertTo(input_img_f, CV_32FC3, 1 / 255.0);  //convert to float format
    
    int width, height;
    width = input_img.rows;
    height = input_img.cols;
    
    cv::Mat input_img_blob;
    cv::dnn::blobFromImage(input_img_f, input_img_blob);   //convert HWC to NCHW
    
    std::vector<int> dims{1, 3, width, height};
    auto nhwc_Tensor = MNN::Tensor::create<float>(dims, NULL, MNN::Tensor::CAFFE);
    auto nhwc_data   = nhwc_Tensor->host<float>();
    auto nhwc_size   = nhwc_Tensor->size();
    ::memcpy(nhwc_data, input_img_blob.data, nhwc_size);
    
    auto net = std::shared_ptr<MNN::Interpreter>(MNN::Interpreter::createFromFile(model_name));   //load model
    
    ScheduleConfig config;
    config.type  = MNN_FORWARD_CPU;

    auto session = net->createSession(config);
    auto input = net->getSessionInput(session, nullptr);  //MNN::Tensor
    
    input->copyFromHostTensor(nhwc_Tensor);   //load input data to model's input
    
    auto batch_in = input->batch();
    auto height_in = input->width();
    auto width_in = input->height();
    auto channel_in = input->channel();
    
    MNN_PRINT("input_tensor: bi=%d, wi=%d, hi=%d, ci=%d\n", batch_in, width_in, height_in, channel_in);   //print input info
    
    {
        AUTOTIME;
        net->runSession(session);   // run
    }
    
    auto outputTensor = net->getSessionOutput(session, NULL);   //get output
    
    //outputTensor->printShape();   //print output tensor dims
    //outputTensor->print();        //print output tensor one by one
    
    // get output tensor dims
    auto batch_out = outputTensor->batch();
    auto height_out = outputTensor->width();
    auto width_out = outputTensor->height();
    auto channel_out = outputTensor->channel();
    
    std::vector<int> dims_out{width_out, height_out, 3};   //define output size
    auto hwc_Tensor = MNN::Tensor::create<float>(dims_out, NULL, MNN::Tensor::TENSORFLOW);  //here we want to get HWC to fit opencv format,so use MNN::Tensor::TENSORFLOW type
    auto hwc_data   = hwc_Tensor->host<float>();
    auto hwc_size   = hwc_Tensor->size();
    
    cv::Mat output_img(height_out, width_out, CV_32FC3);   //difine opencv out img
    outputTensor->copyToHostTensor(hwc_Tensor);
    
    ::memcpy(output_img.data, hwc_data, hwc_size);     //copy to output_img
    
    delete hwc_Tensor;
    
    MNN_PRINT("output_tensor: bo=%d, wo=%d, ho=%d, co=%d\n", batch_out, width_out, height_out, channel_out);
    
    cv::imwrite(output_image_path, output_img*255.0);  
    
    return 0;
}
