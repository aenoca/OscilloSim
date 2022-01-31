#include "pageosc.h"

PageOsc::PageOsc(int dim)
: //!initialisation of the layout of a PageOsc
  box(new QHBoxLayout(this)), image(new QLabel),
  values(new QGridLayout),

//  //Initialisation des Widgets pour la masse
//  m(new QLabel("Masse (Kg) :")), mass(new QDoubleSpinBox),

//  //Initialisation des Widgets pour les frottements
//  fr(new QLabel("Frottements :")), frott(new QDoubleSpinBox),

  //!initialize widgets for vectors A, =, P, Q
  a(new QLabel("Vector A (Direction) : ")),
  o(new QLabel("Vector O (Center) : ")),
  P(new QLabel("Vector P (Position) : ")),
  Q(new QLabel("Vector Q (Velocity) : ")),

  //!initialization of add / remove buttons
  add(new QPushButton("Add")),
  remove(new QPushButton("Remove last"))
{
    //!add image of osc to box layout
    //!add gridlayout to box layout
    box->addWidget(image); box->addLayout(values);

    //!initialize widgets fo A and O
    for(size_t i(0); i < 3; ++i){
        center[i] = new QDoubleSpinBox;
        dir[i] = new QDoubleSpinBox;
    }

    /*//On ajoute la masse au Gridlayout
    masse->setDecimals(3); masse->setMinimum(0.001);
    valeurs->addWidget(m, 0, 0);
    valeurs->addWidget(masse, 0, 1);

    //On ajoute les frottements au Gridlayout
    frott->setDecimals(3); frott->setMinimum(0.0);
    valeurs->addWidget(fr, 4, 0);
    valeurs->addWidget(frott, 4, 1);*/

    //!add titles of A and O to gridlayout
    values->addWidget(a, 1, 0);
    values->addWidget(o, 0, 0);

    //!set max/min values of vectors A and O
    //! -10 to 10 for each direction
    //!then add to grid layout
    for(size_t i(0); i < 3; ++i){
        dir[i]->setDecimals(2);
        dir[i]->setMinimum(-10); dir[i]->setMaximum(10);
        values->addWidget(dir[i], 1, i+1);
        center[i]->setDecimals(2);
        center[i]->setMinimum(-10); center[i]->setMaximum(10);
        values->addWidget(center[i], 0, i+1);
    }
    dir[1]->setValue(1.0); //!default value for A = {0, 1, 0}

    //!add spinbox for the number of dof of osc
    for(int i(0); i < dim; ++i)
    {
        pos.push_back(new QDoubleSpinBox); vel.push_back(new QDoubleSpinBox);
    }

    //!add pos and vel to grid
    values->addWidget(P, 2, 0);
    values->addWidget(Q, 3, 0);

    for(int i(1); i <= dim; ++i)
    {
        values->addWidget(pos[i-1], 2, i);
        values->addWidget(vel[i-1], 3, i);
    }

    //!add add and remove buttons to layout
    values->addWidget(remove, 9, 0);
    values->addWidget(add,9, 5);
}
