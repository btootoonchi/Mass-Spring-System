/*!
 *  \author    Babak Tootoonchi
 *  \version   2.0
 *  \date      Sept. 2014
 */

#ifndef WEIGHT_H
#define WEIGHT_H

#include <QVector2D>
#include <QtOpenGL/QGLWidget>
#include <GL/GLU.h>
#include <QVector>

class Spring;

/*! The Weight class is for simulating weights and their movement. */
class Weight
{
public:
    //! CONSTRUCTOR
    /*! Initializes weight parameters to default values.
     *  Allocates a vector of eight pointers to adjacent spring objects.
     */
    Weight();

    //! DESTRUCTOR
    /*! Clears the spring vector for each weight. */
    ~Weight();

    void init(QVector2D pos);

    /*! Draws the weight. */
    void draw();

    /*! Sets the current position of the weight to the given value.
     *  \param pos new position of the weight.
     */
    void setPos(QVector2D pos);

    /*! Returns the current position of the weight.
     *  \return the position of the weight.
     */
    QVector2D getPos();

    /*! Sets the velocity of the weight to the given value.
     *  \param v new velocity of the weight.
     */
    void setVelocity(QVector2D v);

    /*! Returns the current velocity of the weight.
     *  \return the velocity of the weight.
     */
    QVector2D getVelocity();

    /*! Sets the mass of the weight to the given value.
     *  \param m the mass of the weight.
     */
    void setMass(GLdouble m);

    /*! Returns the mass of the weight.
     *  \return the mass of the weight in kg.
     */
    GLdouble getMass();

    /*! Returns the width of the weight.
     *  \return the width of the weight.
     */
    GLdouble getWidth();

    //! Vector of pointers to eight adjacent springs
    QVector<Spring*> _spring;

private:
    //! Position of the weight at time t
    QVector2D _pos;

    //! Velocity of the weight at time t
    QVector2D _velocity;

    //! Mass of the weight
    GLdouble _mass;

    //! Width of the weight
    GLdouble _width;

};

#endif // WEIGHT_H
