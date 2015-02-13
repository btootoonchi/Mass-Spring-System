#include "spring.h"
#include "utils.h"
#include "weight.h"

Spring::Spring(Weight *head, GLdouble restLen) {
    _restLength = restLen;
    _radius = 0.05;
    _springConstant = 10;
    _dampingCoeff = 0.1;
    _head = head;
    _tail = NULL;
}

Spring::Spring() {
    Spring(NULL, 1);
}

void Spring::setRestLength(GLdouble len) {
    _restLength = len;
}

GLdouble Spring::getRestLength() {
    return _restLength;
}

void Spring::setSpringConstant(GLdouble ks) {
    _springConstant = ks;
}

GLdouble Spring::getSpringConstant() {
    return _springConstant;
}

void Spring::setDampingCoefficient(GLdouble kd) {
    _dampingCoeff = kd;
}

GLdouble Spring::getDampingCoefficient() {
    return _dampingCoeff;
}

void Spring::setPostion(Weight *head, Weight *tail) {
    _head = head;
    _tail = tail;
}

Weight *Spring::getHead() {
    return _head;
}

Weight *Spring::getTail() {
    return _tail;
}

void Spring::draw()
{
    // If rest length is set to 0 draw nothing.
    if (_restLength == 0)
        return;

    // Point count is the number of loops in the spring
    int pointCount = _restLength / UNIT_LEN;

    // Distance between two points on X axis and Y axis
    GLdouble XStep = (_tail->getPos().x() - _head->getPos().x())/(2.0*pointCount);
    GLdouble YStep = (_tail->getPos().y() - _head->getPos().y())/(2.0*pointCount);

    // Slope of the spring
    GLdouble slope;

    // A boolean variable that shows whether the spring is vertical
    bool vertical = false;

    // Spring line equation: y = slope * x + yIntercept
    // If head.x != tail.x, the line is not vertical
    if (fabs(_tail->getPos().x() - _head->getPos().x()) > 0.0001) {
        slope = (_tail->getPos().y()-_head->getPos().y())/(_tail->getPos().x()-_head->getPos().x());
    } else {
        vertical = true;
    }

    // Calculate yIntercept for the spring line
    GLdouble yIntercept = _head->getPos().y() - slope * _head->getPos().x();
    GLdouble x = _head->getPos().x();
    GLdouble y = _head->getPos().y();
    glColor3d(0.7, 0.7, 1.0);
    glLineWidth(2);
    glBegin(GL_LINES);

    for(int i = 0; i < pointCount; i++) {
        //verical spring
        if (vertical) {
            glVertex2d(x, y);
            glVertex2d(x + _radius, y + YStep);
            glVertex2d(x + _radius, y + YStep);
            glVertex2d(x - _radius, y + 2*YStep);
            y += 2*YStep;
        } else if (abs(slope) > 1) {   //near vertical spring, use YSteps
            glVertex2d(x, y);
            glVertex2d((y + YStep - yIntercept)/slope + _radius, y + YStep);
            glVertex2d((y + YStep - yIntercept)/slope + _radius, y + YStep);
            glVertex2d((y + 2*YStep - yIntercept)/slope - _radius, y + 2*YStep);
            y += 2*YStep;
            x = (y - yIntercept)/slope - _radius;
        } else {    //near horizental spring, use XSteps
            glVertex2d(x, y);
            glVertex2d(x + XStep, slope * (x + XStep) + yIntercept + _radius);
            glVertex2d(x + XStep, slope * (x + XStep) + yIntercept + _radius);
            glVertex2d(x + 2*XStep, slope * (x + 2*XStep) + yIntercept - _radius);
            x += 2*XStep;
            y = x * slope + yIntercept - _radius;
        }
    }
    glEnd();
}
