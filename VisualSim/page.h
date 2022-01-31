#ifndef PAGE_H
#define PAGE_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QtWidgets>
#include "glwidget.h"
//#include "pageoscillos.h"

#include "../Oscillators/oscillator.h"

class PendulumPage;
class SpringPage;
class DPendulumPage;
class SPendulumPage;

class Page : public QWidget
{
    Q_OBJECT
private:
    //!general structure of 2nd page
    QVBoxLayout *vlayout;

    //!tabwidget for the 4 oscillator pages
    QTabWidget *tab;
    PendulumPage *pp;
    SpringPage *sp;
    DPendulumPage *dp;
    SPendulumPage *spp;

    //!future improvement, std::array<OscilloPage*, 4> fen;

    //!structure below tabwidget
    QHBoxLayout *int_box;

    //!text before choice of integrator
    QLabel *title;

    //!contains choice of integrators
    QComboBox *choice_integ;

    //!structure at bottom of page
    QHBoxLayout *bottom;

    //!button to come back to homepage
    QPushButton *back;

    //!button to launch the simulation
    QPushButton *launch;

    //!sets the integrator according to choice in combobox
    void setIntegrator(int);

    //!displays the number of osc in sim
    QLabel *nb_osc;

    //!changes the label of num of osc
    void setNbOsc();

    //!window where we draw the osc
    GLWidget w;
public:
    //!constructor
    Page();

    //!destructor
    virtual ~Page(){}

    //!gets pointer on back button
    const QPushButton* getBack();

private slots:
    //!displays the GLWidget window and updates the integrator
    void launchWindow();

    //!adds osc to GLWidget window, and updates num osc label
    void addOscP();
    void addOscDP();
    void addOscS();
    void addOscSP();

    // improvement
    //void addOsc(int);
    //void onAdd();

    //!removes last added osc
    void removeOsc();

    //!reset num osc to zero
    void onClose();

};

#endif // PAGE_H
