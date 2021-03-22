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
