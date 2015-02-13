#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent), _deltaSecond(0.05), _simulationType(simulation_I) {
    initializeMassSpringSystem(DEFAULT_REST_LEN);
}

GLWidget::~GLWidget() {
    for(int i = 0; i < FLAG_DIMENSIONS; i++) {
        for(int j = 0; j < FLAG_DIMENSIONS; j++) {
            for (int k = right_spring; k < left_spring; k++) {
                if (_weightMatrix[i][j]._spring[k] != NULL)
                    delete _weightMatrix[i][j]._spring[k];
            }
        }
    }
}

void GLWidget::initializeGL() {
    static const GLfloat lightPos[4] = { 2.0f, 2.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 60.0, 1.0, 0.5, 10.0 );
    gluLookAt( 0.0, -1.8, 5.0, 1, -1.8, 0.0, 0.0, 1.0, 0.0 );


    draw();
    glColor3d(0.6, 0.4, 0.3);
    glBegin(GL_POLYGON);
    glVertex2d(-2, SURFACE);
    glVertex2d(6, SURFACE);
    glVertex2d(6, 2*SURFACE);
    glVertex2d(-2, 2*SURFACE);
    glEnd();
}

void GLWidget::resizeGL( int width, int height ) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 60.0, 1.0, 0.5, 10.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    updateGL();
}

void GLWidget::reinit(GLdouble len) {

    //delete existing spring system
    for(int i = 0; i < FLAG_DIMENSIONS; i++) {
        for(int j = 0; j < FLAG_DIMENSIONS; j++) {
            for (int k = right_spring; k < left_spring; k++) {
                if (_weightMatrix[i][j]._spring[k] != NULL)
                    delete _weightMatrix[i][j]._spring[k];
            }
        }
    }

    // initialize mass spring system
    initializeMassSpringSystem(len);

    // reset time step to 50ms
    _deltaSecond = 0.05;
}

void GLWidget::initializeMassSpringSystem(GLdouble len) {
    GLdouble restLen = len * UNIT_LEN;

    for(int i = 0; i < FLAG_DIMENSIONS; i++) {
        for(int j = 0; j < FLAG_DIMENSIONS; j++) {
            _weightMatrix[i][j].init(QVector2D(j*restLen,-i*restLen));
            for(int k = 0; k < ADJACENT_NUM; k++) {
                if (k > up_right_spring && k < left_spring) {
                    switch (k) {
                    case right_spring:
                        if (j < FLAG_DIMENSIONS-1) {

                            // create new spring
                            _weightMatrix[i][j]._spring[k] = new Spring(&_weightMatrix[i][j], restLen);
                        }
                        break;
                    case right_down_spring:
                        if (i < FLAG_DIMENSIONS-1 && j < FLAG_DIMENSIONS-1) {

                            // create new spring
                            _weightMatrix[i][j]._spring[k] = new Spring(&_weightMatrix[i][j], restLen * sqrt(2.0));
                        }
                        break;
                    case down_spring:
                        if(i < FLAG_DIMENSIONS-1) {

                            // create new spring
                            _weightMatrix[i][j]._spring[k] = new Spring(&_weightMatrix[i][j], restLen);
                        }
                        break;
                    case left_down_spring:
                        if (i < FLAG_DIMENSIONS-1 && j > 0) {

                            // create new spring
                            _weightMatrix[i][j]._spring[k] = new Spring(&_weightMatrix[i][j], restLen * sqrt(2.0));
                        }
                        break;
                    }
                } else {
                    switch (k) {
                    case up_spring:
                        if (i > 0) {

                            // connect the tail of spring of mass (i-1,j),which was already created, to mass (i,j)
                            _weightMatrix[i - 1][j]._spring[down_spring]->_tail = &_weightMatrix[i][j];
                            _weightMatrix[i][j]._spring[k] = _weightMatrix[i - 1][j]._spring[down_spring];
                        }
                        break;
                    case up_right_spring:
                        if (i > 0 && j < FLAG_DIMENSIONS-1) {

                            // connect the tail of spring of mass (i-1,j+1),which was already created, to mass (i,j)
                            _weightMatrix[i - 1][j + 1]._spring[left_down_spring]->_tail = &_weightMatrix[i][j];
                            _weightMatrix[i][j]._spring[k] = _weightMatrix[i - 1][j + 1]._spring[left_down_spring];
                        }
                        break;
                    case left_spring:
                        if (j > 0) {

                            // connect the tail of spring of mass (i,j-1),which was already created, to mass (i,j)
                            _weightMatrix[i][j - 1]._spring[right_spring]->_tail = &_weightMatrix[i][j];
                            _weightMatrix[i][j]._spring[k] = _weightMatrix[i][j - 1]._spring[right_spring];
                        }
                        break;
                    case up_left_spring:
                        if (i > 0 && j > 0) {

                            // connect the tail of spring of mass (i-1,j-1),which was already created, to mass (i,j)
                            _weightMatrix[i - 1][j - 1]._spring[right_down_spring]->_tail = &_weightMatrix[i][j];
                            _weightMatrix[i][j]._spring[k] = _weightMatrix[i - 1][j - 1]._spring[right_down_spring];
                        }
                        break;
                    }
                }
            }
        }
    }
}

