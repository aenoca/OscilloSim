#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <QObject>
#include <QWidget>
#include <QLayout>
//#include "accueil.h"
//#include "page.h"

class Homepage;
class Page;

//!contains homepage, and input data page
class Window: public QStackedWidget
{
    Q_OBJECT
private:
    //!homepage
    Homepage *page1;

    //!data input page
    Page *page2;

private slots:
    //!methods are called when buttons are clicked
    //!
    //!if next is clicked, goes to data input page
    void next_clicked();

    //!if back is clicked, goes to homepage
    void back_clicked();

public:
    Window();
    virtual ~Window() {}
};

#endif // WINDOW_H
