#ifndef MUDSPRING_H
#define MUDSPRING_H

#include <iostream>
#include <vector>

class MudParticle;

class MudSpring
{

    float SaveRL;


public:
    std::vector<MudParticle*> * particles;
    unsigned int mp1,mp2;

    MudSpring(std::vector<MudParticle*> * particles);
    MudSpring(std::vector<MudParticle*> * particles, unsigned int mp1_, unsigned int mp2_);
    void setRstLgthFrmParts();
    void saveAndSRLFP();

    float randomBreak;
    int state;
    float currLength;
    float RestingLength;
    float k;

    void applyForce();
    void draw();
    friend std::ostream & operator <<(std::ostream & os, const MudSpring & ms);
    friend std::istream & operator >>(std::istream & is, MudSpring & ms);

};

#endif // MUDSPRING_H
