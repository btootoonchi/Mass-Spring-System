/*!
 *  \author    Babak Tootoonchi
 *  \version   2.0
 *  \date      Sept. 2014
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    //! Action item for changing the mass value of all the weights.
    /*! Sets all the weights' masses to the new value.
     *  \param mass new mass value.
     */
    void on_MassValue_valueChanged(double m);

    //! Action item for changing the rest length of all the springs.
    /*! Sets the rest length of all the springs to the new value.
     *  \param len new spring rest length.
     */
    void on_RestLengthValue_valueChanged(double len);

    //! Action item for changing the spring constant
    /*! Sets the spring constants to the new value.
     *  \param ks new spring constant.
     */
    void on_StiffnessValue_valueChanged(double ks);

    //! Action item for changing the spring damping coefficient
    /*! Sets the spring damping coefficients to the new value.
     *  \param ks new spring damping coefficient.
     */
    void on_DampingValue_valueChanged(double kd);

    //! Action item for changing the simulation time intervals
    /*! Sets the delta time between simulation steps
     *  \param delta simulation interval in seconds.
     */
    void on_TimeStepValue_valueChanged(double delta);

    //! Action item for clicking the restart simulation button
    /*! Restarts the simulation from the starting state. */
    void on_restartButton_clicked();

    //! Soccer goal simulation
    void on_Simulation1Button_clicked();

    //! Volleyball net simulation
    void on_Simulation2Button_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;

};

#endif // MAINWINDOW_H
