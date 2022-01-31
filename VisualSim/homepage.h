#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QtWidgets>

//!homepage class
class Homepage : public QWidget
{
private:
    //!image of the homepage
    QLabel *image;

    //!go to next page
    QPushButton *next;

public:
    Homepage();

    virtual ~Homepage(){}

    //! used for signal that button was pressed.
    const QPushButton* getNext();
};

#endif // HOMEPAGE_H
