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

void TextViewer::draw(const WeightedPendulum & p)
{
    cout<<"#PendulePesant"<<endl;
    ecris_Oscillo(p);
}
void TextViewer::draw(Spring const& r)
{
    cout<<"#Ressort"<<endl;
    ecris_Oscillo(r);
}
void TextViewer::draw(DoublePendulum const& dp)
{
    cout<<"#DoublePendule"<<endl;
    ecris_Oscillo(dp);
}
void TextViewer::draw(SpringPendulum const& pr)
{
    cout<<"#PenduleRessort"<<endl;
    ecris_Oscillo(pr);
}

void TextViewer::drawPhase(Oscillator const& o)
{
    cout<<o.getP()[1]<<"    "<<o.getQ()[1]<<endl;
}
