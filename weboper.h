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
void click_PATH(string path);//点击一个浏览器元素
void click_id(string path);
void input_PATH(string path,string str);
 void input_id(string path,string str);
Cweboper(string url);
~Cweboper();
};
