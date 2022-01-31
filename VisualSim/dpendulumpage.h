#ifndef DPENDULUMPAGE_H
#define DPENDULUMPAGE_H

#include "pageosc.h"

//!structure to initialize a doublependulum
struct Values_DP
{
    double m1;
    double m2;
    double l1;
    double l2;

    Vector a;
    Vector o;
    Vector P;
    Vector Q;
};

class DPendulumPage : public PageOsc
{
    Q_OBJECT
private:
    //!widgets for mass
    QLabel *m;
    QDoubleSpinBox *mass;

    //!widgets for length
    QLabel *l;
    QDoubleSpinBox *len;

    //!widgets for mass
    QLabel *m2;
    QDoubleSpinBox *mass2;

    //!widgets for length
    QLabel *l2;
    QDoubleSpinBox *len2;

    //!values initialized with init
    Values_DP v;

public slots:
  //!override of addOsc
  virtual void addOsc(GLWidget &w) override;

public:
    DPendulumPage();

    virtual ~DPendulumPage() {}
    //!updates values of v
    virtual void init() override;
};

#endif // DPENDULUMPAGE_H
