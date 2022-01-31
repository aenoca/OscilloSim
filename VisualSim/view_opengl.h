#ifndef VIEW_OPENGL_H
#define VIEW_OPENGL_H

#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "glsphere.h"
#include "../Display/drawingsupport.h"
//#include "../Oscillators/oscillator.h" //
//#include "../Simulation/system.h"
//#include "../Simulation/vector.h"



class System;
class WeightedPendulum;
class Spring;
class DoublePendulum;
class SpringPendulum;
class Oscillator;
class Vector;

//!class for drawing osc graphically
class ViewOpenGL : public DrawingSupport
{
 public:
    //!reinitialization methods
    void init();
    void initializePosition();

    //!sets projection
    void setProjection(QMatrix4x4 const& projection)
    { prog.setUniformValue("projection", projection); }

    //!translate and rotate
    void translate(double x, double y, double z);
    void rotate(double angle, double dir_x, double dir_y, double dir_z);

    //!drawing methods for objects in the view
    void drawAxes(QMatrix4x4 const& viewpoint = QMatrix4x4(), bool in_color = true);
    void drawGrid();
    void drawSphere (QMatrix4x4 const& point_de_vue, GLSphere s, double red = 1, double green = 1, double blue = 1);
    void drawSpring2D(Vector const &o, const Vector &P, const Vector &perp);
    void drawSpring3D(Vector const& o, Vector const& P, Vector const& perp);

    //!virtual pure drawing methods from drawingsupport
    void draw(System const&); // redefinition of draw
    // virtual void draw(Oscillator const&) override;
    virtual void draw(WeightedPendulum const&) override;
    virtual void draw(Spring const&) override;
    virtual void draw(DoublePendulum const&) override;
    virtual void draw(SpringPendulum const&) override;


    //!method to draw the phase space.
    virtual void drawPhase(Oscillator const&) override;

 private:
    //! Un shader OpenGL encapsulé dans une classe Qt
    QOpenGLShaderProgram prog;

    //! Caméra
    QMatrix4x4 matrix_view;
};

#endif
