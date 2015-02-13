QT       += core gui opengl widgets declarative

TARGET   = MassSpringSimulation
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           glwidget.cpp \
    spring.cpp \
    weight.cpp


HEADERS  += mainwindow.h \
            glwidget.h \
    spring.h \
    weight.h \
    utils.h

FORMS    += mainwindow.ui


