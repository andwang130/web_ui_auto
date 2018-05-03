#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<specific.h>
#include<interpreter.h>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();


  void on_Lclick_Button_clicked();


  void on_code_text_cursorPositionChanged();


  void on_Lclick_Button_d_clicked();

  void on_Rclick_Button_clicked();

  void on_Rclick_Button_d_clicked();

  void on_input_key_butto_clicked();

  void on_input_str_butto_clicked();

  void on_Button_path_mv_clicked();

  void on_Math_Move_butto_clicked();

  void on_Button_path_click_clicked();

  void on_Math_click_butto_clicked();

  void on_while_butto_clicked();

private:
  Ui::MainWindow *ui;
  Interpreter *integ;
  int Psti;

};

#endif // MAINWINDOW_H
