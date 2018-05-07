#ifndef WEBOPER_H
#define WEBOPER_H

#endif // WEBOPER_H
#include<webform.h>
#include<QString>
class Cweboper
{
private:
webForm *webviwe;
public:
static void click_PATH(string path,Cweboper *pewb);//点击一个浏览器元素
static void click_id(string path,Cweboper *pewb);
static void input_PATH(string path,string str,Cweboper *pewb);
static void input_id(string path,string str,Cweboper *pewb);
Cweboper(string url);
~Cweboper();
};
