#ifndef VIEWER_H
#define VIEWER_H

#include <QGLWidget>
#include <QTimer>

#include <mud.h>

class Viewer : public QGLWidget
{
    Q_OBJECT

    int counter;
    int counter2;
    QTimer * timer;
public:

    mud m;
    bool isRetracting;

    explicit Viewer(QWidget *parent = 0);
    void initializeGL();
    virtual void paintGL();


signals:
    
public slots:
    void repaint();
    void generateMud();
    void retractMud();
    void hardenMud();
    void saveMud();
    void loadMud();
    void setCurrent();
};

#endif // VIEWER_H
