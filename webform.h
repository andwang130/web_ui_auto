#ifndef WEBFORM_H
#define WEBFORM_H
#include<QtWebEngineWidgets/QWebEngineView>
#include <QWidget>
#include<QString>
using namespace std;
namespace Ui {
  class webForm;
}

class webForm : public QWidget
{
  Q_OBJECT

public:
   QWebEngineView *webview;
  explicit webForm(QWidget *parent = 0,QString url="http://www.carzy.wang/");
  void is_load();//阻塞函数，判断当前页面是否加载完成，没有加载完成将会一直循环，直到加载完成
  bool load_flag; //是否加载完成标识
  ~webForm();
private slots:
  void webfind_load(bool ok); //接受加载完成信号
  void load_progress(int por);//加载进度
protected:
 void resizeEvent(QResizeEvent *event);//窗口大小修改事件
private:
  Ui::webForm *ui;


};

#endif // WEBFORM_H
