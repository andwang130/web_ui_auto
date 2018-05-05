#include<specific.h>
/*************************************************
整合操作类的cpp文件，
**************************************************/
Integration::Integration()
{
  Mopen_cv=new CMyOpencv(); //实例化opencv操作类
  Contr=new CControl(); //实例鼠标键盘操作类
}
Integration::~Integration()
{  //虚构函数，把new 出来的对象,delete
  delete Mopen_cv;
  delete Contr;
}
void Integration::Match_Click(string path, const int click_falg)
{
  /*************************************************
  使用opencv进行定位，然后难道图片对比的X,Y，进行点击操作
  **************************************************/
  Mat img=Mopen_cv->open_Imge(path); //打开图片
  Mat tem=Mopen_cv->current();//获取屏幕截图的Mat
  int x,y; //初始化X,Y
  double flag;
  Mopen_cv->Img_contrast(img,tem,x,y,flag); //图片对比，获得X,Y值
  x=x+img.cols/2;
  y=y+img.rows/2;
  if(click_falg==IN_DOUBLE)
    {
  Contr->mouse_left_double_click(x,y); //点击
    }
  else if(click_falg==IN_ONE)
    {
      Contr->mouse_left_click(x,y); //点击
    }

}
void Integration::Math_Move(string path)
{
  Mat img=Mopen_cv->open_Imge(path); //打开图片
  Mat tem=Mopen_cv->current();//获取屏幕截图的Mat
  cout<<img.size<<endl;
  cout<<tem.size<<endl;
  int x,y; //初始化X,Y
  double flag;
  Mopen_cv->Img_contrast(img,tem,x,y,flag); //图片对比，获得X,Y值
  x=x+img.cols/2;
  y=y+img.rows/2;
  if(flag>=0.9)
    {

  Contr->mouse_move(x,y);
    }
}
void Integration::L_Click(int x,int y){
  Contr->mouse_left_click(x,y);
}
void Integration::L_Click_d(int x,int y)//右键双击
{
  Contr->mouse_left_double_click(x,y);

}
void Integration::R_Click(int x,int y)
{
  Contr->mouse_right_click(x,y);

}//右键单击
void Integration::R_click_d(int x,int y)
{
  Contr->mouse_right_double_click(x,y);
}
void Integration::Press_one(char str)//按一个键，自动会谈起
{
  Contr->Key_input(str);
}
void Integration::Press_lower(char str)//按下一个键不弹起
{
  Contr->Key_donw(str);
}
void Integration::Bounce(char str)//弹起一个键
{
  Contr->Key_up(str);
}
void Integration::input(string str)//输入字符串
{
  Contr->input_string(str);
}
void Integration::m_sleep(int s)
{
  Sleep(s);
}
void Integration:: open_web(string url)
{
  Cweboper *webop=new Cweboper(url);
  web_list.push_back(*webop);
  web_now=webop;
}
int Integration::web_num()
{
  return web_list.size();
}
void Integration::switch_web(int i)
{
  if(i>web_num()||i<0)
    {
      throw "超越界限";
    }
  else
    {
      *web_now=web_list[i];
    }
}
void Integration::xpath_cilck(string path)
{
  web_now->click_PATH(path);
}//点击一个元素,通过xpath定位的

void Integration::id_click(string path)
{
  web_now->click_id(path);
}
void Integration::xpath_input(string path,string str)
{
  web_now->input_PATH(path,str);

}
void Integration::id_input(string path,string str)
{
  web_now->input_id(path,str);
}

