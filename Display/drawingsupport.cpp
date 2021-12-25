#include "drawingsupport.h"
#include "../Simulation/vector.h"

#include "../Oscillators/oscillator.h"
#include "../Oscillators/weightedpendulum.h"
#include "../Oscillators/spring.h"
#include "../Oscillators/doublependulum.h"
#include "../Oscillators/springpendulum.h"
#include "../Simulation/system.h"

using namespace std;

TextViewer::TextViewer(std::ostream& output)
: flot(output)
{}

void ecris_Oscillo(Oscillator const & o)
{
    cout<<o.getP()<<"\t #Parametre"<<endl;
    cout<<o.getQ()<<"\t #Vitesse"<<endl<<endl;
}

void TextViewer::draw(const System & s)
{
    s.drawSystem();
}

void TextViewer::draw(const Oscillator & o)
{
    cout<<o.getName()<<endl;
    ecris_Oscillo(o);
}

void TextViewer::drawPhase(Oscillator const& o)
{
    cout<<o.getP()[1]<<"    "<<o.getQ()[1]<<endl;
}
