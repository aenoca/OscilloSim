#include "homepage.h"

Homepage::Homepage()
    : image(new QLabel(this)), next(new QPushButton("Next"))
{
    //we define the homepage image
    QPixmap p = QPixmap(":/homepage.jpg");
    image->setPixmap(p);

    QGridLayout *grid = new QGridLayout(image);
    grid->addWidget(next, 1, 1, Qt::AlignRight | Qt::AlignBottom);

    setFixedSize(1125, 719);
}

const QPushButton* Homepage::getNext()
{
    return next;
}
