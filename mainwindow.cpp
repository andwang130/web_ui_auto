#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QString>
#include<string>
#include<QDebug>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  integ=new Interpreter();
}

MainWindow::~MainWindow()
{
  delete ui;
  delete integ;
  Psti=0;
}


void MainWindow::on_pushButton_clicked()
{
  try{
   integ->run("C:\\Users\\me\\Desktop\\plan.txt");
  }
  catch(const char* e)
  {
    cout<<e<<endl;
  }

}


void MainWindow::on_Lclick_Button_clicked()
{
    QString x=ui->Lclick_x->text();  //获得输入框的值
    QString y=ui->Lclick_y->text();
    QString code=QString("左键单击(%1,%2)\n").arg(x).arg(y); //QString 的拼接方法，
    ui->code_text->textCursor().insertText(code);//当前光标位置插入

}



void MainWindow::on_code_text_cursorPositionChanged() //QTextEdit类焦点位置改变事件
{
    QTextCursor tc=ui->code_text->textCursor();  //获得到文本框的焦点
    Psti=tc.position();   //获取位置的信息

}


void MainWindow::on_Lclick_Button_d_clicked()
{
  QString x=ui->Lclick_x_d->text();  //获得输入框的值
  QString y=ui->Lclick_y_d->text();
  QString code=QString("左键双击(%1,%2)\n").arg(x).arg(y); //QString 的拼接方法，
  ui->code_text->textCursor().insertText(code);//当前光标位置插入
}

void MainWindow::on_Rclick_Button_clicked()
{
  QString x=ui->Rclick_x->text();  //获得输入框的值
  QString y=ui->Rclick_y->text();
  QString code=QString("右键单击(%1,%2)\n").arg(x).arg(y);
  ui->code_text->textCursor().insertText(code);
}

void MainWindow::on_Rclick_Button_d_clicked()
{
  QString x=ui->Rclick_x_d->text();  //获得输入框的值
  QString y=ui->Rclick_y_d->text();
  QString code=QString("右键双击(%1,%2)\n").arg(x).arg(y);
  ui->code_text->textCursor().insertText(code);
}
