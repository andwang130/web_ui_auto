#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<Qdebug>
#include<QString>
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  CControl con;
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   QString str=ui->lineEdit->text();//Qstring 转换成数字,如果无法转换，会返回0

   qDebug()<<str<<endl;
   QStringList strlist=str.split(',');
   qDebug()<<strlist<<endl;
   int x=strlist[0].toInt();
   int y=strlist[1].toInt();
   con.mouse_left_click(x,y);
   con.input_string("ssdsds");
}
