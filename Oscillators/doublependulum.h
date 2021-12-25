#ifndef DOUBLEPENDULUM_H
#define DOUBLEPENDULUM_H

#include "weightedpendulum.h"

class DrawingSupport;

//!DoublePendulum class
class DoublePendulum: public WeightedPendulum
{
private:
    //mass 2
    double m2;

    //length 2
    double l2;

public:
    //Constructeur
    DoublePendulum(std::string n, DrawingSupport* supp, double mass1, double mass2,
                  double length1, double length2,
                  Vector A = {1, 0, 0}, Vector o = {0, 0, 0});

    //!Equation du mouvement
    Vector f(double t) override;

    //getter
    double getL2() const;

    //!reduces angles to [-pi, pi]
    void correct() override;

    //!for polymorphic copy
    std::unique_ptr<DoublePendulum> clone() const;
    virtual std::unique_ptr<Oscillator> copy() const override;

    //!méthode pour l'affichage texte
    std::ostream& display(std::ostream& output) const override;

    //!Méthode qui appelle la méthode de dessin appropriée dans le support à dessin
    void draw() override;
};

#endif // DOUBLEPENDULUM_H
