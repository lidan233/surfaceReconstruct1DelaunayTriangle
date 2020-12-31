//
// Created by 李源 on 2019-11-15.
//

#include "edge.h"

Vertex::Vertex(float x, float y):x_(x),y_(y) {}
void Vertex::addEdge(Edge *edge) { this->edge_ = edge;}
Vertex::Vertex(Vertex* another):x_(another->x()),y_(another->y()),z_(another->z()),allindex(another->getallIndex()){}


Edge::Edge(Vertex* org):org_(org){}
Edge::Edge() {}
Edge::~Edge() {}

//so we can get the edge of the quadege
//src rot sym invRot
//we can get the rot manuplication is to add index+1

Edge* Edge::Rot()
{
    return this->rot ;
}
Edge* Edge::Sym()
{

    return this->sym ;
}
Edge* Edge::InvRot()
{
    return this->rot->sym ;
}







