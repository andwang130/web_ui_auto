#include<interpreter.h>
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
  regex func_re("函数 (\\w+)\\(.*?\\)");
  regex func_impt("(\\w+)\\((.*?)\\)");
  regex variable_re("(整型|字符串)\\s(\\w+)");
  while(getline(f,code))
    {
      if(regex_match(code,st1,func_re))
        {  string func_code;
          func_code=get_func_code(f);
          fun_list[st1[1]]=code+func_code;
          cout<<fun_list["func"]<<endl;
        }
      else if(regex_match(code,st1,func_impt))
        {
          string impt_code;
          cout<<st1[1]<<'\n';
          cout<<st1[2]<<'\n';
          impt_code=fun_list[st1[1]];
        }
      else if(regex_match(code,st1,variable_re))
        {

          cout<<st1[1]<<endl;
          cout<<st1[2]<<endl;
        }
      //cout<<code<<endl;;
    }
}
string Interpreter::get_func_code(fstream &f)
{
  string str;
  string code;
  smatch st1;
  int x=0;
  regex end("};");
  while(x<10)
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
void Interpreter::Variable_inte(string code)
{

}
void Interpreter::fun_inte(string code,string pre)
{
  vector<string> pre_vec=split(pre,',');
  for(int i=0;i<pre_vec.size();i++)
    {
      cout<<pre_vec[i]<<endl;
    }

}
void Interpreter::built_func(string func_name)
{

}
vector<string> Interpreter::split(string str,char pi)
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
  return str_ve;
}
