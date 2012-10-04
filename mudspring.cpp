#include "mudspring.h"

#include <mudparticle.h>
#include <GL/gl.h>



MudSpring::MudSpring(std::vector <MudParticle*> * particles_)
{
    particles=particles_;
    k=1.0f;
    state = 0;


    randomBreak = ((float)random()) / RAND_MAX* 0.2f +0.9f;
}

MudSpring::MudSpring(std::vector <MudParticle*> * particles_, unsigned int mp1_, unsigned int mp2_)
{
    particles=particles_;
    mp1 = mp1_;
    mp2 = mp2_;

    setRstLgthFrmParts();
    k=1.0f;
    state = 0;


    randomBreak = ((float)random()) / RAND_MAX* 0.2f +0.9f;
}

void MudSpring::setRstLgthFrmParts() {
    RestingLength = ((*particles)[mp1]->pos - (*particles)[mp2]->pos).length();
    SaveRL = RestingLength;
}

void MudSpring::saveAndSRLFP() {
    RestingLength = SaveRL;
    SaveRL = currLength;
}


void MudSpring::applyForce() {
    if (state == 1) // le ressort est cassé !
        return;
    QVector2D tmp= (*particles)[mp1]->pos - (*particles)[mp2]->pos;
    currLength = tmp.length();

    if (k*currLength / RestingLength > 5.0f*randomBreak) {
        state=1;
        return;
    }
    else if (k*RestingLength / currLength > 3.5f*randomBreak) {
        state=1;
        return;
    }

    tmp /= currLength;

    float forceLength = (RestingLength - currLength) * k;
    QVector2D forceOn1 = tmp * forceLength;
    (*particles)[mp1]->applyForce(forceOn1);
    (*particles)[mp2]->applyForce(-forceOn1);
}


void MudSpring::draw() {
    if (state == 1) // le ressort est cassé !
        return;
    float colorRate = currLength / RestingLength;
    if (colorRate > 1.0f) {
        glColor3f(0.0f, 0.0f ,(colorRate-1.0f)*3.0f);
    }
    else {
        glColor3f((1.0f - colorRate)*3.0f,0.0f,0.0f);
    }


    glVertex2f( (*particles)[mp1]->pos.x(), (*particles)[mp1]->pos.y());
    glVertex2f( (*particles)[mp2]->pos.x(), (*particles)[mp2]->pos.y());
}

std::ostream & operator <<(std::ostream & os, const MudSpring & ms) {
    os<<ms.state<<std::endl;
    os<<ms.RestingLength<<std::endl;
    os<<ms.k<<std::endl;
    os<<ms.mp1<<std::endl;
    os<<ms.mp2<<std::endl;
    return os;
}


std::istream & operator >>(std::istream & is, MudSpring & ms) {
    is>>ms.state;
    is>>ms.RestingLength;
    is>>ms.k;
    is>>ms.mp1;
    is>>ms.mp2;
    ms.setRstLgthFrmParts();
return is;
}
