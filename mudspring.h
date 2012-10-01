#ifndef MUDSPRING_H
#define MUDSPRING_H

#include <iostream>

class MudParticle;

class MudSpring
{
    static int currId;
    int id;

    float SaveRL;


public:
    MudParticle *mp1,*mp2;

    MudSpring(MudParticle *mp1_, MudParticle *mp2_);
    void setRstLgthFrmParts();
    void saveAndSRLFP();

    float randomBreak;
    int state;
    float currLength;
    float RestingLength;
    float k;

    int getId() const;

    void applyForce();
    void draw();
    friend std::ostream & operator <<(std::ostream & os, const MudSpring & ms);

};

#endif // MUDSPRING_H
