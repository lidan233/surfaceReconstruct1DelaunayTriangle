//
// Created by 李源 on 2019-11-15.
//

#include "QuadEdge.h"
QuadEdge::QuadEdge(Vertex *a,Vertex* b) {
    edges[0].setIndex(0) ;
    edges[1].setIndex(1) ;
    edges[2].setIndex(2) ;
    edges[3].setIndex(3) ;

    edges[0].draw = false ;
    edges[1].draw = false ;
    edges[2].draw = false ;
    edges[3].draw = false ;

    edges[0].setNext((edges+0)) ;
    edges[1].setNext((edges+3)) ;
    edges[2].setNext((edges+2)) ;
    edges[3].setNext((edges+1)) ;

    edges[0].org_ = a ;
    edges[1].org_ = &inf_pt ;
    edges[2].org_ = b ;
    edges[3].org_ = &inf_pt ;

    edges[0].rot = &edges[1] ;
    edges[1].rot = &edges[2] ;
    edges[2].rot = &edges[3] ;
    edges[3].rot = &edges[0] ;

    edges[0].sym = &edges[2] ;
    edges[1].sym = &edges[3] ;
    edges[2].sym = &edges[0] ;
    edges[3].sym = &edges[1] ;

}

//create a quadedge and list back the edge
Edge* Edge::MakeEdge(std::vector<QuadEdge *> &list,Vertex* a,Vertex *b) {
    list.push_back(new QuadEdge(a,b)) ;
    return list.back()->edges ;

}