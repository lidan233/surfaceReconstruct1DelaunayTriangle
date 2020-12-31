//
// Created by 李源 on 2019-11-16.
//

#ifndef LIDANDELAUNAY_DELAUNAY_H
#define LIDANDELAUNAY_DELAUNAY_H


#include "edge.h"
#include "QuadEdge.h"
#include "calculate.h"
#include "Vec.h"


#include <Eigen/Core>
#include <memory>
#include <vector>
#include <tuple>
#include <iostream>
#include <stdlib.h>
#include <unordered_set>
#include <math.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iomanip>

typedef std::vector<Edge*> EdgeList ;
typedef std::vector<Vertex*> VertexList ;
typedef std::vector<QuadEdge*> QuadList ;
typedef std::tuple<Edge*,Edge*> EdgePartition ;
typedef std::tuple<VertexList,VertexList> VertexPartition;



class Delaunay {
private:
    unsigned long randomseed;
    VertexList vertexs_ ;
    QuadList edges ;
    unsigned  long randomnation(unsigned int choices);

    void generateRandomVertexs(int n) ;
//    void shuttleVertex(VertexList vl,int begin,int end ) ;

public:

    Delaunay(int n) ;
    Delaunay(string path) ;

    VertexList getVertexs(){ return vertexs_;}
    QuadList getEdges(){ return edges ;}

    Vertex* getVertex(int n);
    VertexPartition partitionVertex(const VertexList & vl) ;

    Edge* MakeEdgeBetween(int a, int b, const VertexList& points) ;
    Edge* MakeEdge(Vertex* a,Vertex* b) ;

    Edge* Connect(Edge* a,Edge* b) ;
    void Kill(Edge* e) ;

    EdgePartition beginTriangulate(const VertexList& vertexs ) ;
    EdgePartition ProcessVertexs2(const VertexList& vertexs) ;
    EdgePartition ProcessVertexs3(const VertexList& vertexs) ;
    Edge* findCommandTangent(Edge*& left,Edge*& right) ;

    Edge* left_Candidate(Edge* basel) ;
    Edge* right_Candidate(Edge* basel) ;
    void Mergehull(Edge* &baseEdge) ;

};


#endif //LIDANDELAUNAY_DELAUNAY_H
