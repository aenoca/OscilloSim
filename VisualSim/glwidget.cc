#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "glwidget.h"

#include "../Simulation/integratoreuler.h"
#include "../Simulation/integratoreulercromer.h"
#include "../Simulation/integratornewmark.h"
#include "../Simulation/integratorrungekutta.h"


void GLWidget::addOsc(Oscillator const& o)
{
    s += o;
}

void GLWidget::setInteg(Integrator * I)
{
    s.setInteg(I);
}

ViewOpenGL& GLWidget::getView()
{
    return view;
}

std::size_t GLWidget::size() const
{
    return s.size();
}

void GLWidget::operator--()
{
    --s;
}

void GLWidget::operator+=(Oscillator const& o)
{
    addOsc(o);
}

void GLWidget::showWindow()
{
    this->show();
    timer.start();
}

// ======================================================================

void GLWidget::initializeGL()
{
  view.init();
  timerId = startTimer(20);
  setMouseTracking(true);
}

// ======================================================================
void GLWidget::resizeGL(int width, int height)
{

  /* We start by indicating where on the OpenGl to draw,
   * here on the whole window
   */
  glViewport(0, 0, width, height);
  /* We modify the projection matrix of the shader,
   * by creating an identity matrix and multiply it from
   * the right with a perspective matrix.
   * See for more details
   *     http://www.songho.ca/opengl/gl_projectionmatrix.html
   * Then upload the matrix on the shader using setProjection.
   */
  QMatrix4x4 matrix;
  matrix.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  view.setProjection(matrix);
}

// ======================================================================

void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //we paint the system in the window
  s.draw();
}

// ======================================================================

void GLWidget::keyPressEvent(QKeyEvent* event)
{
  constexpr double small_angle(5.0); // in degrees
  constexpr double small_step(0.2);

  switch (event->key()) {

  case Qt::Key_Left:
    view.rotate(small_angle, 0.0, -1.0, 0.0);
    break;

  case Qt::Key_Right:
    view.rotate(small_angle, 0.0, +1.0, 0.0);
    break;

  case Qt::Key_Up:
    view.rotate(small_angle, -1.0, 0.0, 0.0);
    break;

  case Qt::Key_Down:
    view.rotate(small_angle, +1.0, 0.0, 0.0);
    break;

  case Qt::Key_PageUp:
  case Qt::Key_W:
    view.translate(0.0, 0.0,  small_step);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    view.translate(0.0, 0.0, -small_step);
    break;

  case Qt::Key_A:
    view.translate( small_step, 0.0, 0.0);
    break;

  case Qt::Key_D:
    view.translate(-small_step, 0.0, 0.0);
    break;

  case Qt::Key_R:
    view.translate(0.0, -small_step, 0.0);
    break;

  case Qt::Key_F:
    view.translate(0.0,  small_step, 0.0);
    break;

  case Qt::Key_Q:
    view.rotate(small_angle, 0.0, 0.0, -1.0);
    break;

  case Qt::Key_E:
    view.rotate(small_angle, 0.0, 0.0, +1.0);
    break;

  case Qt::Key_Home:
    view.initializePosition();
    break;

  case Qt::Key_Space:
    pause();
    break;

  //change integrator during simulation
  case Qt::Key_N:
    s.setInteg(new IntegratorNewmark);
    break;

  case Qt::Key_K:
    s.setInteg(new IntegratorRungeKutta);
    break;

  case Qt::Key_U:
    s.setInteg(new IntegratorEulerCromer);
    break;

  case Qt::Key_J:
    s.setInteg(new IntegratorEuler);
      break;
  //change between normal and phase space
  case Qt::Key_P:
      s.setPhase(true);
      break;
  case Qt::Key_O:
      s.setPhase(false);
      break;

  };

  update(); //redraw
}

// ======================================================================

void GLWidget::mousePressEvent(QMouseEvent* event)
{
  lastMousePosition = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
  /* If mouse tracking is disabled (the default), the widget only receives
   * mouse move events when at least one mouse button is pressed while the
   * mouse is being moved.
   *
   */

  if (event->buttons() & Qt::LeftButton) {
    constexpr double small_angle(.4); // in degrees

    //gets relative movement wrt to previous position of mouse
    QPointF d = event->pos() - lastMousePosition;
    lastMousePosition = event->pos();

    view.rotate(small_angle * d.manhattanLength(), d.y(), d.x(), 0);

    update();
  }
}

void GLWidget::wheelEvent(QWheelEvent * event)
{
    constexpr double small_step(0.5);

    int degrees = event->angleDelta().y() / 8.0;
    int move = degrees / 15;

    view.translate(0, 0, move * small_step);
    update();
}

// ======================================================================

void GLWidget::timerEvent(QTimerEvent* event)
{
  Q_UNUSED(event);

  //double dt = chrono.restart() / 1000.0;
  dt = timer.restart() / 1000.0;
  time += dt;

  s.evolve(dt, time);
  update();
}

void GLWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    //empty the system of oscillators
    s.empty();
    //
    view.initializePosition();
    //set time to zero
    time = 0;
    //kill timer
    if(timerId != 0)
    {
        killTimer(timerId);
        timerId = 0;
    }


    emit on_Close();
}

// ======================================================================
void GLWidget::pause()
{
  if (timerId == 0) {
    // if timer isn't running we launch it
    timerId = startTimer(20);
    timer.restart();
  } else {
    // if timer is running we stop it

    killTimer(timerId);
    timerId = 0;
  }
}

// ======================================================================

