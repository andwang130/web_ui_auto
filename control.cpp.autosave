#include<control.h>

#pragma comment (lib, "User32.lib") //使用mouse_event需要的链接库

void CControl::mouse_left_click(int x,int y)
{

  SetCursorPos(x,y);//鼠标移动
  mouse_event(MOUSEEVENTF_LEFTDOWN |MOUSEEVENTF_LEFTUP,0,0,0,0);//鼠标左键按下和松开两个事件的组合即一次单击：0,0,0,0为当前位置
}
void CControl::mouse_left_click()//重构函数，不传参数，在原地点击了
{

  mouse_event(MOUSEEVENTF_LEFTDOWN |MOUSEEVENTF_LEFTUP,0,0,0,0);
}
//鼠标移动到x,y点击
void CControl::mouse_right_click(int x,int y)
{
  SetCursorPos(x,y);
  mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP,0,0,0,0);
}
//鼠标右键原地点击
void CControl::mouse_right_click()
{
  mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP,0,0,0,0);
}


//鼠标中间点击
void CControl::mouse_Middle_click(int x,int y)
{
  SetCursorPos(x,y);
  mouse_event(MOUSEEVENTF_RIGHTUP|MOUSEEVENTF_MIDDLEUP,0,0,0,0);
}
//鼠标中间原地点击
void CControl::mouse_Middle_click()
{
  mouse_event(MOUSEEVENTF_RIGHTUP|MOUSEEVENTF_MIDDLEUP,0,0,0,0);

}

//左键双击
void CControl::mouse_left_double_click(int x ,int y)
{
  SetCursorPos(x,y);//鼠标移动
  mouse_event(MOUSEEVENTF_LEFTDOWN |MOUSEEVENTF_LEFTUP,0,0,0,0);
  mouse_event(MOUSEEVENTF_LEFTDOWN |MOUSEEVENTF_LEFTUP,0,0,0,0); //双击
}
//左键原地双击
void CControl::mouse_left_double_click()
{

  mouse_event(MOUSEEVENTF_LEFTDOWN |MOUSEEVENTF_LEFTUP,0,0,0,0);
  mouse_event(MOUSEEVENTF_LEFTDOWN |MOUSEEVENTF_LEFTUP,0,0,0,0); //双击
}

//右键双击
void CControl::mouse_right_double_click(int x,int y)
{
  SetCursorPos(x,y);//鼠标移动
  mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP,0,0,0,0);
  mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP,0,0,0,0);
}

//原地右键双击
void CControl::mouse_right_double_click()
{
  mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP,0,0,0,0);
  mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP,0,0,0,0);
}
void CControl::Key_input(QString str,int sp)
{
  for(int i=0;i<str.size();i++)
    {
      int k=str.at(i).toLatin1();
      qDebug()<<k<<endl;
      keybd_event(k,0,0,0);//按下这个键
      keybd_event(k,0,KEYEVENTF_KEYUP,0);//松开这个键
      Sleep(sp);

    }

}

