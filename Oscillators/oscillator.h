#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "../Display/drawable.h"
#include "../Simulation/vector.h"

#include <iostream>
#include <vector>
#include <memory>


//#include "../Display/drawingsupport.h"

class DrawingSupport;

//! structure used to represent a point in phase space (x, y) = (P, Q)
struct Point
{
    double x;
    double y;
};

class Oscillator : public Drawable
{
protected:
    //!position vector
    Vector P;

    //!velocity vector
    Vector Q;

    //!origin vector
    Vector O;

    //!unit direction vector. Indicates plane of oscillation
    Vector a;

    //!friction coefficient
    double lambda;

    //!points of curve of phase space
    std::vector<Point> curve;
public:
    //!constructor
    Oscillator(DrawingSupport* supp, std::size_t dof = 1, double fr = 0,
               Vector A = {0, 1, 0}, Vector o = {0, 0, 0});

    //!equation of motion
    virtual Vector f(double t) = 0; // needs to be defined for the child classes

    //!getters
    Vector getP() const;
    Vector getQ() const;
    Vector getO() const;
    Vector getA() const;

    //!setters
    void setP(Vector const& vec);
    void setQ(Vector const& vec);

    //!calls a DrawingSupport method to display the phase space
    virtual void drawPhase();

    //!Adds point to phase space
    void addPoint(double x, double y);

    //!get phase space curve
    const std::vector<Point>& getCurve() const;

    //!display interesting quantites
    virtual std::ostream& display(std::ostream& output) const;

    //!corrects the oscillators
    virtual void correct() {}

    //!used for polymorphic copy
    virtual std::unique_ptr<Oscillator> copy() const = 0;

    //!virtual method for drawing
    virtual void draw(){};


};

//!displaying an oscillator <<
std::ostream& operator<<(std::ostream& output, const Oscillator& osc);

#endif // OSCILLATOR_H
