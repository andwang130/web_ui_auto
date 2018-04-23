#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QString>
using namespace cv;
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_pushButton_clicked()
{
//   QString str=ui->lineEdit->text();//Qstring 转换成数字,如果无法转换，会返回0
//   QStringList strlist=str.split(',');
//   qDebug()<<strlist<<endl;
//   int x=strlist[0].toInt();
//   int y=strlist[1].toInt();
//   con.mouse_left_click(x,y);
//   con.input_string("ssdsds");
   Mat s=MYcv.current();
   Mat img=MYcv.open_Imge("D:\\me\\42.png");
   Mat tem=MYcv.open_Imge("D:\\me\\48.png");

   cout<<s.elemSize()<<endl;;
    cout<<img.elemSize()<<endl;
    cout<<tem.elemSize()<<endl;
    cout<<s.depth()<<endl;
    cout<<img.depth()<<endl;
    cout<<s.type()<<endl;
    cout<<img.type()<<endl;
    cout<<tem.type()<<endl;
   imshow("2",s);
   int x,y=MYcv.Img_contrast(img,s);
   //cout<<x<<y<<endl;

}
