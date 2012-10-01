#include "mud.h"
#include <random>

#include <GL/gl.h>

#include <QDebug>


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <utils.h>

#include <iostream>
#include <fstream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_euclidean_traits_xy_3<K>  Gt;

typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;
typedef Delaunay::Edge_iterator  Edge_iterator;

typedef K::Point_3   Point;





mud::mud()
{
}


void mud::dart(float r, int average_fail) {

    float curr_aver_fail = 0;
    int curr_try = 0;
    int last_try;
    bool find_before_mt;

    float r_c = r*r;
    while(curr_aver_fail < average_fail) {

        find_before_mt = false;
        curr_try=0;
        while(curr_try < 2* average_fail) {

            float randx = 2.0f * float(random())/RAND_MAX - 1.0f;
            float randy = 2.0f * float(random())/RAND_MAX - 1.0f;
            //qDebug()<<randx<<" - "<<randy;
            if (verify(r_c,randx,randy)) {
                pts.push_back(Point(randx,randy,0));
                find_before_mt = true;
                break;
            }
            curr_try++;
        }

        curr_aver_fail = 0.8 * curr_aver_fail + 0.2 * curr_try;
    }
}




void mud::convertToSpringMass() {



    std::vector<Point>::iterator begin = pts.begin();
    std::vector<Point>::iterator end= pts.end();


    dt.insert(begin,end);
    qDebug() <<" n of v" << dt.number_of_vertices();



    Edge_iterator eit;
    MudParticle tmp_mp1, tmp_mp2;
    MudParticle *tmp_pmp1, *tmp_pmp2;

    int nEdge=0;

    for (eit = dt.edges_begin();eit != dt.edges_end();eit++) {
        Delaunay::Face_handle  f = (*eit).first;
        int i = (*eit).second;
        Delaunay::Vertex_handle vh1 = f->vertex(dt.cw(i));
        Delaunay::Vertex_handle vh2 = f->vertex(dt.ccw(i));

        float tmpX = (*vh1).point().x();
        float tmpY = (*vh1).point().y();

        tmp_mp1.pos.setX(tmpX);
        tmp_mp1.pos.setY(tmpY);
        tmp_mp1.origPos= tmp_mp1.pos;
        if (tmpX > -0.9 && tmpY > -0.9 && tmpX < 0.9 && tmpY < 0.9 )
            tmp_mp1.type = 0;
        else
            tmp_mp1.type = 1;

        tmpX = (*vh2).point().x();
        tmpY = (*vh2).point().y();
        tmp_mp2.pos.setX(tmpX);
        tmp_mp2.pos.setY(tmpY);
        tmp_mp2.origPos= tmp_mp2.pos;

        if (tmpX > -0.9 && tmpY > -0.9 && tmpX < 0.9 && tmpY < 0.9 )
            tmp_mp2.type = 0;
        else
            tmp_mp2.type = 1;


        tmp_pmp1 = utils::findOrAdd(mudPa,&tmp_mp1);
        tmp_pmp2 = utils::findOrAdd(mudPa,&tmp_mp2);

        mudSp.push_back(new MudSpring (tmp_pmp1, tmp_pmp2));
        nEdge++;

    }

    qDebug()<<"mudPa : "<<mudPa.size();
    qDebug()<<"nEdge : "<<nEdge<< " et "<<mudSp.size();


}



float dist(float x, float y, Point & a) {
    float xd = x - a.x();
    float yd = y - a.y();

    return xd*xd + yd*yd;
}

bool mud::verify(float r_c, float x, float y) {
    std::vector<Point>::iterator it;
    for (it = pts.begin(); it != pts.end(); it++) {
        if (dist(x,y,*it) < r_c) {
            return false;
        }
    }
    return true;
}

void mud::retract(float rate) {
    std::vector<MudSpring*>::iterator spIt;
    for (spIt = mudSp.begin(); spIt != mudSp.end(); spIt++) {
        (*spIt)->RestingLength *= rate;
    }
}

void mud::harden(float rate ) {
    std::vector<MudSpring*>::iterator spIt;
    for (spIt = mudSp.begin(); spIt != mudSp.end(); spIt++) {
        (*spIt)->k *= rate;
    }
}
void mud::setCurrent() {
    std::vector<MudSpring*>::iterator spIt;
    for (spIt = mudSp.begin(); spIt != mudSp.end(); spIt++) {
        (*spIt)->saveAndSRLFP();
    }
}


void mud::actualize(float time) {
    std::vector<MudParticle*>::iterator paIt;
    for (paIt = mudPa.begin(); paIt != mudPa.end(); paIt++) {
        (*paIt)->actualize(time);
    }

    std::vector<MudSpring*>::iterator spIt;
    for (spIt = mudSp.begin(); spIt != mudSp.end(); spIt++) {
        (*spIt)->applyForce();
    }

}

void mud::paintMudPts() {
    std::vector<MudParticle*>::iterator paIt;

    glBegin(GL_POINTS);
    for (paIt = mudPa.begin(); paIt != mudPa.end(); paIt++) {
        QVector2D tmp = (*paIt)->pos;
        glVertex2f( tmp.x(), tmp.y());
        /*
        glVertex2f( tmp.x()-0.01f, tmp.y()-0.01f);
        glVertex2f( tmp.x()+0.01f, tmp.y()-0.01f);
        glVertex2f( tmp.x()+0.01f, tmp.y()+0.01f);
        glVertex2f( tmp.x()-0.01f, tmp.y()+0.01f);
        */

    }
    glEnd();


    std::vector<MudSpring*>::iterator msIt;
    glBegin(GL_LINES);
    for (msIt = mudSp.begin(); msIt != mudSp.end(); msIt++) {
        (*msIt)->draw();
    }
    glEnd();
}

void mud::save() {
    qDebug()<<"save mud !";
    std::fstream file;
    file.open("mud.mud",std::fstream::out);
    file<<mudPa.size()<<std::endl;
    file<<mudSp.size()<<std::endl;
    file<<std::endl;

    std::vector<MudParticle*>::iterator paIt;
    for (paIt = mudPa.begin(); paIt != mudPa.end(); paIt++) {
        file<<*(*paIt);
    }

    std::vector<MudSpring*>::iterator msIt;
    for (msIt = mudSp.begin(); msIt != mudSp.end(); msIt++) {
        file<<*(*msIt);
    }
    file.close();
}

void mud::load() {
    std::fstream file;
    file.open("mud.mud",std::fstream::in);
    int nbrParts, nbrSprings;
    file>>nbrParts;
    file>>nbrSprings;
    qDebug()<<"nbr Parts : "<<nbrParts;
    qDebug()<<"nbr Springs : "<<nbrSprings;

    for (int numP=0;numP<nbrParts;numP++) {

    }

    file.close();
}
