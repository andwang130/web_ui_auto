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
  regex Variable_inte_re("(整型|字符串)\\s(\\w+)=(\\S+)"); //匹配变量定义同时赋值
  regex Variable_ass("(\\w+)=(\\S+)"); //匹配变量赋值
  regex print_re("打印\\((\\S+)\\)");//匹配打印
  while(getline(f,code)) //逐行读取
    {
        //cout<<code<<endl;
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
      else if(regex_match(code,st1,variable_re)) //匹配变量定义
        {
          cout<<"变量定义"<<endl;
          Variable_matching(st1[1],st1[2],para_type);

        }
      else if(regex_match(code,st1,Variable_inte_re)) //匹配到v变量定义，并且赋值
        {  cout<<"变量定义"<<endl;
          string var_type=st1[1];
          string var_name=st1[2];
          string value=st1[3];
          Variable_matching(var_type,var_name,para_type);
          if (var_type==Str_IN)
            {
              Variable_inte(var_name,para_str,value);
            }
          else if(var_type==Int_IN)
            {
              Variable_inte(var_name,para_Int,value);
            }

        }

      else if(regex_match(code,st1,Variable_ass))  //匹配变量定义
        {
          string var_name=st1[1];
          string value=st1[2];
          string var_type=para_type[var_name];
          if(var_type==Str_IN)
            {
               Variable_inte(var_name,para_str,value);
            }
          else if(var_type==Int_IN)
            {
               Variable_inte(var_name,para_Int,value);
            }
          else
            {
              throw "变量未定义";
            }
        }
      else if(regex_match(code,st1,print_re)) //打印匹配
        {
          string val=st1[1];
          if(isStr(val))
            {
              str_erase(val);
              print(val);
            }
          else if(isnum(val))
          {
            print(val);

          }
          else if(!para_type[val].empty())
            {
              string var_type=para_type[val];
              if(var_type==Str_IN)
                {
                  if(!para_str[val].empty())
                    {
                      print(para_str[val]);
                    }
                  else
                    {
                      throw "未初始化的变量";
                    }
                }
              else if(var_type==Int_IN)
                {
                  if(!para_Int[val])
                    {
                      print(para_Int[val]);
                    }
                  else
                    {
                       throw "未初始化的变量";
                    }

            }
          else
            {
             throw "未定义的变量";
            }


        }
    }
  }
}
void Interpreter::Variable_matching(string var_type,string var_name,map<string,string> &Vartype_map)//变量匹配
{
  if(var_type=="字符串")
    {
      Vartype_map[var_name]="字符串";
    }
  else if(var_type=="整型")
    {
       Vartype_map[var_name]="整型";
    }
}
void Interpreter::Variable_matching(string var_type,string var_name,map<string,string> &Vartype_map,
                                    map<string,int> &int_map,map<string,string> &str_map,string value)
{
  //变量定义匹配带赋值的
  if(var_type=="整型")
    {
      Vartype_map[var_name]="整型";
      Variable_inte(var_name,int_map,value);
      int re=var_Is_defined(var_name,Vartype_map);
      if(re==1)
      {
          Variable_inte(var_name,int_map,value);
        }
      else if(re==2)
        {
           Variable_inte(var_name,para_Int,value);
        }
       else
        {
          throw "变量未定义";
        }
    }
  else if(var_type=="字符串")
    {
        Vartype_map[var_name]="字符串";
       int re=var_Is_defined(var_name,Vartype_map);
       if(re==1)
       {
           Variable_inte(var_name,str_map,value);
         }
       else if(re==2)
         {
            Variable_inte(var_name,para_str,value);
         }
        else
         {
           throw "变量未定义";
         }
    }
  else
    {

    }
}

int Interpreter::var_Is_defined(string var_name,map<string,string> &Vartype_map) //判断变量是否定义,1在当前传递的map中定义，2在全局map定义，3未定义
{
  if(Vartype_map[var_name].empty())
    {
      if(!para_type[var_name].empty())
        {
          return 2;
        }
      else
        {
          return 3;
        }
    }
  else
    {
      return 1;
    }


}
void Interpreter::Variable_inte(string var_name,map<string,int> &int_map,string value) //整型变量赋值
{
 int Int_;
  if(! isnum(value))
    {
      Int_=int_map[value];
      if(Int_)
        {
        int_map[var_name]=Int_;
        }
      else
        {
      throw "你给我的不是整数类型";
        }
    }
  else
    {
 int_map[var_name]=str_to_int(value);
    }
}
void Interpreter::print(string var)
{
  cout<<var<<endl;
}
void Interpreter::print(int Int)
{
   cout<<Int<<endl;
}
void Interpreter::Variable_inte(string var_name,map<string,string> &str_map,string value) //字符串变量赋值
{
  string value_;
  if(!isStr(value))
    {
      value_=str_map[value];
      if(!value_.empty())
        {
     str_map[var_name]=value_;


        }
      else
        {
          throw "你给我的不是字符串类型";
        }
    }
  else
  {
  value.erase(value.begin());
  value.erase(value.end()-1);
  str_map[var_name]=value;
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
  vector<string> pre_l=pre_list[fun_name];  //内部函数参数列表
  vector<string> pre_vec=split(pre,','); //将参数内容分割
  if(pre_l.size()!=pre_vec.size())
    {
      throw "参数数量不一致";
    }
  for(int i=0;i<pre_vec.size();i++)  //获取每个参数
    {
     if(isnum(pre_vec[i]))
       {


                //cout<<pre_vec[i]<<endl;
               pre_int[pre_l[i]]=str_to_int(pre_vec[i]); //将整型参数放到定义函数参数列表当中

       }
     else if(isStr(pre_vec[i])) //给定义函数传递的是字符串
       {
         string str=pre_vec[i];
         str.erase(str.begin()); //删除首"
         str.erase(str.end()-1);//删除尾部"
         pre_str[pre_l[i]]=str;  //将字符串赋值给内部函数对于的参数
       }
     else //给定义函数传递的是变量
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
         else
           {
             throw "该变量未定义";
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
  for(int i=0;i<str.size();i++)
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
int Interpreter::str_to_int(string str) //字符串转int函数
{
  if(str.empty())
    {
      throw "不能传入一个空的字符串";   //弹出异常
    }
  int Int=0;
  for(int i=0;i<str.size();i++)
    {

      switch(str[i])
        {
        case '0':
          Int=Int*10+0;
          break;
        case '1':
          Int=Int*10+1;
          break;
        case '2':
          Int=Int*10+2;
          break;
        case '3':
          Int=Int*10+3;
          break;
        case '4':
          Int=Int*10+4;
          break;
        case '5':
          Int=Int*10+5;
          break;
        case '6':
          Int=Int*10+6;
          break;
        case '7':
          Int=Int*10+7;
          break;
        case '8':
          Int=Int*10+8;
          break;
        case '9':
          Int=Int*10+9;
          break;

        default:
          throw "无法转换成整型，参数有错误";
        }
    }
  return Int;
}
void Interpreter::str_erase(string &str)
{
  str.erase(str.begin()); //删除首"
  str.erase(str.end()-1);//删除尾部"
}
