#include "webform.h"
#include "ui_webform.h"
#include<QDebug>
webForm::webForm(QWidget *parent,QString url) :
  QWidget(parent),
  ui(new Ui::webForm)
{
  QUrl Qurl(url);
  ui->setupUi(this);
   webview=new QWebEngineView(ui->widget);
   connect(webview,SIGNAL(loadFinished(bool)),this,SLOT(webfind_load(bool)));//绑定加载完成信号
   connect(webview,SIGNAL(loadProgress(int)),this,SLOT(load_progress(int)));//绑定加载进度信号
  this->showMaximized(); //最大化
  webview->load(Qurl);
   webview->show();
}
void webForm::webfind_load(bool ok)
{
 load_flag=true;
}
void webForm::load_progress(int por)
{
  if(por!=100)
    {
      load_flag=false;
      qDebug()<<por<<endl;
    }
  else
    {
      load_flag=true;
    }
}
 void webForm::is_load()
 {
   while(true)
     {
       if(load_flag==true)
         {
          break;

         }
       QApplication::processEvents();
     }
 }
void webForm::resizeEvent(QResizeEvent *event)
{
   //设置QWebEngineView大小
  webview->resize(ui->widget->width(),ui->widget->height());
}
webForm::~webForm()
{
  delete ui;
}
