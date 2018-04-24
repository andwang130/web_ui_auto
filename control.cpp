#include<control.h>
#pragma comment (lib, "User32.lib") //使用mouse_event需要的链接库
void CControl::mouse_move(int x,int y)
{
 SetCursorPos(x,y);//鼠标移动
}
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


void CControl::Key_input(char str,int sp) //按下一个键设置了延迟抬起时间，会自动抬起
{
      keybd_event(str,0,0,0);//按下这个键
      Sleep(sp);
      keybd_event(str,0,KEYEVENTF_KEYUP,0);//松开这个键
}
void CControl::Key_donw(char str) //按下一个键，不抬起
{
  keybd_event(str,0,0,0);
}
void CControl::Key_up(char str)
{
   keybd_event(str,0,KEYEVENTF_KEYUP,0);//松开这个键
}

void CControl::input_string(string str)
{
  HWND hwnd;

  OpenClipboard(NULL);   //打开剪切版
  HANDLE h = GetClipboardData(CF_TEXT); //获得剪切版数据
  EmptyClipboard();//清空剪切版
  HANDLE hHandle = GlobalAlloc(GMEM_FIXED, str.size()*4);//分配内存
  char * p=(char*) GlobalLock(hHandle);//锁定内存，返回锁定的内存的收地址,保存期间剪切版内容不变,p指向的是hHandel的首地址

  strcpy(p,str.data());//将str的内容复制到p的指针
  cout<<p<<endl;
   GlobalUnlock(hHandle);
  SetClipboardData(CF_TEXT,hHandle);//这时候hHandel的内容已经复制为str的内容了

  CloseClipboard();//关闭剪切版

  keybd_event(17,0,0,0);//按下 ctrl键
  keybd_event(86,0,0,0);//按下V键GlobalUnlock(hHandle); //解除锁定
  Sleep(200);//休眠200毫秒

  keybd_event(17,0,KEYEVENTF_KEYUP,0);//松开ctrl键
  keybd_event(86,0,KEYEVENTF_KEYUP,0);//松开V键。完成复制操作
//  SetClipboardData(CF_TEXT,h); //把剪切版内容设置回去


}

