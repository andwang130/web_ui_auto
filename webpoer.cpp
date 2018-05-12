#include<weboper.h>
#include<iostream>
using namespace std;
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
void Cweboper::click_PATH(string path) //通过xpath来定位点击
{
 QString qpath=QString(QString::fromLocal8Bit(path.c_str()));
  QString js=QString("$('%1').click()").arg(qpath);
  webviwe->is_load();

  webviwe->webview->page()->runJavaScript(js,[](const QVariant v){qDebug()<<v<<endl;});

}
 void Cweboper::click_id(string path)//通过ID点击
{ QString qpath=QString(QString::fromLocal8Bit(path.c_str()));
  QString js=QString("document.getElementById('%1').click()").arg(qpath);
     webviwe->is_load(); //等待加载函数
  webviwe->webview->page()->runJavaScript(js);
}

void Cweboper::input_PATH(string path,string str)
{  QString qpath=QString(QString::fromLocal8Bit(path.c_str()));
   QString qstr=QString(QString::fromLocal8Bit(str.c_str()));
  QString js=QString("document.getElementById('%1').val('%2')").arg(qpath).arg(qstr);
    webviwe->is_load(); //等待加载函数
  webviwe->webview->page()->runJavaScript(js);
}
void Cweboper::input_id(string path,string str)
{     qDebug()<<"执行输入"<<endl;
  QString qpath=QString(QString::fromLocal8Bit(path.c_str()));
       QString qstr=QString(QString::fromLocal8Bit(str.c_str()));
       QString js=QString("document.getElementById('%1').value='%2'").arg(qpath).arg(qstr);
       cout<<str<<endl;
       webviwe->is_load(); //等待加载函数
       webviwe->webview->page()->runJavaScript(js);

}
QWebEngineView *QWebEngineView::createWindow(QWebEnginePage::WebWindowType type)
{
  Q_UNUSED(type);
  return this;
}
