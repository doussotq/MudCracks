#include "mudspring.h"

#include <mudparticle.h>
#include <GL/gl.h>


int MudSpring::currId=0;

MudSpring::MudSpring(MudParticle *mp1_, MudParticle *mp2_)
{
    id = currId;
    currId++;

    mp1 = mp1_;
    mp1->addSpring(this);

    mp2 = mp2_;
    mp2->addSpring(this);

    setRstLgthFrmParts();
    k=1.0f;
    state = 0;


    randomBreak = ((float)random()) / RAND_MAX* 0.2f +0.9f;
}

void MudSpring::setRstLgthFrmParts() {
    RestingLength = (mp1->pos - mp2->pos).length();
    SaveRL = RestingLength;
}

void MudSpring::saveAndSRLFP() {
    RestingLength = SaveRL;
    SaveRL = currLength;
}

int MudSpring::getId() const {
    return id;
}

void MudSpring::applyForce() {
    if (state == 1) // le ressort est cassé !
        return;
    QVector2D tmp= mp1->pos - mp2->pos;
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
    mp1->applyForce(forceOn1);
    mp2->applyForce(-forceOn1);
}


void MudSpring::draw() {
    if (state == 1) // le ressort est cassé !
        return;
    float colorRate = currLength / RestingLength;
    if (colorRate > 1.0f) {
        glColor3f(0.0f, 0.0f ,(colorRate-1.0f));
    }
    else {
        glColor3f(1.0f - colorRate,0.0f,0.0f);
    }


    glVertex2f( mp1->pos.x(), mp1->pos.y());
    glVertex2f( mp2->pos.x(), mp2->pos.y());
}

std::ostream & operator <<(std::ostream & os, const MudSpring & ms) {
    os<<ms.getId()<<std::endl;
    os<<ms.state<<std::endl;
    os<<ms.RestingLength<<std::endl;
    os<<ms.k<<std::endl;
    os<<ms.mp1->getId()<<std::endl;
    os<<ms.mp2->getId()<<std::endl;
}
