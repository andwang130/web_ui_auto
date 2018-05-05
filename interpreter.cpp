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
  regex func_re("\\s*函数 (\\w+)\\((.*?)\\)"); //匹配脚本写的函数
  regex if_re("\\s*如果(.*?)");
  regex for_re("\\s*循环(.*?)");//循环匹配
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
      else if(regex_match(code,st1,if_re))  //匹配到IF语句
        {
          string if_Expression=st1[1];

          string if_code=skip_if(f);
         if_init(if_code,if_Expression,para_type,para_str,para_Int);



        }
     else if(regex_match(code,st1,for_re))
        {
           cout<<"匹配到for"<<"********"<<endl;
          string if_Expression=st1[1];
          string for_code=skip_for(f);
          for_init(for_code,if_Expression,para_type,para_str,para_Int);



        }
      else{
          implement(code,para_type,para_str,para_Int); //匹配具体执行

        }
    }


}
void Interpreter::for_init(string code,string if_Expression,map<string,string>&var_map_type,map<string,string>&str_map,map<string,int>&int_map)
{
  smatch st1;
  vector<string> vect_if_code=split(code,'\n');
  regex exp_num("\\((\\d+)\\)");
  int for_num=1;
  if(regex_match(if_Expression,st1,exp_num))
    {
      cout<<st1[1]<<endl;
      for_num=str_to_int(st1[1]);
    }
  for(;for_num>0;for_num--)
    {
  if(Expression(if_Expression,para_type,para_str,para_Int)) //表达式未TRUE，代码继续执行
    {
      regex if_re("\\s*如果(.*?)");
      regex for_re("\\s*循环(.*?)");
      for(int i=0;i<vect_if_code.size();i++)
        {
          if(regex_match(vect_if_code[i],st1,if_re))
            {
              i++;
              string if_code=get_if_code(vect_if_code,i);
              if_init(if_code,st1[1],var_map_type,str_map,int_map);

            }
          else if(regex_match(vect_if_code[i],st1,for_re))
            {
              i++;
              string for_code=get_for_code(vect_if_code,i);
              for_init(for_code,st1[1],var_map_type,str_map,int_map);
            }
          else
            {
          implement(vect_if_code[i],var_map_type,str_map,int_map);
            }
        }

    }
    }
}
void Interpreter::if_init(string code,string if_Expression,map<string,string>&var_map_type,map<string,string>&str_map,map<string,int>&int_map)
{

  smatch st1;
  vector<string> vect_if_code=split(code,'\n');
  if(Expression(if_Expression,para_type,para_str,para_Int)) //表达式未TRUE，代码继续执行
    {

      regex if_re("\\s*如果(.*?)");
      regex for_re("\\s*循环(.*?)");
      for(int i=0;i<vect_if_code.size();i++)
        {
          if(regex_match(vect_if_code[i],st1,if_re))
            {

              i++;
              string if_code=get_if_code(vect_if_code,i);

              if_init(if_code,st1[1],var_map_type,str_map,int_map);



            }
          else if(regex_match(vect_if_code[i],st1,for_re))
            {
              i++;
               string for_code=get_for_code(vect_if_code,i);
               for_init(for_code,st1[1],var_map_type,str_map,int_map);
            }
          else
            {
          implement(vect_if_code[i],var_map_type,str_map,int_map);
            }
        }

    }

}
string Interpreter::skip_for(fstream &f)
{
  string str;
  string code;
  smatch st1;
  int x=0;
  regex end("\\}");
  regex if_re("如果(.*?)");
  regex for_re("循环(.*?)");
  while(true)
    {

      getline(f,code);
      str=str+'\n'+code;
      if(regex_match(code,st1,if_re))
        {
          x++;
        }
      else if(regex_match(code,st1,for_re))
        {
          x++;
        }
      else if(regex_match(code,st1,end)&&x<=0)
        {
          break;
        }
       else if(regex_match(code,st1,end))
        {
         x--;
        }

    }
  return str;
}
string Interpreter::skip_if(fstream &f)
{
  string str;
  string code;
  smatch st1;
  int x=0;
  regex end("\\}");
  regex if_re("如果(.*?)");
  regex for_re("循环(.*?)");
  while(true)
    {

      getline(f,code);
      str=str+'\n'+code;
      if(regex_match(code,st1,if_re))
        {
          x++;
        }
      else if(regex_match(code,st1,for_re))
        {
          x++;
        }
      else if(regex_match(code,st1,end)&&x<=0)
        {
          break;
        }
       else if(regex_match(code,st1,end))
        {
         x--;
        }

    }
  return str;

}
string Interpreter::get_for_code(vector<string> vect_if_code,int &num)
{
  string str;
  string code;
  smatch st1;
  int x=0;
  regex end("\\s*\\}");
  regex if_re("\\s*如果(.*?)");
  regex for_re("\\s*循环(.*?)");
  for(;num<vect_if_code.size();num++){
      str=str+'\n'+vect_if_code[num];
      if(regex_match(vect_if_code[num],st1,if_re))
        {
          x++;
        }
      else if(regex_match(vect_if_code[num],st1,for_re))
        {
          x++;
        }
      else if(regex_match(vect_if_code[num],st1,end)&&x<=0)
        {
          break;
        }
       else if(regex_match(vect_if_code[num],st1,end))
        {
         x--;
        }

    }
  return str;
}
string Interpreter::get_if_code(vector<string> vect_if_code,int &num)
{
  string str;
  smatch st1;
  int x=0;
  regex end("\\s*\\}");
  regex if_re("\\s*如果(.*?)");
  regex for_re("\\s*循环(.*?)");
  for(;num<vect_if_code.size();num++){
      str=str+'\n'+vect_if_code[num];
      if(regex_match(vect_if_code[num],st1,if_re))
        {
          x++;
        }
      else if(regex_match(vect_if_code[num],st1,for_re))
        {
          x++;
        }
      else if(regex_match(vect_if_code[num],st1,end)&&x<=0)
        {

          break;
        }
       else if(regex_match(vect_if_code[num],st1,end))
        {
         x--;
        }

    }
  return str;
}
bool Interpreter::Expression(string code,map<string,string>&var_map_type,map<string,string>&str_map,map<string,int>&int_map) //表达式匹配
{


  regex Variabl_IN("\\((\\w+)(>|<|==|>=|<=)(\\w+)\\)");
  regex nums("\\((\\d+)\\)"); //数字
  smatch st;

  if(regex_match(code,st,Variabl_IN))
    {

          string val1_=st[1];
          string val3_=st[2];
          string val2_=st[3];
          if(isnum(val1_)&&isnum(val2_))
            {

              int val1=str_to_int(val1_);
              int val2=str_to_int(val2_);
             return juge_Expression<int,string,int>(val1,val3_,val2);
            }
          else if(isStr(val1_)&&isStr(val2_))
            {
              str_erase(val1_);
               str_erase(val2_);
               string val1=val1_;
               string val2=val2_;
             return  juge_Expression<string,string,string>(val1,val3_,val2);
            }
          else if(isStr(val1_)&&!isStr(val2_)&&!isnum(val2_))
            {
              str_erase(val1_);
              string val1=val1_;
              string str;
              int Int;
              Variable_get(val2_,str,Int,var_map_type,str_map,int_map);
              if(!str.empty())
                {
                  string val2=str;
                return  juge_Expression<string,string,string>(val1,val3_,val2);
                }
              else
                {
                  throw "类型不一致";
                }



            }
          else if(isnum(val1_)&&!isStr(val2_)&&isnum(val2_))
            {

              int val1=str_to_int(val1_);
              string str;
              int Int;
              Variable_get(val2_,str,Int,var_map_type,str_map,int_map);
              if(Int)
                {
                  int val2=Int;
                 return juge_Expression<int,string,int>(val1,val3_,val2);
                }
              else
                {
                  throw "类型不一致";
                }


            }
          else if(isStr(val2_)&&!isStr(val1_)&&!isnum(val1_))
            {
              str_erase(val2_);
              string val1=val2_;
              string str;
              int Int;
              Variable_get(val1_,str,Int,var_map_type,str_map,int_map);
              if(!str.empty())
                {
                  string val2=str;
                 return juge_Expression<string,string,string>(val1,val3_,val2);
                }
              else
                {
                  throw "类型不一致";
                }



            }
          else if(isnum(val2_)&&!isStr(val1_)&&!isnum(val1_))
            {

              int val2=str_to_int(val2_);
              string str;
              int Int;
              Variable_get(val1_,str,Int,var_map_type,str_map,int_map);
              if(Int)
                {
                  int val1=Int;
                 return juge_Expression<int,string,int>(val1,val3_,val2);
                }
              else
                {
                  throw "类型不一致";
                }


            }
          else
            {
              string str1;
              int Int1;
              string str2;
              int Int2;
              Variable_get(val1_,str1,Int1,var_map_type,str_map,int_map);
              Variable_get(val2_,str2,Int2,var_map_type,str_map,int_map);
              if(!str1.empty()&&!str2.empty())
                {
                  string val1=str1;
                  string val2=str2;
                  return juge_Expression<string,string,string>(val1,val3_,val2);
                }
              else if(Int1&&Int2)
                {
                   int val1=Int1;
                   int val2=Int2;
                 return  juge_Expression<int,string,int>(val1,val3_,val2);

                }
            }

    }
    else if(regex_match(code,st,nums))
      {
     if(st[1]=="0")
       {
         return false;
       }
     else
       {
         return true;
       }
    }
  else
    {
      throw "表达试错误";
    }




}

