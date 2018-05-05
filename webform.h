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

  ~webForm();
protected:
 void resizeEvent(QResizeEvent *event);//窗口大小修改事件
private:
  Ui::webForm *ui;

};

#endif // WEBFORM_H
