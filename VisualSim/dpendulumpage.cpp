#include "dpendulumpage.h"
#include "../Oscillators/doublependulum.h"

DPendulumPage::DPendulumPage()
  : PageOsc(2),
    //initialize widgets for length, mass and frict
    m(new QLabel("Mass (kg) :")), mass(new QDoubleSpinBox),
    l(new QLabel("Length (m) :")), len(new QDoubleSpinBox),
    m2(new QLabel("Mass 2 (kg) :")), mass2 (new QDoubleSpinBox),
    l2(new QLabel("Length 2 (m) :")), len2 (new QDoubleSpinBox)
    //fr(new QLabel("Friction () :")), frict(new QDoubleSpinBox)
{
    //define image on PendulumPage
    image->setPixmap(QPixmap(":/DoublePendulum.jpg"));

    //!add mass to grid layout
    mass->setDecimals(3); mass->setMinimum(0.001);
    values->addWidget(m, 4, 0);
    values->addWidget(mass, 4, 1);

    //!add length to grid layout
    len->setDecimals(3); len->setMinimum(0.001);
    values->addWidget(l, 5, 0);
    values->addWidget(len, 5, 1);

    //!add mass to grid layout
    mass2->setDecimals(3); mass2->setMinimum(0.001);
    values->addWidget(m2, 4, 2);
    values->addWidget(mass2, 4, 3);

    //!add length to grid layout
    len2->setDecimals(3); len2->setMinimum(0.001);
    values->addWidget(l2, 5, 2);
    values->addWidget(len2, 5, 3);

    /*!add frict to grid layout
    frict->setDecimals(3); frict->setMinimum(0.0);
    values->addWidget(fr, 6, 0);
    values->addWidget(frict, 6, 1);*/

    //!position goes from -pi to pi
    pos[0]->setDecimals(4);
    pos[0]->setMinimum(-3.1415); pos[0]->setMaximum(3.1415);
    pos[1]->setDecimals(4);
    pos[1]->setMinimum(-3.1415); pos[1]->setMaximum(3.1415);

    //!vel between -10 to 10
    vel[0]->setDecimals(4);
    vel[0]->setMinimum(-10); vel[0]->setMaximum(10);
    vel[1]->setDecimals(4);
    vel[1]->setMinimum(-10); vel[1]->setMaximum(10);

}

void DPendulumPage::init()
{
    v.m1 = mass->value();
    v.m2 = mass2->value();
    v.l1 = len->value();
    v.l2 = len2->value();

    v.a = {dir[0] -> value(), dir[1] -> value(), dir[2] -> value()};
    v.o = {center[0] -> value(), center[1] -> value(), center[2] -> value()};
    v.P = {pos[0]->value(), pos[1]->value()};
    v.Q = {vel[0]->value(), vel[1]->value()};
}

void DPendulumPage::addOsc(GLWidget & w)
{
    init(); //initialise v

    //check if A is the null vector
    // may want to display an error box
    if(v.a == Vector({0, 0, 0})) std::cerr<<"Vector A cannot be null vector."<<std::endl;
    else if(v.a * Vector({1, 0, 0}) == 0 and v.a * Vector({0, 1, 0}) == 0) std::cerr<<"Vector A cannot be colinear to g"<<std::endl;
    else{
        DoublePendulum dp("dp1", &w.getView(), v.m1, v.m2, v.l1, v.l2, v.a, v.o);
        dp.setP(v.P);
        dp.setQ(v.Q);

        w += dp;
    }
}
