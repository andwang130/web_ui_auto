#ifndef CONTROL_H
#define CONTROL_H
#pragma once
#endif // CONTROL_H
#include<QString>
#include<Windows.h>
#include<QDebug>
#include<iostream>
#include<string>
using namespace std;
class CControl
{
public:
void mouse_move(int x,int y);
void mouse_left_click(int x,int y);//左键点击，带参数
void mouse_left_click();//左键单击，原地点击

void mouse_right_click(int x,int y);
void mouse_right_click();

void mouse_Middle_click(int x,int y);
void mouse_Middle_click();

void mouse_left_double_click(int x,int y);//左键双击
void mouse_left_double_click();//左键原地双击

void mouse_right_double_click(int x,int y); //右键双击
void mouse_right_double_click(); //右键原地双核

void Key_input(char str,int sp=10);//键盘输入,可以传入一个间隔时间默认10毫秒
void Key_donw(char str); //按下一个键
void Key_up(char str); //松开一个键

void input_string(string str); //输入一串字符串，使用的是剪切版

};
