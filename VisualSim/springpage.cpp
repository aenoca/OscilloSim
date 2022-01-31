#include "springpage.h"

#include "../Oscillators/spring.h"

SpringPage::SpringPage()
  : PageOsc(1),
    //initialize widgets for k, mass and frict
    m(new QLabel("Mass (kg) :")), mass(new QDoubleSpinBox),
    k(new QLabel("Spring cste (N/m) :")), cst(new QDoubleSpinBox),
    fr(new QLabel("Friction () :")), frict(new QDoubleSpinBox)
{
    //define image on PendulumPage
    image->setPixmap(QPixmap(":/Spring.jpg"));

    //!add mass to grid layout
    mass->setDecimals(3); mass->setMinimum(0.001);
    values->addWidget(m, 4, 0);
    values->addWidget(mass, 4, 1);

    //!add length to grid layout
    cst->setDecimals(3); cst->setMinimum(0.001);
    values->addWidget(k, 5, 0);
    values->addWidget(cst, 5, 1);

    //!add frict to grid layout
    frict->setDecimals(3); frict->setMinimum(0.0);
    values->addWidget(fr, 6, 0);
    values->addWidget(frict, 6, 1);

    //!position goes from -pi to pi
    pos[0]->setDecimals(4);
    pos[0]->setMinimum(-30); pos[0]->setMaximum(30);

    //!vel between -10 to 10
    vel[0]->setDecimals(4);
    vel[0]->setMinimum(-30); vel[0]->setMaximum(30);

}

void SpringPage::init()
{
    //On initialise les valeurs de v pour le ressort
    v.m = mass->value();
    v.fr = frict->value();
    v.k = cst->value();

    v.a = {dir[0] -> value(), dir[1] -> value(), dir[2] -> value()};
    v.o = {center[0] -> value(), center[1] -> value(), center[2] -> value()};
    v.P = {pos[0]->value()};
    v.Q = {vel[0]->value()};
}

void SpringPage::addOsc(GLWidget & w)
{
    init(); //update values

    //A cannot be null, vector of direction of oscillation
    if(v.a == Vector({0, 0, 0})) std::cerr<<"Vector A cannot be null vector."<<std::endl;
    else{
        Spring r("r1", &w.getView(), v.m, v.k, v.fr, v.a, v.o);
        r.setP(v.P);
        r.setQ(v.Q);

        w += r;
    }
}
