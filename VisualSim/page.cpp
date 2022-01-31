#include "page.h"
//#include "pageosc.h"

#include "../Simulation/integratoreuler.h"
#include "../Simulation/integratoreulercromer.h"
#include "../Simulation/integratornewmark.h"
#include "../Simulation/integratorrungekutta.h"

#include "pendulumpage.h"
#include "springpage.h"
#include "dpendulumpage.h"
#include "spendulumpage.h"


Page::Page()
:vlayout(new QVBoxLayout(this)),
  //!initialize the osc pages
  tab(new QTabWidget),
  pp(new PendulumPage), sp(new SpringPage), dp(new DPendulumPage), spp(new SPendulumPage),

  //!initialize integrator choice box
  int_box(new QHBoxLayout), title(new QLabel("Choose the integrator :")), choice_integ(new QComboBox),

  //!initialize buttons and display of # of osc
  bottom(new QHBoxLayout), back(new QPushButton("Back")), launch(new QPushButton("Launch")), nb_osc(new QLabel("# of oscillators : 0"))
{
    //!add pageosc to QWidgetTab
    tab->addTab(pp, "Weighted Pendulum"); tab->addTab(sp, "Spring");
    tab->addTab(dp, "Double Pendulum"); tab->addTab(spp, "Spring Pendulum");

    //!add the QWidgetTab to the layout of the page
    vlayout->addWidget(tab);

    //!add choice of integrator to QComboBox
    choice_integ->addItem("Euler"); choice_integ->addItem("Euler-Cromer");
    choice_integ->addItem("Newmark"); choice_integ->addItem("Runge-Kutta");
    choice_integ->setFixedWidth(150);

    //!add the QHBoxlayout of the integrator to layout of page
    vlayout->addLayout(int_box);

    //!add the widgets to layout of integrator
    int_box->addWidget(title, 0, Qt::AlignRight);
    int_box->addWidget(choice_integ ,0, Qt::AlignLeft);

     //!add bottom QHBoxLayout to general layout
     vlayout->addLayout(bottom);

     //!add widgets back, launch and nb_osc to bottom hbox
     bottom->addWidget(back,0, Qt::AlignBottom | Qt::AlignLeft);
     bottom->addWidget(nb_osc, 0, Qt::AlignBottom | Qt::AlignCenter);
     bottom->addWidget(launch, 0, Qt::AlignBottom | Qt::AlignRight);


     //!when a button is pressed, call method to add osc
     connect(pp->getAdd(), SIGNAL(clicked(bool)), this, SLOT(addOscP()));
     connect(dp->getAdd(), SIGNAL(clicked(bool)), this, SLOT(addOscDP()));
     connect(sp->getAdd(), SIGNAL(clicked(bool)), this, SLOT(addOscS()));
     connect(spp->getAdd(), SIGNAL(clicked(bool)), this, SLOT(addOscSP()));

     //!when a button is pressed, call method to remove osc
     connect(pp->getLess(), SIGNAL(clicked(bool)), this, SLOT(removeOsc()));
     connect(dp->getLess(), SIGNAL(clicked(bool)), this, SLOT(removeOsc()));
     connect(sp->getLess(), SIGNAL(clicked(bool)), this, SLOT(removeOsc()));
     connect(spp->getLess(), SIGNAL(clicked(bool)), this, SLOT(removeOsc()));


     //!if launch button is pressed, call method to launch window
     QObject::connect(launch, SIGNAL(clicked(bool)), this, SLOT(launchWindow()));

     //!if GLWidget window is closed, call on_close()
     connect(&w, SIGNAL(on_Close()), this, SLOT(onClose()));
}

const QPushButton* Page::getBack()
{
    return back;
}

void Page::launchWindow()
{
    setIntegrator(choice_integ->currentIndex());
    w.showWindow();
}

void Page::addOscP(){ pp->addOsc(w); setNbOsc(); }
void Page::addOscDP() { dp->addOsc(w); setNbOsc(); }
void Page::addOscS() { sp->addOsc(w); setNbOsc(); }
void Page::addOscSP() { spp->addOsc(w); setNbOsc(); }

//Potentielle amélioration
//void Page::ajouterOscillo(std::size_t i) { fen_o[i]->ajouterOscillo(w); setNbOscillo(); }
//void Page::on_add() { setNbOscillo();}

void Page::removeOsc() { --w; setNbOsc(); }

 void Page::setIntegrator(int i)
 {
     switch (i){
        case 0 :
            w.setInteg(new IntegratorEuler);
            break;
        case 1 :
            w.setInteg(new IntegratorEulerCromer);
            break;
        case 2 :
            w.setInteg(new IntegratorNewmark);
            break;
        case 3:
            w.setInteg(new IntegratorRungeKutta);
            break;
     }
 }

 void Page::setNbOsc()
 {
    nb_osc->setText("# oscillators : " + QString::number(w.size()));
 }

 void Page::onClose()
 {
     setNbOsc();
 }
