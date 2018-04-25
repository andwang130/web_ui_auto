#include<interpreter.h>
#include<cctype>
void Interpreter::run(string path)
{
  fstream f;
  f.open(path,ios::in);
  if(!f.is_open())
    {
      cout<<"null"<<endl;

    }
  string code;
  smatch st1;
  regex func_re("函数 (\\w+)\\((.*?)\\)"); //匹配脚本写的函数
  regex func_impt("(\\w+)\\((.*?)\\)"); //匹配函数调用

  regex variable_re("(整型|字符串)\\s(\\w+)");  //匹配变量定义
  while(getline(f,code)) //逐行读取
    {

      if(regex_match(code,st1,func_re)) //匹配到了函数定义
        {  string func_code;
          vector<string> pre_str=split(st1[2],','); //将参分割
          pre_list[st1[1]]=pre_str;
          func_code=get_func_code(f);   //转到函数代码的获取
          fun_list[st1[1]]=code+func_code; //获取到代码了，函数名为键，存到保存函数的map当中
        }
      else if(regex_match(code,st1,func_impt))  //匹配到函数调用
        {
          string impt_code;
          //st1[1];     //函数名
          //st1[2]     //参数内容
          impt_code=fun_list[st1[1]];
          string pre=st1[2];

          if(impt_code!="")
            {
              fun_inte(st1[1],impt_code,pre);  //该函数存在，为定义函数转到定义函数调用
            }
          else
            {
             built_func(st1[1],pre);    //没有找到，函数为内部函数，转到内部函数调用
            }
        }
      else if(regex_match(code,st1,variable_re))
        {

          cout<<st1[1]<<endl;
          cout<<st1[2]<<endl;
        }

    }
}
string Interpreter::get_func_code(fstream &f) //获得定义函数的代码
{
  string str;
  string code;
  smatch st1;
  int x=0;
  regex end("\\};");
  while(true)
    {
      x++;
      getline(f,code);
      str=str+'\n'+code;
      if(regex_match(code,st1,end))
        {
          break;
        }
    }
  return str;

}
void Interpreter::Variable_inte(string code) //参数定义
{

}
void Interpreter::fun_inte(string fun_name,string code,string pre) //定义函数调用
{
  map<string,int> pre_int;//int类型的参数
  map<string,string>pre_str;//
  vector<string> pre_l=pre_list[fun_name];
  vector<string> pre_vec=split(pre,','); //将参数内容分割
  for(int i=0;i<pre_vec.size();i++)  //获取每个参数
    {
     if(isnum(pre_vec[i]))
       {
         //pre_int[pre_l[i]]=stoi(pre_vec[i].c_str()); //字符串转整型报错了， 还未解决
       }
     else if(isStr(pre_vec[i]))
       {
         pre_str[pre_l[i]]=pre_vec[i];
       }
     else
       {
         string type=para_type[pre_l[i]];
         if(type=="整型")
           {
             pre_int[pre_l[i]]=para_Int[pre_l[i]];
           }
         else if(type=="字符串")
           {
             pre_str[pre_l[i]]=para_str[pre_l[i]];
           }

       }
    }

}
void Interpreter::get_pre(string pre_nmae,int &Int,string &str)
{

}
void Interpreter::built_func(string func_name,string pre) //内部函数调用
{

}
vector<string> Interpreter::split(string str,char pi) //自己写的一个字符串分割函数
{
  vector<string> str_ve;
  string temporary;
  for(int i=0;i<str.size();i++)
    {
      if(str[i]==pi)
        {
          str_ve.push_back(temporary);
          temporary="";
        }
      else
        {
          temporary=temporary+str[i];

        }
    }
  if(temporary!="")
    {
      str_ve.push_back(temporary);
    }
  return str_ve;
}
bool Interpreter::isnum(string str) //判断一个字符串是否全是数字
{
  for(int i;i<str.size();i++)
    {
      if(!isdigit(str[i]))
        {
          return false;
        }
    }
  return true;
}
bool Interpreter::isStr(string str)//判断字符串
{
  char head=str.at(0);
  char end=str.at(str.size()-1);
  if(head=='"'&&end=='"')
  {
      return true;
  }
  else
    {
      return false;
    }


}
