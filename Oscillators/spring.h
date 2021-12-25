#ifndef SPRING_H
#define SPRING_H

#include "oscillator.h"
//#include "../Simulation/vector.h"

class DrawingSupport;

//!Classe permettant d'implémenter un Ressort
class Spring : public virtual Oscillator
{
protected:
    //!mass
    double m;

    //!stiffness constant
    double k;

public:
    //!constructor
    Spring(std::string n, DrawingSupport* supp, double m, double cst, double fr = 0,
           Vector A = {1, 0, 0}, Vector o = {0, 0, 0});

    //!equation of motion
    Vector f(double t) override;

    //!for polymorphic copy
    std::unique_ptr<Spring> clone() const;
    virtual std::unique_ptr<Oscillator> copy() const override;

    //!for text display
    std::ostream& display(std::ostream& output) const override;

    //!calls the appropriate DrawingSupport method
    void draw() override;
};

#endif // SPRING_H
