#include "mybutton.h"
 
#include <QCoreApplication>
 
MyButton::MyButton(QWidget *parent)
   : QWidget(parent)
{
   // Create the button, make "this" the parent
   my_button = new QPushButton("My Button", this);
   // set size and location of the button
   my_button->setGeometry(QRect(QPoint(100, 100),
   QSize(200, 50)));
 
   // Connect button signal to appropriate slot
   connect(my_button, SIGNAL (released()), this, SLOT (handleButton()));
}
 
void MyButton::handleButton()
{
   // change the text
   my_button->setText("Pause");
   // resize button
   my_button->resize(100,100);
}
