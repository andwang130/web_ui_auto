#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QString>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  integ=new Integration();
}

MainWindow::~MainWindow()
{
  delete ui;
  delete integ;
}


void MainWindow::on_pushButton_clicked()
{

   integ->Match_Click("D:\\me\\42.png");

}
