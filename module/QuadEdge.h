//
// Created by 李源 on 2019-11-15.
//

#ifndef LIDANDELAUNAY_QUADEDGE_H
#define LIDANDELAUNAY_QUADEDGE_H
#include "edge.h"


class QuadEdge {
public:
    Edge edges[4] ;
    QuadEdge(Vertex *a,Vertex* b) ;
};



#endif //LIDANDELAUNAY_QUADEDGE_H
