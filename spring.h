/*!
 *  \author    Babak Tootoonchi
 *  \version   2.0
 *  \date      Sept. 2014
 */

#ifndef SPRING_H
#define SPRING_H

#include <QVector2D>
#include <QtOpenGL/QGLWidget>
#include <GL/GLU.h>
#include "utils.h"

class Weight;

/*! The Spring class is for simulating spring objects and their behaviour. */
class Spring
{
public:
    //! CONSTRUCTOR
    /*! Initializes spring parameters to default values.
     *  \param head pointer to the head weight.
     *  \param restLen the initial rest length
     */
    Spring(Weight *head, GLdouble restLen);

    //! DEFAULT CONSTRUCTOR
    Spring();

    //! DESTRUCTOR
    ~Spring(){}

    /*! Sets the rest length of the spring to the given value.
     *  \param len new rest length for the spring.
     */
    void setRestLength(GLdouble len);

    /*! Returns the current rest length of the spring.
     *  \return the rest length of the spring.
     */
    GLdouble getRestLength();

    /*! Sets the spring constant to the given value value.
     *  \param ks new spring constant.
     */
    void setSpringConstant(GLdouble ks);

    /*! Returns the spring constant
     *  \return spring constant.
     */
    GLdouble getSpringConstant();

    /*! Sets the spring damping coefficient to the given value.
     *  \param kd damping coefficient.
     */
    void setDampingCoefficient(GLdouble kd);

    /*! Returns the damping coefficient of the spring.
     *  \return damping coefficient.
     */
    GLdouble getDampingCoefficient();

    /*! Sets the head and tail pointers
     *  \param head pointer to the head weight.
     *  \param tail pointer to the tail weight.
     */
    void setPostion(Weight *head, Weight *tail);

    /*! Returns the head pointer */
    Weight *getHead();

    /*! Returns the tail pointer */
    Weight *getTail();

    /*! Draws the spring */
    void draw();

    //! Pointer to the head of the spring
    Weight *_head;

    //! Pointer to the tail of the spring
    Weight *_tail;

 private:
    //! Rest length of the spring.
    GLdouble _restLength;

    //! Spring radius
    GLdouble _radius;

    //! Spring constant a.k.a. stiffness.
    GLdouble _springConstant;

    //! Damping coefficient
    GLdouble _dampingCoeff;
};

#endif // SPRING_H
