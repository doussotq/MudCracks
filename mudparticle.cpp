#include "mudparticle.h"
#include <mudspring.h>

int MudParticle::currId=0;

void MudParticle::toggleCounter(bool on) {
    counterOn=on;
}

MudParticle::MudParticle()
{

    if (counterOn) {
        currId++;
        id = currId;
    }
    else id = -1;

}

MudParticle::MudParticle(const MudParticle &mp) {
    (*this)=mp;
    if (counterOn) {
        currId++;
        id = currId;
    }
    else id = -1;
}


int MudParticle::getId() const {
    return id;
}

void MudParticle::applyForce(QVector2D force) {
    f += force;
}

bool MudParticle::operator==(const MudParticle & mp) const {

    return pos == mp.pos;

}


void MudParticle::addSpring(MudSpring *s) {
    springs.push_back(s);
}


void MudParticle::actualize(float time) {
    f += (origPos - pos)/2;
    if (type == 0)
        pos += time * f.normalized();
    f -= f;
}


std::ostream & operator <<(std::ostream & os, const MudParticle & mp) {
    os<<mp.getId()<<std::endl;
    os<<mp.type<<std::endl;
    os<<mp.origPos.x()<<std::endl;
    os<<mp.origPos.y()<<std::endl;
    os<<mp.pos.x()<<std::endl;
    os<<mp.pos.y()<<std::endl;
    os<<mp.f.x()<<std::endl;
    os<<mp.f.y()<<std::endl;
    os<<mp.springs.size()<<std::endl;

//    std::vector<MudSpring*>::iterator msIt;
    for (std::vector<MudSpring*>::const_iterator msIt = mp.springs.begin(); msIt != mp.springs.end(); msIt++) {
        os<< ((*msIt)->getId());
    }

return os;
}

std::istream & operator <<(std::istream & os, MudParticle & mp) {
    os>>mp.id;

    /*os<<mp.type<<std::endl;
    os<<mp.origPos.x()<<std::endl;
    os<<mp.origPos.y()<<std::endl;
    os<<mp.pos.x()<<std::endl;
    os<<mp.pos.y()<<std::endl;
    os<<mp.f.x()<<std::endl;
    os<<mp.f.y()<<std::endl;
    os<<mp.springs.size()<<std::endl;

//    std::vector<MudSpring*>::iterator msIt;
    for (std::vector<MudSpring*>::const_iterator msIt = mp.springs.begin(); msIt != mp.springs.end(); msIt++) {
        os<< ((*msIt)->getId());
    }
*/
return os;
}
