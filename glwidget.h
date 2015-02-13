/*!
 *  \author    Babak Tootoonchi
 *  \version   2.0
 *  \date      Sept. 2014
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <GL/GLU.h>
#include <QTimer>
#include "utils.h"
#include "weight.h"
#include "spring.h"

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    /// CONSTRUCTOR
    GLWidget(QWidget *parent = 0);

    /// DESTRUCTOR
    ~GLWidget();

    // ADD YOUR CODE
    void draw();
    void reinit(GLdouble len);

    /*! Returns the simulation time step
     * \return the time step
     */
    GLdouble getDelta();

    /*! Set the simulation time step to the given value
     * \param delta set the time step
     */
    void setDelta(GLdouble delta);

    /*! Returns the simulation type
     * \return the simulation type
     */
    simulation_t getSimulationType();

    /*! Set the simulation type to the given value
     * \param type set the simulation step
     */
    void setSimulationType(simulation_t type);

    /*! Return the rest length of the kth spring in weight(i,j).
     * \param i row
     * \param j column
     * \param k spring index
     * \return rest length of the kth spring of weight (i,j)
     */
    GLdouble getRestLen(int i, int j, int k);

    /*! Set the rest length of the springs in the system.
     * \param len rest length of the springs
     */
    void setRestLen(GLdouble len);

    /*! Return the mass of weight(i,j) in the system.
     * \param i row
     * \param j column
     * \return mass of weight (i,j)
     */
    GLdouble getMassValue(int i, int j);

    /*! Set the mass of all the weights in the system.
     * \param m mass of the weights
     */
    void setMassValue(GLdouble m);

    /*! Return the spring constant of the kth spring in weight(i,j).
     * \param i row
     * \param j column
     * \param k spring index
     * \return spring constant of the kth spring of weight (i,j)
     */
    GLdouble getSpringConstant(int i, int j, int k);

    /*! Set the spring constant of the springs in the system.
     * \param ks spring constant.
     */
    void setSpringConstant(GLdouble ks);

    /*! Set the damping coefficient of the springs in the system.
     * \param kd damping coefficient.
     */
    void setSpringDamping(GLdouble kd);

    /*! Return the damping coefficient of the kth spring in weight(i,j).
     * \param i row
     * \param j column
     * \param k spring index
     * \return damping coefficient of the kth spring of weight (i,j)
     */
    GLdouble getSpringDamping(int i, int j, int k);

    /*! Calculates the spring force for weight[i][j].
     * \param i the row at which the weight is located.
     * \param j the column at which the weight is located.
     * \return the spring force.
     */
    QVector2D springForce(int i, int j);

    /*! Calculates the damping force for weight[i][j].
     * \param i the row at which the weight is located.
     * \param j the column at which the weight is located.
     * \return the damping force.
     */
    QVector2D dampingForce(int i, int j);

    /*! Calculates the gravity force for weight[i][j].
     * \param i the row at which the weight is located.
     * \param j the column at which the weight is located.
     * \return the gravity force.
     */
    QVector2D gravityForce(int i, int j);

    /*! Calculates the total force for weight[i][j].
     * \param i the row at which the weight is located.
     * \param j the column at which the weight is located.
     * \return the total force.
     */
    QVector2D totalForces(int i, int j);

    /*! Calculates the velocity of the weight[i][j] at time t+dt.
     * \param i the row at which the weight is located.
     * \param j the column at which the weight is located.
     * \param f total force on the mass.
     * \return the velocity at time t+dt.
     */
    QVector2D getNewVelocity(int i, int j, QVector2D f);

    /*!
     * \brief Calculates the position of the weight[i][j] at time t+dt.
     * \param i the row at which the weight is located.
     * \param j the column at which the weight is located.
     * \param f total force on the mass.
     * \return the new position at time t+dt.
     */
    QVector2D getNewPosition(int i, int j, QVector2D f);

private:
    //! Simulation time step
    GLdouble _deltaSecond;

    //! Simulation type;
    simulation_t _simulationType;

    //! Weight matrix
    Weight _weightMatrix[FLAG_DIMENSIONS][FLAG_DIMENSIONS];

protected:
    //! OPENGL
    void initializeGL();
    void paintGL();
    void resizeGL( int width, int height );

    //! Initialize mass spring system
    /*! Initializes the objects and assign the pointers of the system
     * In this system, the minmum number of springs for each mass is 3
     * and the maximum number of springs is 8 for a mass. The springs
     * will be add clockwise to masses.
     * \param len rest length of the springs
     */
    void initializeMassSpringSystem(GLdouble len);

signals:

public slots:
    /*! Performs the simulation for the next time interval. */
    void simStep();

private slots:

protected slots:


};

#endif // GLWIDGET_H
