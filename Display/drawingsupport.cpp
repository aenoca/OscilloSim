#include "drawingsupport.h"
#include "../Simulation/vector.h"

#include "../Oscillators/oscillator.h"
#include "../Oscillators/weightedpendulum.h"
#include "../Oscillators/spring.h"
#include "../Oscillators/doublependulum.h"
#include "../Oscillators/springpendulum.h"
#include "../Simulation/system.h"

#include <fstream>
#include <string>

using namespace std;

void DrawingSupport::draw(const System & s)
{
    s.drawSystem();
}

TextViewer::TextViewer(std::ostream& output)
: flot(output)
{}

void TextViewer::drawOsc(Oscillator const & o)
{
    cout<<o.getName()<<endl;
    cout<<o.getP()<<"\t #Parametre"<<endl;
    cout<<o.getQ()<<"\t #Vitesse"<<endl<<endl;
}

// void TextViewer::draw(const System & s)
// {
//     s.drawSystem();
// }

void TextViewer::draw(WeightedPendulum const& o) {drawOsc(o);}
void TextViewer::draw(Spring const& o) {drawOsc(o);}
void TextViewer::draw(DoublePendulum const& o) {drawOsc(o);}
void TextViewer::draw(SpringPendulum const& o) {drawOsc(o);}

void TextViewer::drawPhase(Oscillator const& o)
{
    cout<<o.getP()[1]<<"    "<<o.getQ()[1]<<endl;
}

void FileLogger::drawOsc(Oscillator const & s)
{
    // for each oscillator, print P values in a file
    // print Q values in a file
    string filename = s.getName();
    fstream file_P(filename + "_P.txt", std::fstream::app);
    fstream file_Q(filename + "_Q.txt", std::fstream::app);

    file_P << s.getP()<< endl;
    file_Q << s.getQ()<< endl;

    file_P.close();
    file_Q.close();
}

void FileLogger::draw(WeightedPendulum const& o) {drawOsc(o);}
void FileLogger::draw(Spring const& o) {drawOsc(o);}
void FileLogger::draw(DoublePendulum const& o) {drawOsc(o);}
void FileLogger::draw(SpringPendulum const& o) {drawOsc(o);}

void FileLogger::drawPhase(Oscillator const & s)
{

}
