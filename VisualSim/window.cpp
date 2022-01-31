#include "window.h"

#include "homepage.h"
#include "page.h"

Window::Window()
    : page1(new Homepage), page2(new Page)
{
    //!define the icon of the window
   QWidget::setWindowIcon(QIcon(QPixmap(":/Icone.jpg")));

   //!add two pages to the window
   addWidget(page1);
   addWidget(page2);

   //!show the window
   show();

   //!if buttons are clicked, then do
   QObject::connect(page1->getNext(), SIGNAL(clicked()), this, SLOT(next_clicked()));
   QObject::connect(page2->getBack(), SIGNAL(clicked()), this, SLOT(back_clicked()));

   //! size of window is the size of the first page
   setFixedSize(page1->size());
   //setBaseSize(page1->size());
}

void Window::next_clicked()
{
    this->setCurrentIndex(1);
}

void Window::back_clicked()
{
    this->setCurrentIndex(0);
}
