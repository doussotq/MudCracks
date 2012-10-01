#include "viewer.h"
#include <QDebug>


Viewer::Viewer(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    timer = new QTimer(this);
    timer->start(10);
    connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));
    isRetracting = false;
    counter=0;
    counter2=0;
}


void Viewer::initializeGL(){
    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    glEnable(GL_DEPTH_TEST);

    m.dart(0.05f,50);
    m.convertToSpringMass();

}


void Viewer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0,0,0);
    m.paintMudPts();

}

void Viewer::repaint() {
    m.actualize(0.001);
    if (isRetracting) {
        counter++;
        qDebug()<<"is Retracting ! ";
        if (counter %10 == 0)
            m.retract(0.99f);

        if (counter == 800 + counter2) {
            counter = 0;
            counter2+=20;
            m.setCurrent();
        }
    }
    updateGL();
}


void Viewer::retractMud() {
    isRetracting= !isRetracting;
    //m.retract(0.95f);
}

void Viewer::hardenMud() {
    m.harden(1.01f);
}

void Viewer::saveMud() {
    m.save();
}

void Viewer::loadMud() {
    m.load();
}

void Viewer::setCurrent() {
    m.setCurrent();
}
