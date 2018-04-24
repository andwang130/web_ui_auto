#ifndef OPENCV_CODE_H
#define OPENCV_CODE_H
#endif // OPENCV_CODE_H
#include<iostream>
#include<string>
#include<Windows.h>
#include<wingdi.h>
#include<opencv/cv.hpp>
#include<opencv/highgui.h>

using namespace std;
using namespace cv;

class CMyOpencv
{
public:
  int WINx;//屏幕的X
  int WINy;//屏幕的Y
  CMyOpencv(); //构造函数，在构造函数中将初始化，屏幕的X,Y
  Mat screenshot(int x,int y);//使用opencv进行截图，传入两个参数
  Mat current(void);//对当前屏幕进行截图
  Mat open_Imge(string path);//使用opencv打开一张图片，返回这张图片的Mat
  void Img_contrast(Mat imgMat,Mat temMat,int &x,int &y);//传入两张图片的Mat，进行对比，需要传入x,y的坐标
  void Img_contrast(string path,string tempath,int &x,int &y);//传入两个路径做对比

};
