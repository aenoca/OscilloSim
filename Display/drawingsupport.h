#ifndef DRAWINGSUPPORT_H
#define DRAWINGSUPPORT_H

#include <iostream>

class Oscillator;
class WeightedPendulum;
class Spring;
class DoublePendulum;
class SpringPendulum;
class System;

//!abstract mother class for
class DrawingSupport
{
public:
    virtual ~DrawingSupport () {}

    //!called when a drawable is drawn
    void draw(System const&);
    virtual void draw(Oscillator const&) = 0;

    //!called to draw phase space
    virtual void drawPhase(Oscillator const&) = 0;

};

//!class to draw in text form
class TextViewer : public DrawingSupport {
 public:

    TextViewer(std::ostream& output);

    virtual ~TextViewer() {}

    //!called to draw oscillators
    //virtual void draw(System const& j) override;
    virtual void draw(Oscillator const& o) override;

    //!called to draw the phase space
    virtual void drawPhase(Oscillator const&) override;

 private:

    std::ostream& flot;
};

void ecris_Oscillo(Oscillator const& o);

//!class to draw each oscillator in its own file
class FileLogger: public DrawingSupport {
 public:
    FileLogger() {};

    //!called to draw oscillators
    //virtual void draw(System const& j) override;
    virtual void draw(Oscillator const& o) override;

    //!called to draw the phase space
    virtual void drawPhase(Oscillator const&) override;

};

#endif // DRAWINGSUPPORT_H
