#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QString>
#include<string>
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
