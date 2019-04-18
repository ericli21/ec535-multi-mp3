#ifndef MYBUTTON_H
#define MYBUTTON_H
 
#include <QMainWindow>
#include <QPushButton>
 
namespace Ui {
   class MyButton;
}
 
class MyButton : public QWidget
{
   Q_OBJECT
public:
   explicit MyButton(QWidget *parent = 0);
private slots:
   void handleButton();
private:
   QPushButton *my_button;
};
 
#endif // MAINWINDOW_H
