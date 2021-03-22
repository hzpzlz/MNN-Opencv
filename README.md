# MNN-Opencv
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
## 3 参考链接
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
