#include "spendulumpage.h"

#include "../Oscillators/springpendulum.h"

SPendulumPage::SPendulumPage()
  : PageOsc(2),
    //initialize widgets for k, mass and frict
    m(new QLabel("Mass (kg) :")), mass(new QDoubleSpinBox),
    k(new QLabel("Spring cste (N/m) :")), cst(new QDoubleSpinBox),
    l(new QLabel("Length (m) :")), len(new QDoubleSpinBox)
{
    //define image on PendulumPage
    image->setPixmap(QPixmap(":/SpringPendulum.jpg"));

    //!add mass to grid layout
    mass->setDecimals(3); mass->setMinimum(0.001);
    values->addWidget(m, 4, 0);
    values->addWidget(mass, 4, 1);

    //!add length to grid layout
    cst->setDecimals(3); cst->setMinimum(0.001);
    values->addWidget(k, 5, 0);
    values->addWidget(cst, 5, 1);

    //!add frict to grid layout
    len->setDecimals(3); len->setMinimum(0.0);
    values->addWidget(l, 6, 0);
    values->addWidget(len, 6, 1);

    //!position goes from -pi to pi
    pos[0]->setDecimals(4);
    pos[0]->setMinimum(-30); pos[0]->setMaximum(30);
    pos[1]->setDecimals(4);
    pos[1]->setMinimum(-30); pos[1]->setMaximum(30);

    //!vel between -10 to 10
    vel[0]->setDecimals(4);
    vel[0]->setMinimum(-30); vel[0]->setMaximum(30);
    vel[1]->setDecimals(4);
    vel[1]->setMinimum(-30); vel[1]->setMaximum(30);

}

void SPendulumPage::init()
{
    //update v
    v.m = mass->value();
    v.l = len->value();
    v.k = cst->value();

    v.a = {dir[0] -> value(), dir[1] -> value(), dir[2] -> value()};
    v.o = {center[0] -> value(), center[1] -> value(), center[2] -> value()};
    v.P = {pos[0]->value(), pos[1]->value()};
    v.Q = {vel[0]->value(), vel[1]->value()};
}

void SPendulumPage::addOsc(GLWidget & w)
{
    init(); //Les valeurs de V sont initialisées

    //Warning position cannot be null,
    //par rapport à son centre sinon les éq de mouvement ne font rien
    //De même l'axe A ne peur être le vecteur nul

    if(v.P == Vector({0, 0})) std::cerr<<"Position of the mass cannot be at attachement point."<<std::endl;
    else if(v.a == Vector({0, 0, 0})) std::cerr<<"Vector A cannot be null"<<std::endl;
    else if(v.a * Vector({1, 0, 0}) == 0 and v.a * Vector({0, 1, 0}) == 0) std::cerr<<"Vector A cannot be colinear to G."<<std::endl;
    else{
        SpringPendulum pr("sp1", &w.getView(), v.m, v.k, v.l, v.a, v.o);
        pr.setP(v.P);
        pr.setQ(v.Q);

        w += pr;
    }
}
