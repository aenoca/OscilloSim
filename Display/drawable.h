#ifndef DRAWABLE_H
#define DRAWABLE_H

class DrawingSupport;

//!Mother class of everything that can be drawn
class Drawable
{
protected:
    //!pointer on drawing support (Textviewer or OpenGLview)
    DrawingSupport* support;
public:
    //!constructor
    Drawable(DrawingSupport* supp);

    //!destructor
    virtual ~Drawable(){};

    //!to be defined by each inheriting class
    virtual void draw() = 0;

    /*	To add to all inheriting classes
     * virtual void draw() override
     * {(*support).draw(*this);}
     *
    */

};

#endif // DRAWABLE_H
