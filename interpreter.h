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
const string Str_IN="字符串";
const string Int_IN="整型";
class Interpreter
{
 private:
  map<string,string> para_type; //变量类型
  map<string,int> para_Int;         //int型变量
  map<string,string> para_str;     //字符型变量
  map<string,vector<string>> pre_list; //自定义函数变量名称集合
  map<string,string> fun_list;   //自定义函数代码
  vector<string> split(string str,char pi);  //字符串分割函数
  bool isnum(string str);//判断一个字符串是否全是数字
  bool isStr(string str);//判断字符串
  void get_pre(string pre_nmae,int &Int,string &str);//获取变量
  int str_to_int(string str); //字符串转int函数
  void Variable_inte(string var_name,map<string,int> &int_map,string value);//整型变量赋值
  void Variable_inte(string var_name,map<string,string> &str_map,string value);//字符型变量赋值
  void Variable_inte(string var_name, map<string, int> &int_map, map<string,string> &str_map,string var);//一个变量和另外一个变量赋值
  void Variable_matching(string var_type,string var_name,map<string,string> &Vartype_map);//变量匹配
  void Variable_matching(string var_type,string var_name,map<string,string> &Vartype_map,map<string,int> &int_map,map<string,string> &str_map,string value);
  int var_Is_defined(string var_name,map<string,string> &Vartype_map);//判断变量是否定义,1在当前传递的map中定义，2在全局map定义，3未定义
 public:
  void run(string path);
  void Variable_inte(string code);//
  string get_func_code(fstream &f);
  void fun_inte(string fun_name,string code,string pre);//
  void built_func(string func_name,string pre);
};
