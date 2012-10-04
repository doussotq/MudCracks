#ifndef MUD_H
#define MUD_H

#include <vector>
#include <QVector2D>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;




#include <mudparticle.h>
#include <mudspring.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_euclidean_traits_xy_3<K>  Gt;
typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;


class mud
{

    std::vector<K::Point_3> pts;
    Delaunay dt;
    std::vector<MudSpring*> mudSp;
    std::vector<MudParticle*> mudPa;

public:
    mud();


    void dart(float r, int average_fail);
    void convertToSpringMass();
    bool verify(float r_c, float x, float y);

    void retract(float rate);
    void harden(float rate);
    void setCurrent();

    void actualize(float time);
    void paintMudPts();


    void save();
    void load();
    void reset();

};

#endif // MUD_H