template<typename v1,typename sy,typename v2>
bool Interpreter::juge_Expression(v1 val1,sy symbol,v2 val2)
{

      if(symbol==">")
        {
           return val1>val2;
        }

      else if(symbol=="<")
        {
          return val1<val2;
        }
      else if(symbol=="==")
        {


            return val1==val2;


        }

      else if(symbol==">=")
        {
          return val1>=val2;




        }
      else if(symbol=="<=")
        {
          return val1==val2;
        }
      else
        {
          throw "表达式错误";
        }


}
int Interpreter::Variable_INT(string var,map<string,int>&int_map)
{

  if(isnum(var))
    {
      return str_to_int(var);
    }

  else
    {
      if(int_map.find(var)==int_map.end())
        {
        if(para_Int.find(var)==para_Int.end())
          {
             throw "该变量未定义";
          }
        else
          {
            return para_Int[var];
          }
        }
      else
        {
          return int_map[var];
        }
    }

}
string Interpreter::Variable_Str(string var,map<string,string>&str_map)//获取字符串变量的值
{
  if(isStr(var))
    {
      str_erase(var);
      return var;
    }
 if(str_map.find(var)==str_map.end())
   {
     if(para_str.find(var)==para_str.end())
       {
         throw "该变量未定义";

       }
     else
       {
         return para_str[var];
       }
   }
 else
   {
     return str_map[var];
   }
}
void Interpreter::Variable_get(string var,string &str,int &Int,map<string,string>&var_map_type,map<string,string>&str_map,map<string,int>&int_map)
{

  if(var_map_type.find(var)!=var_map_type.end())
    {
     string var_type=var_map_type[var];
     if(var_type==Str_IN){
         Int=int_map[var];
       }
     if(var_type==Int_IN)
       {
         str=str_map[var];

       }
    }
  else if(para_type.find(var)!=para_type.end())
    {
      string var_type=para_type[var];
      if(var_type==Str_IN){
          Int=para_Int[var];
        }
      if(var_type==Int_IN)
        {
          str=para_str[var];
        }

    }
  else
    {
      throw "变量未定义";
    }

}
void Interpreter::implement(string code,map<string,string>&var_map_type,map<string,string>&str_map,map<string,int>&int_map) //其他的函数调用，变量定义匹配
{
  smatch st1;
  regex func_impt("\\s*(\\S+)\\((.*?)\\)"); //匹配函数调用
  regex variable_re("\\s*(整型|字符串)\\s(\\w+)");  //匹配变量定义
  regex Variable_inte_re("\\s*(整型|字符串)\\s(\\w+)=(\\S+)"); //匹配变量定义同时赋值
  regex Variable_ass("\\s*(\\w+)=(\\w+)"); //匹配变量赋值
  regex print_re("\\s*打印\\((\\S+)\\)");//匹配打印
  regex operation_re("\\s*(\\w+)=(\\S+)"); //运算匹配
   if(regex_match(code,st1,func_impt)&&st1[1]!="打印")  //匹配到函数调用
    {
      string impt_code;

      //st1[1];     //函数名
      //st1[2]     //参数内容
      string fun_name=st1[1];
      impt_code=fun_list[st1[1]];
      string pre=st1[2];

      if(impt_code!="")
        {

          fun_inte(st1[1],impt_code,pre);  //该函数存在，为定义函数转到定义函数调用
        }
      else
        {

         built_func(st1[1],pre,var_map_type,str_map,int_map);    //没有找到，函数为内部函数，转到内部函数调用
        }
    }
  else if(regex_match(code,st1,variable_re)) //匹配变量定义
    {
      Variable_matching(st1[1],st1[2],var_map_type);

    }
  else if(regex_match(code,st1,Variable_inte_re)) //匹配到v变量定义，并且赋值
    {
      string var_type=st1[1];
      string var_name=st1[2];
      string value=st1[3];
      Variable_matching(var_type,var_name,var_map_type);
      if (var_type==Str_IN)
        {
          Variable_inte(var_name,str_map,value);
        }
      else if(var_type==Int_IN)
        {
          Variable_inte(var_name,int_map,value);
        }

    }

  else if(regex_match(code,st1,Variable_ass))  //匹配赋值
    {
      string var_name=st1[1];
      string value=st1[2];
      string var_type=var_map_type[var_name];
      if(var_type.empty())
        {
          var_type=para_type[var_name];
        }
      if(var_type==Str_IN)
        {
           Variable_inte(var_name,str_map,value);
        }
      else if(var_type==Int_IN)
        {
           Variable_inte(var_name,int_map,value);
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
       else if(var_map_type.find(val)!=var_map_type.end())
         {

           string var_type=var_map_type[val];

           if(var_type==Str_IN)
             {
               if(str_map.find(val)!=str_map.end())
                 {
                   print(str_map[val]);
                 }
               else
                 {


                   throw "未初始化的变量";
                 }
             }
           else if(var_type==Int_IN)
             {
               if(int_map.find(val)!=int_map.end())
                 {

                   print(int_map[val]);
                 }
               else
                 {


                    throw "未初始化的变量";
                 }

               }


     }
       else if(para_type.find(val)!=para_type.end()) //未匹配到传递的变量map，使用全局的
         {
           string var_type=para_type[val];

           if(var_type==Str_IN)
             {
               if(para_str.find(val)!=para_str.end())
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
               if(para_Int.find(val)!=para_Int.end())
                 {

                   print(para_Int[val]);
                 }
               else
                 {


                    throw "未初始化的变量";
                 }

               }


         }

       else
         {


          throw "未定义的变量";
         }
     }
   else if(regex_match(code,st1,operation_re))
     {
       int type_flag=var_Is_defined(st1[1],var_map_type);
       string var_name=st1[1];
       if(type_flag==3)
         {
            throw "变量未定义";
         }
       else if(type_flag==1)
         {
           string var_type=var_map_type[var_name];
           if(var_type==Str_IN)
             {
              str_map[var_name]=operation_str(st1[2],var_map_type,str_map,int_map);
             }
           else if(var_type==Int_IN)
             {
               int_map[var_name]=operation_int(st1[2],var_map_type,str_map,int_map);

             }
         }
       else if(type_flag==2)
         {
           string var_type=para_type[var_name];
           if(var_type==Str_IN)
             {
              para_str[var_name]=operation_str(st1[2],var_map_type,str_map,int_map);
             }
           else if(var_type==Int_IN)
             {
               para_Int[var_name]=operation_int(st1[2],var_map_type,str_map,int_map);

             }

         }




     }
}
string Interpreter::operation_str(string code,map<string,string>type_map,map<string,string>str_map,map<string,int>int_map)
{
  string reutn_str;
   string str_num;
  for(int i=0;i<code.size();i++)
    {

      if(code[i]=='+'||code[i]=='-'||code[i]=='*'||code[i]=='/')
      {

         string R_str_num=get_Left_value(code,i);

         if(!reutn_str.empty())
           {

             switch (code[i])
               {
               case '+':
                 reutn_str=reutn_str+Variable_Str(R_str_num,str_map);
                 break;
               case '-':
                 throw "字符类型不支持—操作符";
                 break;
                case '*':
                throw "字符类型不支持*操作符";
                 break;
               case '/':
                throw "字符类型不支持/操作符";
                break;
               }

           }
         else
           {

            switch (code[i])
              {
              case '+':
                reutn_str=Variable_Str(str_num,str_map)+Variable_Str(R_str_num,str_map);
                break;
              case '-':
              throw "字符类型不支持—操作符";
                break;
               case '*':
               throw "字符类型不支持*操作符";
                break;
              case '/':
               throw "字符类型不支持/操作符";
               break;
              }

           }

      str_num="";
      }
      else
        {
          str_num=str_num+code[i];
        }

    }
 return reutn_str;
}

int Interpreter::operation_int(string code,map<string,string>type_map,map<string,string>str_map,map<string,int>int_map)
{
  int reutn_num;
   string str_num;
  for(int i=0;i<code.size();i++)
    {

      if(code[i]=='+'||code[i]=='-'||code[i]=='*'||code[i]=='/')
      {

         string R_str_num=get_Left_value(code,i);

         if(reutn_num)
           {

             switch (code[i])
               {
               case '+':
                 reutn_num=reutn_num+Variable_INT(R_str_num,int_map);
                 break;
               case '-':
                 reutn_num=reutn_num-Variable_INT(R_str_num,int_map);
                 break;
                case '*':
                 reutn_num=reutn_num*Variable_INT(R_str_num,int_map);
                 break;
               case '/':
                reutn_num=reutn_num/Variable_INT(R_str_num,int_map);
                break;
               }

           }
         else
           {

            switch (code[i])
              {
              case '+':
                reutn_num=Variable_INT(str_num,int_map)+Variable_INT(R_str_num,int_map);
                break;
              case '-':
               reutn_num=Variable_INT(str_num,int_map)-Variable_INT(R_str_num,int_map);
                break;
               case '*':
               reutn_num=Variable_INT(str_num,int_map)*Variable_INT(R_str_num,int_map);
                break;
              case '/':
               reutn_num=Variable_INT(str_num,int_map)/Variable_INT(R_str_num,int_map);
               break;
              }

           }

      str_num="";
      }
      else
        {
          str_num=str_num+code[i];
        }

    }
 return reutn_num;
}
string Interpreter::get_Left_value(string str,int &x)
{
  string str_num;
 for(int i=x+1 ;i<str.size();i++)
   {

     if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')
     {
         return str_num;
     }
     else
       {
          str_num=str_num+str[i];
       }

}
 return str_num;
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
 int O_Int;
  if(! isnum(value))
    {
      Int_=int_map[value];
      O_Int=para_Int[value];
      if(int_map.find(value)!=int_map.end())
        {

        int_map[var_name]=Int_;
        }
      else if(para_Int.find(value)!=para_Int.end())
        {
          int_map[var_name]=O_Int;
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
      string O_str=para_str[value];
      if(str_map.find(value)!=str_map.end())
        {
     str_map[var_name]=value_;


        }
      else if(para_str.find(value)!=para_str.end())
        {
          str_map[var_name]=O_str;
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
  regex end("\\s*\\}");
  regex if_re("\\s*如果(.*?)");
  regex for_re("\\s*循环(.*?)");
  while(true)
    {

      getline(f,code);
      str=str+'\n'+code;
      if(regex_match(code,st1,if_re))
        {
          x++;
        }
      else if(regex_match(code,st1,for_re))
        {
          x++;
        }
      else if(regex_match(code,st1,end)&&x<=0)
        {
          break;
        }
      else if(regex_match(code,st1,end))
        {
         x--;
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
  map<string,string>pre_type;
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
                pre_type[pre_l[i]]=Int_IN;
               pre_int[pre_l[i]]=str_to_int(pre_vec[i]); //将整型参数放到定义函数参数列表当中

       }
     else if(isStr(pre_vec[i])) //给定义函数传递的是字符串
       {
         pre_type[pre_l[i]]=Str_IN;
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
  code=fun_list[fun_name];
  vector<string> fun_code_list=split(code,'\n');
  regex if_re("如果(.*?)");
  regex for_re("循环(.*?)");
  smatch st1;
  for(int i=0;i<fun_code_list.size();i++)
    {
      if(regex_match(fun_code_list[i],st1,if_re))
        {

          i++;
          string if_code=get_if_code(fun_code_list,i);

          if_init(if_code,st1[1],pre_type,pre_str,pre_int);



        }
      else if(regex_match(fun_code_list[i],st1,for_re))
        {
           i++;
           string for_code=get_for_code(fun_code_list,i);
           for_init(for_code,st1[1],pre_type,pre_str,pre_int);
        }
      else
        {
      implement(fun_code_list[i],pre_type,pre_str,pre_int);
        }


    }

}
void Interpreter::get_pre(string pre_nmae,int &Int,string &str)
{

}
void Interpreter::built_func(string func_name,string pre,map<string,string>type_map,map<string,string>str_map,map<string,int>int_map) //内部函数调用
{
  vector<string>ver_pre=split(pre,',');
  int pre_size=ver_pre.size();
  cout<<pre_size<<endl;
  cout<<"执行内部函数"<<func_name<<endl;
  if(func_name=="左键单击")
    {
      if(pre_size!=2)
        {
          throw "需要参数是两个,请检查参数";
        }
      else
        {
          int x=Variable_INT(ver_pre[0],int_map);
          int y=Variable_INT(ver_pre[1],int_map);
          oper->L_Click(x,y);
        }

    }
  else if(func_name=="左键双击")
    {
      if(pre_size!=2)
        {
          throw "需要参数是两个,请检查参数";
        }
      else
        {
          int x=Variable_INT(ver_pre[0],int_map);
          int y=Variable_INT(ver_pre[1],int_map);
          oper->L_Click_d(x,y);
        }
    }
  else if(func_name=="匹配单击")
    {
      if(pre_size!=1)
        {
          throw "需要参数是一个,请检查参数";
        }
      else
        {
          string path=Variable_Str(ver_pre[0],str_map);

          oper->Match_Click(path,2);
        }
    }
  else if(func_name=="匹配双击")
    {
      if(pre_size!=1)
        {
          throw "需要参数是一个,请检查参数";
        }
      else
        {
          string path=Variable_Str(ver_pre[0],str_map);

          oper->Match_Click(path,1);
        }
    }
  else if(func_name=="匹配移动")
    {
      if(pre_size!=1)
        {
          throw "需要参数是一个,请检查参数";
        }
      else
        {
          string path=Variable_Str(ver_pre[0],str_map);

          oper->Math_Move(path);
        }
    }
  else if(func_name=="右键单击")
    {
      if(pre_size!=2)
        {
          throw "需要参数是两个,请检查参数";
        }
      else
        {
          int x=Variable_INT(ver_pre[0],int_map);
          int y=Variable_INT(ver_pre[1],int_map);
          oper->R_Click(x,y);
        }

    }
  else if(func_name=="右键双击")
    {
      if(pre_size!=2)
        {
          throw "需要参数是两个,请检查参数";
        }
      else
        {
          int x=Variable_INT(ver_pre[0],int_map);
          int y=Variable_INT(ver_pre[1],int_map);
          oper->R_click_d(x,y);
        }

    }
  else if(func_name=="输入字符")
    {
      {
        if(pre_size!=1)
          {
            throw "需要参数是一个,请检查参数";
          }
        else
          {
            string str=Variable_Str(ver_pre[0],str_map);

            oper->input(str);
          }
      }
    }
  else if(func_name=="键盘按键")
    {
      {
        if(pre_size!=1)
          {
            throw "需要参数是一个,请检查参数";
          }
        else
          {
            string str=Variable_Str(ver_pre[0],str_map);
            char p=str[0];
            oper->Press_one(p);
          }
      }
    }
  else if(func_name=="按键按下")
    {
      {
        if(pre_size!=1)
          {
            throw "需要参数是一个,请检查参数";
          }
        else
          {
            string str=Variable_Str(ver_pre[0],str_map);
            char p=str[0];
            oper->Press_lower(p);
          }
      }
    }
  else if(func_name=="按键弹起")
    {

        if(pre_size!=1)
          {
            throw "需要参数是一个,请检查参数";
          }
        else
          {
            string str=Variable_Str(ver_pre[0],str_map);
            char p=str[0];
            oper->Bounce(p);
          }


    }
  else if(func_name=="休眠")
    {
      if(pre_size!=1)
        {
          throw "需要参数是一个,请检查参数";
        }
      else
        {
          int s=Variable_INT(ver_pre[0],int_map);

          oper->m_sleep(s);
        }

    }
  else if(func_name=="打开浏览器")
    {

      if(pre_size!=1)
        {
          throw "需要参数是一个,请检查参数";
        }
      else
        {
          string s=Variable_Str(ver_pre[0],str_map);

          oper->open_web(s);
        }
    }
  else if(func_name=="xpath点击")
    {
      if(pre_size!=1)
        {
          throw "需要参数是一个,请检查参数";
        }
      else
        {
          string s=Variable_Str(ver_pre[0],str_map);

          oper->xpath_cilck(s);
        }
    }
 else if(func_name=="ID点击")
    {
      if(pre_size!=1)
              {
                throw "需要参数是一个,请检查参数";
              }
            else
              {
                string s=Variable_Str(ver_pre[0],str_map);

                oper->id_click(s);
              }
    }
  else if(func_name=="xpath输入")
    {
      if(pre_size!=2)
              {
                throw "需要参数是两个个,请检查参数";
              }
            else
              {
                string s=Variable_Str(ver_pre[0],str_map);
                string s2=Variable_Str(ver_pre[1],str_map);
                oper->xpath_input(s,s2);
              }
    }
  else if(func_name=="id输入")
    {
      if(pre_size!=2)
              {
                throw "需要参数是两个个,请检查参数";
              }
            else
              {
                string s=Variable_Str(ver_pre[0],str_map);
                string s2=Variable_Str(ver_pre[1],str_map);
                oper->id_input(s,s2);
              }
    }
  else
    {
      throw "不存在的函数";
    }
}
vector<string> Interpreter::split(string str,char pi) //字符串分割函数
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
