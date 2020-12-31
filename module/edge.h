//
// Created by 李源 on 2019-11-15.
//

#ifndef LIDANDELAUNAY_EDGE_H
#define LIDANDELAUNAY_EDGE_H

#include <memory>
#include <Eigen/Core>
#include <vector>
#include <string.h>


using namespace std ;

class Edge ;
class QuadEdge ;


class Vertex {
private:
    Edge *edge_;
    float x_;
    float y_;
    float z_;
    int index;
    int allindex;
public:

    Vertex(float x, float y);

    Vertex(Vertex *another);

    Vertex() {}

    int getallIndex() { return allindex; }



    void setallIndex(int i) { allindex = i; }

    void addEdge(Edge *edge);

    float x() { return x_; }

    float y() { return y_; }

    float z() { return z_; }

    float lengthsquared() { return x_ * x_ + y_ * y_; }

    void setz(float z) { z_ = z; }

    string toString() { return std::to_string(x_) + " " + std::to_string(y_); }

    bool static compare(Vertex a, Vertex b) {
        if (a.x() != b.x()) {
            return a.x() < b.x();
        } else {
            return a.y() < b.y();
        }
    }

    inline bool operator==(const Vertex &ps) const {

        if (this->x_==ps.x_ && this->y_==ps.y_ )
            return true;
        return false;
    };
    inline Vertex operator-(const Vertex &ps) const {

        return Vertex(this->x_-ps.x_,this->y_-ps.y_) ;
    }
    ;
    inline double cross(const Vertex& p) const
    {
        return  x_ * p.y_ - y_ * p.x_;
    }
    inline double cross(const Vertex& a,const Vertex& b) const
    {
        return (a-*this).cross(b - *this);
    } ;
};

static Vertex inf_pt = Vertex(1e18, 1e18);


class Edge {
private:
    Vertex *org_ = nullptr;

//    Vertex *des ;
    Edge* rot;
    Edge* sym ;
    Edge*  oNext ;
    int index_ ;
    friend QuadEdge ;


public:
    bool used = false ;
    Edge(Vertex* org) ;
    Edge() ;
    ~Edge() ;

    bool draw ;

    int index() {return index_; }

    //基础操作 其他操作均有此组合导出
    Edge* Rot() ;
    Edge* Sym() ;
    Edge* InvRot();//基础操作对称操作
    Edge* Onext(){ return oNext;}  //基础属性




    //导出操作
    Edge* Oprev()	{ return Rot()->Onext()->Rot(); };
    Edge* Dnext()	{ return Sym()->Onext()->Sym(); };
    Edge* Dprev()	{ return InvRot()->Onext()->InvRot(); };
    Edge* Lnext()	{ return InvRot()->Onext()->Rot(); };
    Edge* Lprev()	{ return Onext()->Sym(); };
    Edge* Rnext()	{ return Rot()->Onext()->InvRot(); };
    Edge* Rprev()	{ return Sym()->Onext(); };


    //other manipulation
    Vertex* org() { return org_ ;}
    Vertex* Des() { return Sym()->org_ ;}

    void setNext(Edge *next) {oNext = next ;}
    void setIndex(int index ){ index_=index ;}
    static Edge* MakeEdge(std::vector<QuadEdge*>& list,Vertex* a,Vertex* b) ;



};


#endif //LIDANDELAUNAY_EDGE_H
