#include "weight.h"
#include "utils.h"

Weight::Weight()
{
    // Initialize with default position at (1,1)
    init(QVector2D(1,1));
}

void Weight::init(QVector2D pos)
{
    _width = 0.3;
    _mass = 1;   //1kg
    _pos = pos;
    _velocity.setX(0);
    _velocity.setY(0);

    // Resize vector to store eight pointers for eight adjacent springs
    _spring.resize(8);
}

Weight::~Weight() {
    _spring.clear();
}

void Weight::setPos(QVector2D pos) {
    _pos = pos;
}

QVector2D Weight::getPos() {
    return _pos;
}

void Weight::setVelocity(QVector2D v) {
    _velocity = v;
}

QVector2D Weight::getVelocity() {
    return _velocity;
}

void Weight::setMass(GLdouble m) {
    _mass = m;
}

GLdouble Weight::getMass() {
    return _mass;
}

GLdouble Weight::getWidth() {
    return _width;
}

void Weight::draw(){

    // Draw a square of width _width around the position
    glColor3d(0.3, 1.0, 0.3);
    glBegin(GL_POLYGON);
    glVertex2d(_pos.x() - _width/2, _pos.y() + _width/2);
    glVertex2d(_pos.x() + _width/2, _pos.y() + _width/2);
    glVertex2d(_pos.x() + _width/2, _pos.y() - _width/2);
    glVertex2d(_pos.x() - _width/2, _pos.y() - _width/2);
    glEnd();
}

