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
  map<string,string> para_type;
  map<string,int> Int;
  map<string,string> str;
  map<string,vector<int>> list;
  map<string,string> fun_list;
  vector<string> split(string str,char pi);
 public:
  void run(string path);
  void Variable_inte(string code);//
  string get_func_code(fstream &f);
  void fun_inte(string code,string pre);//
  void built_func(string func_name);
};
