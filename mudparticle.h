#ifndef MUDPARTICLE_H
#define MUDPARTICLE_H

#include <vector>
#include <QVector2D>
#include <iostream>


class MudSpring;

class MudParticle
{

    static int currId;
    static bool counterOn;
    static void toggleCounter(bool on);
    int id;

public: 

    MudParticle();
    MudParticle(const MudParticle & mp);


    int getId() const;

    int type;
    QVector2D origPos;
    QVector2D pos;
    QVector2D f; // Permet d'additioner la force des ressorts.
    void applyForce(QVector2D force);


    std::vector<MudSpring*> springs;
    void addSpring(MudSpring *s);

    bool operator==(const MudParticle & mp) const;
    bool operator!=(const MudParticle & mp) const { return ! (*(this) == mp); }

    friend std::ostream & operator <<(std::ostream & os, const MudParticle & mp);
    friend std::istream & operator >>(std::istream & os, MudParticle & mp);

    //Actualiser la position et remets à 0 f.
    void actualize(float time);



};



#endif // MUDPARTICLE_H
