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
  this->showMaximized(); //最大化
  webview->load(Qurl);
   webview->show();
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
