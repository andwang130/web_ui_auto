#ifndef SPECIFIC_H
#define SPECIFIC_H

#endif // SPECIFIC_H
#include<control.h>
#include<opencv_code.h>
//************************
//封装的整合操作类,供解释类调用
class Integration
{
private:
CMyOpencv *Mopen_cv;
CControl *Contr;
static const int IN_DOUBLE=1;//双击参数
static const int IN_ONE=2;//单击参数
public:
Integration();//构造函数
~Integration();//析构函数
void Match_Click(string path,const int click_falg=IN_DOUBLE);//传入一张图片的地址，然后点击这张图片的位置
void Math_Move(string path);//匹配移动，传入一张图片的地址，移动到该位置
void L_Click(int x,int y);//左键单击
void L_Click_d(int x,int y);//右键双击
void R_Click(int x,int y);//右键单击
void R_click_d(int x,int y);
void Press_one(char str);//按一个键，自动会谈起
void Press_lower(char str);//按下一个键不弹起
void Bounce(char str);//弹起一个键
void input(string str);//输入字符串
};