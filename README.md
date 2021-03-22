# MNN-Opencv Quantize
Verify the accuracy of MNN model conversion
## 1 参考https://github.com/hzpzlz/MNN-Compiler 完成MNN框架编译
## 2 在MNN/demo/exec目录下的CMakeLists.txt中添加：
```
add_executable(RFDN_woESA.out ${CMAKE_CURRENT_LIST_DIR}/RFDN_woESA.cpp)
target_link_libraries(RFDN_woESA.out ${MNN_DEPS}
                      /usr/local/lib/libopencv_highgui.so.3.4.7
                      /usr/local/lib/libopencv_core.so.3.4.7
                      /usr/local/lib/libopencv_imgproc.so.3.4.7
                      /usr/local/lib/libopencv_imgcodecs.so.3.4.7
                      /usr/local/lib/libopencv_dnn.so.3.4.7
                      /usr/local/lib/libopencv_dnn_objdetect.so.3.4.7)
```
- 如果不添加以下4行，无法使用opencv
```
/usr/local/lib/libopencv_highgui.so.3.4.7
/usr/local/lib/libopencv_core.so.3.4.7
/usr/local/lib/libopencv_imgproc.so.3.4.7
/usr/local/lib/libopencv_imgcodecs.so.3.4.7
```
- 如果不添加以下两行，无法使用cv::dnn::blobFromImage进行图像格式转换
```
/usr/local/lib/libopencv_dnn.so.3.4.7
/usr/local/lib/libopencv_dnn_objdetect.so.3.4.7
```
## 3 量化
- a. 编写量化所需的json文件
```
{
    "format":"RGB",
    "mean":[
        0.0,
        0.0,
        0.0
    ],
    "normal":[
        0.00392156862745,
        0.00392156862745,
        0.00392156862745
    ],
    "width":512,
    "height":512,
    "path":"/home/notebook/data/group/hezhipeng/compare_method/cover_hard_512x512"
}
```
- 这里的mean和norm取决于你的数据预处理方式，dst=(src-mean)·normal，因为我的预处理只要/255，所以设置如上
- b. 使用MNN/build/quantized.out进行量化，生成量化以后的mnn文件
```
./MNN/build/quantized.out ${save_path}.mnn ${save_quant_path}.mnn ${json_path}.json
```
- c.将得到的量化后的的mnn替换到main.cpp里面的路径就可以了
- 注：MNN进行了量化和反量化，输入输出都可以是Float类型的，不需要进行额外的数据转换
## 4 参考链接
- https://blog.csdn.net/XDH19910113/article/details/100099318
### 官方文档
- https://www.yuque.com/mnn/cn/output
### MNN输入输出
- https://github.com/alibaba/MNN/issues/909
- https://blog.csdn.net/qq_37546267/article/details/108056650
### CmakeLists.txt配置
- https://github.com/alibaba/MNN/issues/666
### opencv Mat permute
- https://www.zhihu.com/question/400627328
- https://docs.opencv.org/3.4/d6/d0f/group__dnn.html#ga29f34df9376379a603acd8df581ac8d7
### json文件
- https://github.com/alibaba/MNN/blob/master/tools/quantization/preprocessConfig.json
