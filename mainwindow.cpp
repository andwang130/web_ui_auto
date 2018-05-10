#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QString>
#include<string>
#include<QDebug>
#include<QFileDialog>
#include<spapidef.h>
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

   integ->run("C:/Users/me/Desktop/plan.txt");
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

void MainWindow::on_input_key_butto_clicked()
{
    QString key=ui->key_input->text();
    QString code=QString("键盘按键(\"%1\")\n").arg(key);
    ui->code_text->textCursor().insertText(code);
}

void MainWindow::on_input_str_butto_clicked()
{
    QString str=ui->str_input->text();
    QString code=QString("输入字符(\"%1\")\n").arg(str);
    ui->code_text->textCursor().insertText(code);
}

void MainWindow::on_Button_path_mv_clicked()
{
    QFileDialog *filedialog=new QFileDialog(this);//实例一个文件选择对话框
    filedialog->setWindowTitle(tr("选择图片"));  //设置窗口的标题
    filedialog->setDirectory(".");//设置默认路径
    filedialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));  //设置文件过滤器
    if(filedialog->exec()) //exec显示，判断是否打开成功
    {
     QStringList fileName=filedialog->selectedFiles();//获取到文件路径
     if(!fileName.empty())
       {
     ui->img_mv_path->setText(fileName[0]);
       }
    }
    delete filedialog;

}

void MainWindow::on_Math_Move_butto_clicked()
{
    QString path=ui->img_mv_path->text();
    QString code=QString("匹配移动(\"%1\")\n").arg(path);
    ui->code_text->textCursor().insertText(code);

}



void MainWindow::on_Button_path_click_clicked()
{
  QFileDialog *filedialog=new QFileDialog(this);//实例一个文件选择对话框
  filedialog->setWindowTitle(tr("选择图片"));  //设置窗口的标题
  filedialog->setDirectory(".");//设置默认路径
  filedialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));  //设置文件过滤器
  if(filedialog->exec()) //exec显示，判断是否打开成功
  {
   QStringList fileName=filedialog->selectedFiles();//获取到文件路径
   if(!fileName.empty())
     {
   ui->img_click_path->setText(fileName[0]);
     }
  }
  delete filedialog;
}

void MainWindow::on_Math_click_butto_clicked()
{
  QString path=ui->img_click_path->text();
  QString code=QString("匹配点击(\"%1\")\n").arg(path);
  ui->code_text->textCursor().insertText(code);
}

void MainWindow::on_while_butto_clicked()
{
   QString while_num=ui->while_num->text();
   QString code=QString("循环(\%1\)\n{\n\n}\n").arg(while_num);
   ui->code_text->textCursor().insertText(code);
}
