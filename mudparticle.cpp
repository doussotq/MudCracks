#include "mudparticle.h"
#include <mudspring.h>

MudParticle::MudParticle(std::vector<MudSpring*> * springs_)
{
    springs = springs_;
}


void MudParticle::applyForce(QVector2D force) {
    f += force;
}

bool MudParticle::operator==(const MudParticle & mp) const {

    return pos == mp.pos;

}


void MudParticle::addSpring(unsigned int n) {
    springsNums.push_back(n);
}


void MudParticle::actualize(float time) {
    f += (origPos - pos)/2;
    if (type == 0)
        pos += time * f;
    f -= f;
}


std::ostream & operator <<(std::ostream & os, const MudParticle & mp) {
    os<<mp.type<<std::endl;
    os<<mp.origPos.x()<<std::endl;
    os<<mp.origPos.y()<<std::endl;
    os<<mp.pos.x()<<std::endl;
    os<<mp.pos.y()<<std::endl;
    os<<mp.f.x()<<std::endl;
    os<<mp.f.y()<<std::endl;
    os<<mp.springsNums.size()<<std::endl;

    for (std::vector<unsigned int>::const_iterator msIt = mp.springsNums.begin(); msIt != mp.springsNums.end(); msIt++) {
        os<<(*msIt)<<std::endl;
    }
return os;
}

std::istream & operator >>(std::istream & os, MudParticle & mp) {

    os>>mp.type;
    float tmpIn;
    os>>tmpIn;
    mp.origPos.setX(tmpIn);
    os>>tmpIn;
    mp.origPos.setY(tmpIn);

    os>>tmpIn;
    mp.pos.setX(tmpIn);
    os>>tmpIn;
    mp.pos.setY(tmpIn);

    os>>tmpIn;
    mp.f.setX(tmpIn);
    os>>tmpIn;
    mp.f.setY(tmpIn);

    int sn;
    os>>sn;

    std::vector<MudSpring*>::iterator msIt;
    int tmpIn2;
    for (int i=0;i<sn;i++) {
        os>>tmpIn2;
        mp.addSpring(tmpIn2);
    }
return os;
}
