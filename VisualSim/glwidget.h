#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>        //Class for opengl window
//#include <QTime>            //Class to deal with time
//#include <QtOpenGL>
#include <QtWidgets>
#include <QLayout>
#include <QObject>
#include "view_opengl.h"
#include "../Simulation/system.h"
#include "../Oscillators/oscillator.h"

class Oscillator;
class Integrator;


//!class to open window on which drawables are
//!window inherits from QGLWidget, events (keyboard, mouse, time)
//!are virtual methods to redefine.
class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget* parent = nullptr)
      : QOpenGLWidget(parent), s(&view), time(0),  dt(20.0e-3)
    {
        //!set min size of window
        setMinimumSize(640, 480);
        setWindowIcon(QIcon(":/Icone.jpg"));
        //timer.start();
    }

  virtual ~GLWidget() {}

  //!add osc to window
  void addOsc(Oscillator const& o);

  //!change integrator of system
  void setInteg(Integrator*);

  //!returns the view on which to draw
  ViewOpenGL& getView();

  //!returns size of system
  std::size_t size() const;

  //!remove last added osc
  void operator--();

  //!add osc to window
  void operator+=(Oscillator const& o);

  //! show window
  void showWindow();

signals:
    //!signal when window is closed
    void on_Close();

private:
  //!3 key methods from QGLWidget to reimplement
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  //!methods to handle events

  //!keyboard events
  virtual void keyPressEvent(QKeyEvent* event) override;

  //!mouse press event
  virtual void mousePressEvent(QMouseEvent* event) override;

  //!mouse move event
  virtual void mouseMoveEvent(QMouseEvent* event)  override;

  //!scroll wheel event
  virtual void wheelEvent(QWheelEvent *event) override;

  //!time evolution of system and window update
  virtual void timerEvent(QTimerEvent* event)  override;

  //!window closed event => osc system is emptied
  virtual void closeEvent(QCloseEvent *event) override;

  //!internal method to pause
  void pause();

  //!drawing support for the system
  ViewOpenGL view;

  //!system of osc
  System s;

  //! Timer
  int timerId;
  //!time
  double time;
  //!time step
  double dt;

  //!computer delta time
  QElapsedTimer timer;

  //!position of mouse
  QPoint lastMousePosition;


};

#endif // GLWIDGET_H
