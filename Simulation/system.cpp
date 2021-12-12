#include "system.h"
#include "../Oscillators/oscillator.h"
#include "integrator.h"
#include "../Display/drawingsupport.h"

#include <iostream>
//#include <vector>
//#include <memory>


using namespace std;

System::System(DrawingSupport* supp, Integrator* I)
:Drawable(supp), phase(false)
{
    integrator = std::unique_ptr<Integrator>(I);
}

void System::draw()
{
    support->draw(*this);
}

void System::drawSystem() const
{
    for(auto& oscillo : system){
        if(phase and system.size() == 1) oscillo->drawPhase();
        else if (phase) cerr<<"Too many oscillators in the system"
                            <<" to draw the phase space."<<endl;
        else oscillo->draw();
    }
}

void System::evolve(double dt, double t)
{
    for(auto & oscillo: system)
    {
        oscillo->correct();
        oscillo->addPoint(oscillo->getP()[1], oscillo->getQ()[1]); //add points to curve
        integrator->integrate(*oscillo, dt, t);
    }
}

void System::addOscillo(Oscillator const& o)
{
    system.push_back(o.copy());
}

System& System::operator+=(Oscillator const& o)
{
    addOscillo(o);
    return *this;
}

void System::setInteg(Integrator* integ)
{
    if(integ != nullptr) integrator = unique_ptr<Integrator>(integ);
}

void System::setPhase(bool p)
{
    phase = p;
}

void System::empty()
{
    system.clear();
}

std::size_t System::size() const
{
    return system.size();
}

System& System::operator--()
{
    if(system.size() != 0) system.pop_back();
    return *this;
}
