#ifndef SPRINGPAGE_H
#define SPRINGPAGE_H

#include "pageosc.h"

//!structure to initialize a spring
struct Values_S
{
    double m;
    double fr;
    double k;

    Vector a;
    Vector o;
    Vector P;
    Vector Q;
};

class SpringPage : public PageOsc
{
    Q_OBJECT
private:
    //!widgets for mass
    QLabel *m;
    QDoubleSpinBox *mass;

    //!widgets for spring constant
    QLabel *k;
    QDoubleSpinBox *cst;

    //!widgets for friction
    QLabel *fr;
    QDoubleSpinBox *frict;

    //!values initialized with init
    Values_S v;

public slots:
    //!override of addOsc
    virtual void addOsc(GLWidget &w) override;

public:
    SpringPage();

    virtual ~SpringPage() {}
    //!updates values of v
    virtual void init() override;
};

#endif // SPRINGPAGE_H
