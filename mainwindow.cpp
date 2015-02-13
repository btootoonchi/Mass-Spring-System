#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include "utils.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), ui->glwidget, SLOT(simStep()));
    timer->start(50);  //in miliseconds
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_MassValue_valueChanged(double m)
{
    ui->glwidget->setMassValue(m);
}

void MainWindow::on_RestLengthValue_valueChanged(double len)
{
    ui->glwidget->setRestLen(len);
}

void MainWindow::on_StiffnessValue_valueChanged(double ks)
{
    ui->glwidget->setSpringConstant(ks);
}

void MainWindow::on_DampingValue_valueChanged(double kd)
{
    ui->glwidget->setSpringDamping(kd);
}

void MainWindow::on_TimeStepValue_valueChanged(double delta)
{
    ui->glwidget->setDelta(delta);
}

void MainWindow::on_restartButton_clicked()
{
    ui->glwidget->reinit(DEFAULT_REST_LEN);
    ui->MassValue->setValue(ui->glwidget->getMassValue(0,0));
    ui->RestLengthValue->setValue(ui->glwidget->getRestLen(0,0,4));
    ui->StiffnessValue->setValue(ui->glwidget->getSpringConstant(0,0,4));
    ui->DampingValue->setValue(ui->glwidget->getSpringDamping(0,0,4));
    ui->TimeStepValue->setValue(ui->glwidget->getDelta());
}

void MainWindow::on_Simulation1Button_clicked()
{
    ui->glwidget->setSimulationType(simulation_I);
    ui->glwidget->reinit(DEFAULT_REST_LEN);
    ui->MassValue->setValue(ui->glwidget->getMassValue(0,0));
    ui->RestLengthValue->setValue(ui->glwidget->getRestLen(0,0,4));
    ui->StiffnessValue->setValue(ui->glwidget->getSpringConstant(0,0,4));
    ui->DampingValue->setValue(ui->glwidget->getSpringDamping(0,0,4));
    ui->TimeStepValue->setValue(ui->glwidget->getDelta());
}

void MainWindow::on_Simulation2Button_clicked()
{
    ui->glwidget->setSimulationType(simulation_II);
    ui->glwidget->reinit(DEFAULT_REST_LEN);
    ui->MassValue->setValue(ui->glwidget->getMassValue(0,0));
    ui->RestLengthValue->setValue(ui->glwidget->getRestLen(0,0,4));
    ui->StiffnessValue->setValue(ui->glwidget->getSpringConstant(0,0,4));
    ui->DampingValue->setValue(ui->glwidget->getSpringDamping(0,0,4));
    ui->TimeStepValue->setValue(ui->glwidget->getDelta());
}
