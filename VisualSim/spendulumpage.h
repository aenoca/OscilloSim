#ifndef SPENDULUMPAGE_H
#define SPENDULUMPAGE_H

#include "pageosc.h"

struct Values_SP
{
    double m;
    double l;
    double k;

    Vector a;
    Vector o;
    Vector P;
    Vector Q;
};

class SPendulumPage : public PageOsc
{
    Q_OBJECT
private:
    //!widgets for mass
    QLabel *m;
    QDoubleSpinBox *mass;

    //!widgets for spring constant
    QLabel *k;
    QDoubleSpinBox *cst;

    //!widgets for zero-length
    QLabel *l;
    QDoubleSpinBox *len;

    //!values initialized with init
    Values_SP v;

public slots:
    //!override of addOsc
    virtual void addOsc(GLWidget &w) override;

public:
    SPendulumPage();

    virtual ~SPendulumPage() {}
    //!updates values of v
    virtual void init() override;

};

#endif // SPENDULUMPAGE_H
