#ifndef PAGEOSC_H
#define PAGEOSC_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QLayout>

#include <array>
#include <vector>

#include "glwidget.h"
#include "../Simulation/vector.h"
#include "../Oscillators/oscillator.h"

class PageOsc : public QWidget
{
    Q_OBJECT
protected:
    //!Layout of a PageOsc
    QHBoxLayout *box;

    //!image of osc
    QLabel *image;

    //!layout added inside box
    QGridLayout *values;

//    //! Widgets pour récupérer la valeur de la masse
//    QLabel *m;
//    QDoubleSpinBox *mass;

//    //! Widgets pour récupérer la valeur des frottements
//    QLabel *fr;
//    QDoubleSpinBox *frott;

    //!widgets to get vectors A and O
    QLabel *a;
    std::array<QDoubleSpinBox*, 3> dir;

    QLabel *o;
    std::array<QDoubleSpinBox*, 3> center;

    //!widgets to get vectors P and Q
    QLabel *P;
    std::vector<QDoubleSpinBox*> pos;

    QLabel *Q;
    std::vector<QDoubleSpinBox*> vel;

    //!button used to add osc to window
    QPushButton *add;

    //!button used to remove last added osc
    QPushButton *remove;
public slots:
    //!method to add osc to window, specific to each osc
    virtual void addOsc(GLWidget & w) = 0;

public:
    //!Constructor
    PageOsc(int dim = 1);

    virtual ~PageOsc() {}

    //!returns pointer on add button
    const QPushButton* getAdd() const { return add; }

    //!returns pointer on remove button
    const QPushButton* getLess() const { return remove; }

    //!used by addOsc, initializes an instance of structure to initialize the osc
    virtual void init() = 0;
};

#endif // PAGEOSC_H
