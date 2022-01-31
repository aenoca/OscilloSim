#include "pendulumpage.h"
#include "../Oscillators/weightedpendulum.h"


PendulumPage::PendulumPage()
  : PageOsc(1),
    //initialize widgets for length, mass and frict
    m(new QLabel("Mass (kg) :")), mass(new QDoubleSpinBox),
    l(new QLabel("Length (m) :")), len(new QDoubleSpinBox),
    fr(new QLabel("Friction () :")), frict(new QDoubleSpinBox)
{
    //define image on PendulumPage
    image->setPixmap(QPixmap(":/WeightedPendulum.jpg"));

    //!add mass to grid layout
    mass->setDecimals(3); mass->setMinimum(0.001);
    values->addWidget(m, 4, 0);
    values->addWidget(mass, 4, 1);

    //!add length to grid layout
    len->setDecimals(3); len->setMinimum(0.001);
    values->addWidget(l, 5, 0);
    values->addWidget(len, 5, 1);

    //!add frict to grid layout
    frict->setDecimals(3); frict->setMinimum(0.0);
    values->addWidget(fr, 6, 0);
    values->addWidget(frict, 6, 1);

    //!position goes from -pi to pi
    pos[0]->setDecimals(4);
    pos[0]->setMinimum(-3.1415); pos[0]->setMaximum(3.1415);

    //!vel between -10 to 10
    vel[0]->setDecimals(4);
    vel[0]->setMinimum(-10); vel[0]->setMaximum(10);

}

void PendulumPage::init()
{
    //update attributes of pendulum
    v.m = mass->value();
    v.l = len->value();
    v.fr = frict->value();

    v.a = {dir[0] -> value(), dir[1] -> value(), dir[2] -> value()};
    v.o = {center[0] -> value(), center[1] -> value(), center[2] -> value()};
    v.P = {pos[0]->value()};
    v.Q = {vel[0]->value()};
}

void PendulumPage::addOsc(GLWidget & w)
{
    init(); //v values are updated

    //check if A is the null vector
    // may want to display an error box
    if(v.a == Vector({0, 0, 0})) std::cerr<<"Vector A cannot be null vector."<<std::endl;
    else if(v.a * Vector({1, 0, 0}) == 0 and v.a * Vector({0, 1, 0}) == 0) std::cerr<<"Vector A cannot be colinear to g"<<std::endl;
    else{
        //On initialise un pendulePesant avec les valeurs de v
        WeightedPendulum p("p1", &w.getView(), v.m, v.l, v.fr, v.a, v.o);
        p.setP(v.P);
        p.setQ(v.Q);

        w += p;
    }
}
