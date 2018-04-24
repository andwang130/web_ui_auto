#include<opencv_code.h>
#pragma comment (lib, "gdi32.lib")
CMyOpencv::CMyOpencv()
{
  WINx=GetSystemMetrics(SM_CXSCREEN);//获得屏幕的X大小
  WINy=GetSystemMetrics(SM_CXSCREEN);//获得屏幕的Y
}
Mat CMyOpencv::current()
{
  HDC hdc=GetDC(NULL); //获得窗口的句柄
  HDC comhdc=CreateCompatibleDC(hdc);//设置一个画布
  HBITMAP hbitmap=CreateCompatibleBitmap(hdc,WINx,WINy);//传入hdc句柄和x,y，获取句柄的位图
  SelectObject(comhdc,hbitmap);//将位图写入comhdc内存画布中
   BitBlt(comhdc,0,0,WINx,WINy,hdc,0,0,SRCCOPY);
  BITMAP bitmap;
  GetObjectA(hbitmap,sizeof(BITMAP),&bitmap);


  //GetObject函数得泛指得到对象，到指定图形对象的信息，根据图形对象，函数把填满的或结构，或表项（用于逻辑调色板）数目放入一个指定的缓冲区
  //百度的也没看太懂
  int nchan=bitmap.bmBitsPixel==1?1:bitmap.bmBitsPixel/8;
  Mat v_mat;
  v_mat.create(cvSize(bitmap.bmWidth,bitmap.bmHeight),CV_MAKETYPE(CV_8U,4));//创建一个新的mat矩阵体
  GetBitmapBits(hbitmap,bitmap.bmWidth*bitmap.bmHeight*nchan,v_mat.data);//将bitamp的数据读取道mat
  DeleteDC(hdc);
  DeleteDC(comhdc);
  return v_mat;
}
void CMyOpencv::Img_contrast(Mat imgMat,Mat temMat,int &x,int &y)
{
  Mat rec;
  matchTemplate(imgMat,temMat,rec,TM_CCOEFF_NORMED);  //opencv模板匹配函数，4个参数，匹配的图片，模板图片，匹配返回的图片，和匹配的算法类型
  double minVal,maxVal;
  Point minloc,maxloc;
  minMaxLoc(rec,&minVal,&maxVal,&minloc,&maxloc);
  x=maxloc.x;
  y=maxloc.y;
  //100-minVal 计算匹配度。TM_CCOEFF_NORMED匹配，值越小匹配度越高，如果值越小100减去的值也越少


}
Mat CMyOpencv::open_Imge(string path)
{
  return imread(path,-1); //opencv打开图片函数，返回的是Mat对象，Mat一个矩阵，opencv的函数都是对这个矩阵操作.-1为8位图，原通道，这样和全屏截图才是一样的
}
void CMyOpencv::Img_contrast(string path,string tempath,int &x,int &y)
{
  Mat rec;
  Mat imgMat=open_Imge(path);
  Mat temMat=open_Imge(tempath);
  matchTemplate(imgMat,temMat,rec,TM_CCOEFF_NORMED);  //opencv模板匹配函数，4个参数，匹配的图片，模板图片，匹配返回的图片，和匹配的算法类型
  double minVal,maxVal;
  Point minloc,maxloc;
  minMaxLoc(rec,&minVal,&maxVal,&minloc,&maxloc);
  x=maxloc.x;
  y=maxloc.y;



}
