#ifndef SYSTEM_H
#define SYSTEM_H

#include "../Display/drawable.h"
#include <vector>
#include <memory>

class DrawingSupport;
class Oscillator;
class Integrator;

//!class containing system of oscillators
class System : public Drawable
{
private:

    //!group of oscillators
    std::vector<std::unique_ptr<Oscillator>> system;

    //!pointer on the integrator
    std::unique_ptr<Integrator> integrator;

    //!true -> draw phase space
    bool phase;

public:
    //!constructor
    System(DrawingSupport* supp, Integrator* I);

    //!we delete the copy constructor
    System(System& s) = delete;

    //!polymorphic method call to DrawingSupport method
    virtual void draw() override;

    //!called by DrawingSupport method
    void drawSystem() const;

    //!system advance by one step dt, at time t
    void evolve(double dt, double t = 0);

    //!add oscillator with polymorphic copy
    void addOscillo(Oscillator const& o);

    //!add oscillator
    System& operator+=(Oscillator const& o);

    //!remove last added oscillator
    System& operator--();

    //!choose the integrator
    void setInteg(Integrator* integ);

    //!choose if phase drawing
    void setPhase(bool);

    //!empties the system
    void empty();

    //!size of system
    std::size_t size() const;
};

#endif // SYSTEM_H