GLdouble GLWidget::getDelta() {
    return _deltaSecond;
}

void GLWidget::setDelta(GLdouble delta) {
    _deltaSecond = delta;
}

simulation_t GLWidget::getSimulationType() {
    return _simulationType;
}

void GLWidget::setSimulationType(simulation_t type) {
    _simulationType = type;
}

GLdouble GLWidget::getRestLen(int i, int j, int k) {
    if (_weightMatrix[i][j]._spring[k] != NULL)
        return _weightMatrix[i][j]._spring[k]->getRestLength()/UNIT_LEN;
    return 0;
}

void GLWidget::setRestLen(GLdouble len) {
    reinit(len);
}

GLdouble GLWidget::getMassValue(int i, int j) {
    return _weightMatrix[i][j].getMass();
}

void GLWidget::setMassValue(GLdouble m) {
    for(int i = 0; i < FLAG_DIMENSIONS; i++) {
        for(int j = 0; j < FLAG_DIMENSIONS; j++) {
            // set mass
            _weightMatrix[i][j].setMass(m);
        }
    }
}

GLdouble GLWidget::getSpringConstant(int i, int j, int k) {
    if (_weightMatrix[i][j]._spring[k] != NULL)
        return _weightMatrix[i][j]._spring[k]->getSpringConstant();
    return 0;
}

void GLWidget::setSpringConstant(GLdouble ks) {
    for(int i = 0; i < FLAG_DIMENSIONS; i++) {
        for(int j = 0; j < FLAG_DIMENSIONS; j++) {
            // iterate through springs around mass(i,j)
            // spring right, right down, down, and left down
            for (int k = right_spring; k < left_spring; k++) {
                if (_weightMatrix[i][j]._spring[k] != NULL)
                    // set spring constant for spring k
                    _weightMatrix[i][j]._spring[k]->setSpringConstant(ks);
            }
        }
    }
}

GLdouble GLWidget::getSpringDamping(int i, int j, int k) {
    if (_weightMatrix[i][j]._spring[k] != NULL)
        return _weightMatrix[i][j]._spring[k]->getDampingCoefficient();
    return 0;
}

void GLWidget::setSpringDamping(GLdouble kd) {
    for(int i = 0; i < FLAG_DIMENSIONS; i++) {
        for(int j = 0; j < FLAG_DIMENSIONS; j++) {
            // iterate through springs around mass(i,j)
            // spring right, right down, down, and left down
            for (int k = right_spring; k < left_spring; k++) {
                if (_weightMatrix[i][j]._spring[k] != NULL)
                    // set damping coefficient for spring k
                    _weightMatrix[i][j]._spring[k]->setDampingCoefficient(kd);
            }
        }
    }
}

void GLWidget::draw() {
    for (int i = 0; i < FLAG_DIMENSIONS; i++) {
        for (int j = 0; j < FLAG_DIMENSIONS; j++) {
            // draw mass
            _weightMatrix[i][j].draw();
            // iterate through springs around mass(i,j)
            // spring right, right down, down, and left down
            for (int k = right_spring; k < left_spring; k++) {
                if (_weightMatrix[i][j]._spring[k] != NULL) {
                    // draw spring
                    _weightMatrix[i][j]._spring[k]->draw();
                }
            }
        }
    }
}

