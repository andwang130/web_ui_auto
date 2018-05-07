#include<weboper.h>
Cweboper::Cweboper(string url)
{
  QString Qurl=QString::fromStdString(url);
  webviwe=new webForm(0,Qurl);
  webviwe->show();

}
Cweboper::~Cweboper()
{
  delete webviwe;
}
void Cweboper::click_PATH(string path,Cweboper *pewb) //通过xpath来定位点击
{ qDebug()<<"执行点击"<<endl;
  QString qpath=QString::fromStdString(path);
  QString js=QString("$(\"%1\").click()").arg(qpath);
    //pewb->webviwe->is_load(); //等待加载函数
   //pewb->webviwe->webview->page()->runJavaScript(js);

}
 void Cweboper::click_id(string path,Cweboper *pewb)//通过ID点击
{ QString qpath=QString::fromStdString(path);
  QString js=QString("document.getElementById(\"%1\").click()").arg(qpath);
     pewb->webviwe->is_load(); //等待加载函数
  pewb->webviwe->webview->page()->runJavaScript(js);
}

void Cweboper::input_PATH(string path,string str,Cweboper *pewb)
{ QString qpath=QString::fromStdString(path);
   QString qstr=QString::fromStdString(str);
  QString js=QString("document.getElementById(\"translate-button\").val(\"%2\")").arg(qpath).arg(qstr);
    pewb->webviwe->is_load(); //等待加载函数
  pewb->webviwe->webview->page()->runJavaScript(js);
}
void Cweboper::input_id(string path,string str,Cweboper *pewb)
{      QString qpath=QString::fromStdString(path);
       QString qstr=QString::fromStdString(str);
       QString js=QString("document.getElementById(\"%1\").value=\"%2\"").arg(qpath).arg(qstr);
       pewb->webviwe->is_load(); //等待加载函数
       pewb->webviwe->webview->page()->runJavaScript(js);

}
