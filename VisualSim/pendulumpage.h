#ifndef PENDULUMPAGE_H
#define PENDULUMPAGE_H

#include "pageosc.h"

//!structure to initalize weightedpendulum
struct Values_P
{
    double m;
    double l;
    double fr;

    Vector a;
    Vector o;
    Vector P;
    Vector Q;
};

class PendulumPage: public PageOsc
{
    Q_OBJECT
private:
   //! values are initialized with init() method
   Values_P v;
protected:
  //!widgets for mass
  QLabel *m;
  QDoubleSpinBox *mass;

  //!widgets for length
  QLabel *l;
  QDoubleSpinBox *len;

  //!widgets for friction
  QLabel *fr;
  QDoubleSpinBox *frict;
public slots:
  //!override of addOsc
  virtual void addOsc(GLWidget &w) override;

public:
    PendulumPage();

    virtual ~PendulumPage() {}

    //!updates values of v
    virtual void init() override;
};

#endif // PENDULUMPAGE_H
