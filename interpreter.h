#ifndef INTERPRETER_H
#define INTERPRETER_H
#endif // INTERPRETER_H
#include<iostream>
#include<regex>
#include<vector>
#include<map>
#include<string>
#include<fstream>
using namespace std;
class Interpreter
{
 private:
  map<string,string> para_type; //变量类型
  map<string,int> Int;         //int型变量
  map<string,string> str;     //字符型变量
  map<string,vector<string>> pre_list; //自定义函数变量名称集合
  map<string,string> fun_list;   //自定义函数代码
  vector<string> split(string str,char pi);  //字符串分割函数
 public:
  void run(string path);
  void Variable_inte(string code);//
  string get_func_code(fstream &f);
  void fun_inte(string fun_name,string code,string pre);//
  void built_func(string func_name,string pre);
};