QVector2D GLWidget::springForce(int i, int j) {
    GLdouble ks, l0;
    QVector2D totalForceSpring(0,0), l;

    // iterate through springs around mass(i,j) to calculate spring forces
    for(int k = 0; k < ADJACENT_NUM; k++) {
        if (_weightMatrix[i][j]._spring[k] != NULL) {

            // spring constant
            ks = _weightMatrix[i][j]._spring[k]->getSpringConstant();

            // spring rest lenght
            l0 = _weightMatrix[i][j]._spring[k]->getRestLength();
            if (k >= right_spring && k <= left_down_spring) {

                // spring length change for springs form right spring to left down spring. it means spring right, right down, down, and left down
                l = _weightMatrix[i][j]._spring[k]->_tail->getPos() - _weightMatrix[i][j]._spring[k]->_head->getPos();
            } else {

                // spring length change for springs form right spring to left down spring. it means spring right, right down, down, and left down
                l = _weightMatrix[i][j]._spring[k]->_head->getPos() - _weightMatrix[i][j]._spring[k]->_tail->getPos();
            }

            // to prevent having very large spring forces due to zero lenght, cap the spring force to when the spring length is half of rest length
            if(l.length()<(l0*0.5)) {
                l = (0.5*l0) * l/l.length() * UNIT_LEN;
            }

            // spring force for spring k
            QVector2D fs = ks * (l.length() - l0) * (l/l.length()) ;

            totalForceSpring = totalForceSpring + fs;
        }
    }
    return totalForceSpring;
}

QVector2D GLWidget::dampingForce(int i, int j) {
    GLdouble kd;
    QVector2D dx, dv, totalForceDamping(0,0);

    // iterate through springs around mass(i,j) to calculate spring damping forces
    for(int k = 0; k < ADJACENT_NUM; k++) {
        if (_weightMatrix[i][j]._spring[k] != NULL) {

            // damping force
            kd = _weightMatrix[i][j]._spring[k]->getDampingCoefficient();

            if (k >= right_spring && k <= left_down_spring) {

                // spring velocity change for springs form right spring to left down spring. it means spring right, right down, down, and left down
                dv = _weightMatrix[i][j]._spring[k]->_tail->getVelocity() - _weightMatrix[i][j]._spring[k]->_head->getVelocity();
            } else {

                // spring velocity change for springs that are up, up right, left, and up left spring.
                dv = _weightMatrix[i][j]._spring[k]->_head->getVelocity() - _weightMatrix[i][j]._spring[k]->_tail->getVelocity();
            }

            // damping force for spring k = damping coeffcient * velocity * ???
            QVector2D fd = kd * dv;

            totalForceDamping = totalForceDamping + fd;
        }
    }

    return totalForceDamping;
}

QVector2D GLWidget::gravityForce(int i, int j) {
    GLdouble m = _weightMatrix[i][j].getMass();

    // gravity force = mass * gravity acceleration
    return m * GRAVITY * QVector2D(0, 1);
}

QVector2D GLWidget::totalForces(int i, int j) {
    QVector2D fs, fd, fg;

    fs = springForce(i,j);
    fd = dampingForce(i,j);
    fg = (_weightMatrix[i][j].getPos().y() > SURFACE) ? gravityForce(i,j) : QVector2D(0,0);    //collision detection

    // total force = spring force + damping force + gravity force
    return fs + fd + fg;
}

QVector2D GLWidget::getNewVelocity(int i, int j, QVector2D f) {
    QVector2D vt;
    GLdouble m;

    vt = _weightMatrix[i][j].getVelocity();
    m = _weightMatrix[i][j].getMass();

    return vt + ((_deltaSecond * f) / m);
}

QVector2D GLWidget::getNewPosition(int i, int j, QVector2D f) {
    QVector2D xt, xdt, vt;
    GLdouble m;

    xt = _weightMatrix[i][j].getPos();
    vt = _weightMatrix[i][j].getVelocity();
    m = _weightMatrix[i][j].getMass();
    xdt = xt + (vt * _deltaSecond) + ((pow(_deltaSecond,2.0) * f) / (2 * m));

    // collision detection
    if (xdt.y() <= SURFACE) {
         xdt.setY(SURFACE);
    }
    return xdt;
}

void GLWidget::simStep() {

    simulation_t type = getSimulationType();
    int sim1 = (type == simulation_I) ? 1: 0;
    int sim2 = (type == simulation_II) ? 1: sim1;

    // iterate through all index(mass) of array
    for(int i = sim1; i < FLAG_DIMENSIONS; i++) {
        for(int j = sim2; j < FLAG_DIMENSIONS-sim2; j++) {

            // Calculate total force
            QVector2D forces = totalForces(i,j);

            // Calculate the new velocity and set it
            _weightMatrix[i][j].setVelocity(getNewVelocity(i,j,forces));

            // Set the new positions
            _weightMatrix[i][j].setPos(getNewPosition(i,j,forces));
        }
    }

    // Update the screen
    updateGL();
}

